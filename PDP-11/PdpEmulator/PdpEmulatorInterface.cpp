#include "stdafx.h"
#include <fstream>
#include "PdpEmulatorInterface.h"
#include "PdpEmulator.h"
#include "PdpConstants.h"


void GetVideoBuffer(char * buffer)
{
	auto emu = PdpEmulator::IPtr();
	memcpy(buffer, emu->GetByteFromMemory(PdpConstants::SizeOfVideoBuffer), PdpConstants::SizeOfVideoBuffer);
}

void GetCurrentInstruction(char * buffer)
{
	auto emu = PdpEmulator::IPtr();
	offset_t pc = emu->GetRegisterValue(7);
	word instrCode = *emu->GetWordFromMemory(pc);
	auto instrString = emu->GetInstructionString(instrCode, pc).first;
	auto instrStringC = instrString.c_str();
	memcpy(buffer, instrStringC, strlen(instrStringC) + 1);
}

void GetInstructions(int number, char * buffer)
{
	auto emu = PdpEmulator::IPtr();
	offset_t pc = emu->GetRegisterValue(7);
	std::string instrString = "";
	int offsetToNextInstruction = 0;
	while (number-- > 0) {
		word instrCode = *emu->GetWordFromMemory(pc + offsetToNextInstruction);
		auto instructionAndOffset = emu->GetInstructionString(instrCode, pc + offsetToNextInstruction);
		instrString += instructionAndOffset.first;
		offsetToNextInstruction += instructionAndOffset.second * 2;
		if (number != 0) instrString += ";";
	}
	auto instrStringC = instrString.c_str();
	memcpy(buffer, instrStringC, strlen(instrStringC) + 1);
}

void GetRegisters(int * buffer)
{
	auto emu = PdpEmulator::IPtr();
	for (int i = 0; i < 8; i++)
		buffer[i] = emu->GetRegisterValue(i);
}

byte GetFlags()
{
	auto emu = PdpEmulator::IPtr();
	return emu->GetFlagsByte();
}

int PerformStep()
{
	auto emu = PdpEmulator::IPtr();
	return emu->PerformCurrentInstruction();
}

void ResetProgram()
{
	PdpEmulator::destroyInstance();
}

void PerformProgram() {
	PdpEmulator::destroyInstance();
	auto emu = PdpEmulator::IPtr();
	bool isEnd = false;
	while (!isEnd) {
		isEnd = emu->PerformCurrentInstruction();
	}
}