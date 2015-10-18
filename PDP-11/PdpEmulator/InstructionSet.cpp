#include "stdafx.h"
#include "InstructionSet.h"
#include "PdpEmulator.h"

InstructionSet::InstructionSet(PdpEmulator * emulator) {
	pdpEmulator = emulator;

	for (int i = 010000; i < 017777; i++)
		table[i] = std::bind(&InstructionSet::Move, this, getFrontOperand(i, false), getBackOperand(i, false));
	for (int i = 060000; i < 067777; i++)
		table[i] = std::bind(&InstructionSet::Add, this, getFrontOperand(i, false), getBackOperand(i, false));
}

InstructionSet::~InstructionSet() {
}

void InstructionSet::Move(void * src, void * dest) {
	auto srcValue = pdpEmulator->GetTwoBytes(src);
	pdpEmulator->SetTwoBytes(src, dest);
	pdpEmulator->SetFlagN(srcValue < 0);
	pdpEmulator->SetFlagZ(srcValue == 0);
	pdpEmulator->SetFlagV(0);
	// flagC not affected
}

void InstructionSet::Add(void * src, void * dest) {
	int srcValue = pdpEmulator->GetTwoBytes(src);
	int destValue = pdpEmulator->GetTwoBytes(dest);
	int result = (srcValue + destValue) % (1 << 16);
	pdpEmulator->SetTwoBytes(&result, dest);
	pdpEmulator->SetFlagN(result < 0);
	pdpEmulator->SetFlagZ(result == 0);
	// TODO: V and C flags
}

void * InstructionSet::chooseAddressByMode(int mode, int number, bool isByte) {
	int result, resultPtr, increment, decrement, pc, valueFromReg, valueFromMem;

	switch (mode) {
	case 0:
		return (void*)pdpEmulator->GetRegister(number);
		break;
	case 1:
		return (void*)pdpEmulator->GetRegisterValue(number);
		break;
	case 2:
		result = pdpEmulator->GetRegisterValue(number);
		increment = (number <= 5 && isByte) ? 1 : 2;
		pdpEmulator->SetRegisterValue(number, pdpEmulator->GetRegisterValue(number) + increment);
		return (void*)result;
		break;
	case 3:
		resultPtr = pdpEmulator->GetRegisterValue(number);
		pdpEmulator->SetRegisterValue(number, pdpEmulator->GetRegisterValue(number) + 2);
		return (void*)pdpEmulator->GetFromMemory(resultPtr);
		break;
	case 4:
		decrement = (number <= 5 && isByte) ? 1 : 2;
		pdpEmulator->SetRegisterValue(number, pdpEmulator->GetRegisterValue(number) - decrement);
		return (void*)pdpEmulator->GetRegisterValue(number);
		break;
	case 5:
		pdpEmulator->SetRegisterValue(number, pdpEmulator->GetRegisterValue(number) - 2);
		return (void*)pdpEmulator->GetFromMemory(pdpEmulator->GetRegisterValue(number));
		break;
	case 6:
		valueFromReg = pdpEmulator->GetRegisterValue(number);
		pc = pdpEmulator->GetRegisterValue(7);
		valueFromMem = pdpEmulator->GetFromMemory(pc);
		pdpEmulator->SetRegisterValue(7, pdpEmulator->GetRegisterValue(7) + 2);
		return (void*)(valueFromReg + valueFromMem);
		break;
	case 7:
		valueFromReg = pdpEmulator->GetRegisterValue(number);
		pc = pdpEmulator->GetRegisterValue(7);
		valueFromMem = pdpEmulator->GetFromMemory(pc);
		pdpEmulator->SetRegisterValue(7, pdpEmulator->GetRegisterValue(7) + 2);
		return (void*)pdpEmulator->GetFromMemory(valueFromReg + valueFromMem);
		break;
	default:
		break;
	}
	return nullptr;
}

void * InstructionSet::getFrontOperand(int instruction, bool isByte) {
	int number = (instruction >> 6) & 07;
	int mode = (instruction >> 9) & 07;
	return chooseAddressByMode(mode, number, isByte);
}

void * InstructionSet::getBackOperand(int instruction, bool isByte) {
	int number = instruction & 07;
	int mode = (instruction >> 3) & 07;
	return chooseAddressByMode(mode, number, isByte);
}

void * InstructionSet::getFrontOperandRegister(int instruction, bool isByte) {
	int number = (instruction >> 6) & 07;
	return chooseAddressByMode(0, number, isByte);
}

void * InstructionSet::getBackOperandRegister(int instruction, bool isByte) {
	int number = instruction & 07;
	return chooseAddressByMode(0, number, isByte);
}