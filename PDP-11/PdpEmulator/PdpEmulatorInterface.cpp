#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "PdpEmulatorInterface.h"
#include "PdpEmulator.h"

int Sum(int a, int b)
{
	// my Emulator
	return a + b;
}

int Sub(int a, int b)
{
	return a - b;
}

int Check()
{
	return PdpEmulator::I().Check(010102);
}

void GetVideoBuffer(char * buffer)
{
	offset_t startOfVideoBuffer = 040000;
	offset_t sizeOfVideoBuffer = 512 * 256 / 8;
	auto emu = PdpEmulator::IPtr();
	int num = 9;
	while (num-- > 0) {
		emu->PerformCurrentInstruction();
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