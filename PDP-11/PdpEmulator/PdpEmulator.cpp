#include "stdafx.h"
#include "PdpEmulator.h"
#include "PdpConstants.h"
#include "InstructionSet.h"

PdpEmulator::PdpEmulator() {
	instructionSet = new InstructionSet(this);

	for (int i = 0; i < 8; i++)
		registers[i] = 0;
	processorStatusWord = 0;
}

PdpEmulator::~PdpEmulator() {
	if (instructionSet)
		delete instructionSet;
	instructionSet = nullptr;
}

int PdpEmulator::Check(int num) {
	for (int i = 0; i < 8; i++)
		registers[i] = i;
	instructionSet->GetInstruction(num)();
	auto ret = registers[2];
	return ret;
}

int PdpEmulator::GetTwoBytes(void * pointer) {
	int number = *(int*)pointer;
	return (((number >> 8) & 0xff) << 8) + (number & 0xff) - ((number >> 15) & 1) * (1 << 16);
}

int PdpEmulator::GetOneByte(void * pointer) {
	int number = *(int*)pointer;
	return (number & 0xff) - ((number >> 7) & 1) * (1 << 8);
}

void PdpEmulator::SetTwoBytes(void * fromPointer, void * toPointer) {
	int fromNumber = *(int*)fromPointer;
	int toNumber = *(int*)toPointer;
	for (int i = 0; i < 16; i++) {
		bool value = (fromNumber >> i) & 1;
		toNumber = (toNumber | (1 << i)) & (~((1 << i) ^ (value << i)));
	}
	*(int*)toPointer = toNumber;
}

void PdpEmulator::SetOneByte(void * fromPointer, void * toPointer) {
	int fromNumber = *(int*)fromPointer;
	int toNumber = *(int*)toPointer;
	for (int i = 0; i < 8; i++) {
		bool value = (fromNumber >> i) & 1;
		toNumber = (toNumber | (1 << i)) & (~((1 << i) ^ (value << i)));
	}
	*(int*)toPointer = toNumber;
}

