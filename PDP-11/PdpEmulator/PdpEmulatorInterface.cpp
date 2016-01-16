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

std::string getInstruction(offset_t offset)
{
	auto emu = PdpEmulator::IPtr();
	word instrCode = *emu->GetWordFromMemory(offset);
	auto instructionAndOffset = emu->GetInstructionString(instrCode, offset);
	auto instrString = instructionAndOffset.first;
	auto offsetToNext = instructionAndOffset.second * 2; // words -> bytes

	instrString += ";";
	instrCode = *emu->GetWordFromMemory(offset + offsetToNext);
	instructionAndOffset = emu->GetInstructionString(instrCode, offset + offsetToNext);
	instrString += instructionAndOffset.first;
	offsetToNext += instructionAndOffset.second * 2; // words -> bytes

	return instrString;
}

void GetCurrentInstruction(char * buffer)
{
	auto emu = PdpEmulator::IPtr();
	offset_t pc = emu->GetRegisterValue(7);
	auto instrString = getInstruction(pc);
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