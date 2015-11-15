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
	int num = 0;
	bool isEnd = false;
	while (!isEnd) {
		isEnd = emu->PerformCurrentInstruction();
	}
	memcpy(buffer, emu->GetByteFromMemory(startOfVideoBuffer), sizeOfVideoBuffer);
}

void GetCurrentInstruction(char * buffer)
{
	auto emu = PdpEmulator::IPtr();
	auto string = emu->GetCurrentInstruction();
	auto cString = string.c_str();
	memcpy(buffer, cString, string.length() + 1);
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

bool PerformStep()
{
	auto emu = PdpEmulator::IPtr();
	return emu->PerformCurrentInstruction();
}