#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "PdpEmulatorInterface.h"
#include "PdpEmulator.h"

void GetVideoBuffer(char * buffer)
{
	offset_t startOfVideoBuffer = 040000;
	offset_t sizeOfVideoBuffer = 512 * 256 / 8;
	auto emu = PdpEmulator::IPtr();
	memcpy(buffer, emu->GetByteFromMemory(startOfVideoBuffer), sizeOfVideoBuffer);
}

const char * getInstruction(offset_t offset)
{
	auto emu = PdpEmulator::IPtr();
	auto instrCode = *emu->GetWordFromMemory(offset);
	auto instrString = emu->GetInstructionString(instrCode, offset);
	return instrString.c_str();
}

void GetCurrentInstruction(char * buffer)
{
	auto emu = PdpEmulator::IPtr();
	auto pc = emu->GetRegisterValue(7);
	auto instrString = getInstruction(pc);
	memcpy(buffer, instrString, strlen(instrString) + 1);
}

void GetNextInstruction(char * buffer)
{
	auto emu = PdpEmulator::IPtr();
	auto pc = emu->GetRegisterValue(7);
	// need to calculate step: 1 or 2 words

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