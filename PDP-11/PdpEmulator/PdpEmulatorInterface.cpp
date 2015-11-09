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
	offset_t startOfVideoBuffer = 0110000;
	offset_t sizeOfVideoBuffer = 512 * 256 / 8;
	auto emu = PdpEmulator::IPtr();
	memcpy(buffer, emu->GetByteFromMemory(startOfVideoBuffer), sizeOfVideoBuffer);
}