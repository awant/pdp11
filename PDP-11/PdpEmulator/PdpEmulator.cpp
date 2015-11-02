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

	loadProgram();
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

unsigned char* readBMP(char* filename)
{
	int i;
	FILE* f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	return data;
}

void PdpEmulator::initProgram() {
	// Read program
	std::ifstream file("program.h", std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	if (file.read(memory, size))
	{
		std::cout << "Read file!\n";
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