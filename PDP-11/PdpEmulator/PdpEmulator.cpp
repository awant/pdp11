#include "stdafx.h"
#include <bitset>
#include "PdpEmulator.h"
#include "PdpConstants.h"
#include "InstructionSet.h"

PdpEmulator::PdpEmulator() {
	instructionSet = new InstructionSet(this);
	disasm = new Disassembler(this);

	for (int i = 0; i < 6; i++)
		registers[i] = 0;
	registers[6] = PdpConstants::StackPointerBegin;
	registers[7] = PdpConstants::ProgramCounterBegin;
	processorStatusWord = 0;

	initProgram();
}

PdpEmulator::~PdpEmulator() {
	if (instructionSet)	delete instructionSet;	 instructionSet = nullptr;
	if (disasm)			delete disasm;			 disasm = nullptr;
}

bool PdpEmulator::PerformCurrentInstruction() {
	word num = *GetWordFromMemory(GetRegisterValue(7));
	SetRegisterValue(7, GetRegisterValue(7) + 2);
	return GetInstruction(num)();
}

std::string PdpEmulator::GetCurrentInstruction() {
	offset_t pc = GetRegisterValue(7);
	word num = *GetWordFromMemory(pc);
	return GetInstructionString(num, pc);
}

std::function<bool()> PdpEmulator::GetInstruction(uword instrCode) {
	return instructionSet->GetInstruction(instrCode);
}

std::string PdpEmulator::GetInstructionString(uword instrCode, offset_t pc) {
	return disasm->GetInstructionString(instrCode, pc);
}


// image loading by Roman
unsigned char getByte(const char* data)
{
	unsigned char byte = 0;
	const char* end = data + 8;

	for (; *data && (data < end); ++data)
	{
		byte <<= 1;

		byte |= (*data == '1') ? 1 : 0;
	}

	return byte;
}

void PdpEmulator::initProgram() {
	// Read program
	std::ifstream file("..\\PdpEmulator\\program.h", std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	byte data[077777];
	if (file.read(data, size))
	{
		std::cout << "Read file!\n";
	}
	const char* array = data;

	unsigned int offset = 0100000;
	int isOdd = 0;
	while (array - data < size)
	{
		unsigned char byte = getByte(array);
		if (isOdd) {
			memcpy(memory + offset, &byte, 1);
			isOdd = 0;
			offset += 2;
		}
		else {
			memcpy(memory + offset + 1, &byte, 1);
			isOdd = 1;
		}
		array += 8;
	}

	// Read image
	std::ifstream image("..\\PdpEmulator\\image.bmp", std::ios::binary | std::ios::ate);
	std::streamsize sizeImage = image.tellg();
	image.seekg(0, std::ios::beg);
	if (image.read(memory + 0110000, sizeImage))
	{
		std::cout << "Read image!\n";
	}
}
