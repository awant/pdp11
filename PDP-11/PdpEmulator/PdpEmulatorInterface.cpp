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

void GetCurrentInstruction(char * buffer)
{
	auto emu = PdpEmulator::IPtr();
	auto string = emu->GetCurrentInstruction();
	auto cString = string.c_str();
	memcpy(buffer, cString, string.length() + 1);
}

void GetAllInstructions(char ** buffer)
{
	auto emu = PdpEmulator::IPtr();
	bool isEnd = false;
	int i = 0;
	while (!isEnd) {
		auto string = emu->GetCurrentInstruction();
		auto cString = string.c_str();
		memcpy(buffer[i++], cString, string.length() + 1);
		isEnd = emu->PerformCurrentInstruction();
	}
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

int GetInstructionNumber()
{
	auto emu = PdpEmulator::IPtr();
	bool isEnd = false;
	int num = 0;
	while (!isEnd) {
		num++;
		isEnd = emu->PerformCurrentInstruction();
	}
	return num;
}

bool PerformStep()
{
	auto emu = PdpEmulator::IPtr();
	return emu->PerformCurrentInstruction();
}

void PerformProgram() {
	auto emu = PdpEmulator::IPtr();
	bool isEnd = false;
	while (!isEnd) {
		isEnd = emu->PerformCurrentInstruction();
	}
}