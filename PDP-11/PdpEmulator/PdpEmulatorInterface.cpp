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
