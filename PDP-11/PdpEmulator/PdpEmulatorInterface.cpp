#include "stdafx.h"
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
	/*offset_t startOfVideoBuffer = 040000;
	offset_t sizeOfVideoBuffer = 0100000 - 040000;
	memcpy(buffer, PdpEmulator::I().GetByteFromMemory(startOfVideoBuffer), sizeOfVideoBuffer);*/

	int n = 512 * 256;
	while (n-- > 0) {
		int x = int(float(rand()) / 32767 * 7) + 1;
		buffer[n] = (1 << x) - 1;
	}
}