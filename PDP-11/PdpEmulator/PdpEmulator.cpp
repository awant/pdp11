#include "stdafx.h"
#include "PdpEmulator.h"
#include "PdpConstants.h"
#include "InstructionSet.h"

PdpEmulator::PdpEmulator() {
	instructionSet = new InstructionSet(this);

	for (int i = 0; i < 6; i++)
		registers[i] = 0;
	registers[6] = 020000;
	registers[7] = 040000;
	processorStatusWord = 0;

	//loadProgram();
	initProgram();
}

PdpEmulator::~PdpEmulator() {
	if (instructionSet)	delete instructionSet;	 instructionSet = nullptr;
}

std::function<void()> PdpEmulator::GetInstruction(int number) {
	return instructionSet->GetInstruction(number);
}

std::string PdpEmulator::GetInstructionString(int number) {
	return disasm->GetInstructionString(number);
}

void PdpEmulator::loadProgram() {
	word instr;
	word offset = registers[7];
	instr = 010102; memcpy(memory + offset, &instr, sizeof(word)); offset += 2;
}

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
	std::ifstream file("program.h", std::ios::ate);
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
	offset = 0100000;
	for (int i = 0; i < 100; i++) {
		printf("%c", *(memory+offset));
		offset += 8;
	}

	// Read image
	std::ifstream image("..\\PdpEmulator\\image.bmp", std::ios::binary | std::ios::ate);
	std::streamsize sizeImage = file.tellg();
	image.seekg(54, std::ios::beg);

	if (image.read(memory + 0110000, sizeImage))
	{
		std::cout << "Read image!\n";
	}
}

int PdpEmulator::Check(int val) {
	return 2;
}

__declspec(dllexport) wchar_t** __stdcall PdpEmulator::GetData() {
	wchar_t** wct = new wchar_t*[2];
	wct[0] = L"Awant begin";
	wct[1] = L"Awant end";
	return wct;
}