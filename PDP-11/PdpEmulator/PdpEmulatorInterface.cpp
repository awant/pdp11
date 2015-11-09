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

	/*std::ifstream image("..\\PdpEmulator\\image.bmp", std::ios::binary | std::ios::ate);
	std::streamsize sizeImage = image.tellg();*/

	auto emu = PdpEmulator::IPtr();
	memcpy(buffer, emu->GetByteFromMemory(startOfVideoBuffer), sizeOfVideoBuffer);
	int i = 0;
	int n = 512 * 256 / 8;
	while (n-- > 0) {
		if (buffer[i] == 0) {
			buffer[i] = 1;
		}
		i++;
	}
}