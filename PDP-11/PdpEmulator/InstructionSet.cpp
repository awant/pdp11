#include "stdafx.h"
#include "InstructionSet.h"
#include "PdpEmulator.h"
#include "PdpConstants.h"

InstructionSet::InstructionSet(PdpEmulator * emulator) {
	pdpEmulator = emulator;

	for (int i = 0; i < 0177777; i++)		{ names[i] = "NULL"; table[i] = std::bind(&InstructionSet::FreeInstruction, this); }

	for (int i = 010000; i < 017777; i++)   { names[i] = "MOV";  table[i] = std::bind(&InstructionSet::MOV, this, getFrontOperand(i, false), getBackOperand(i, false)); }
	for (int i = 0110000; i < 0117777; i++) { names[i] = "MOVB"; table[i] = std::bind(&InstructionSet::MOVB, this, getFrontOperand(i, false), getBackOperand(i, false)); }
	for (int i = 060000; i < 067777; i++)   { names[i] = "ADD";  table[i] = std::bind(&InstructionSet::ADD, this, getFrontOperand(i, false), getBackOperand(i, false)); }
	for (int i = 0160000; i < 0167777; i++) { names[i] = "SUB";  table[i] = std::bind(&InstructionSet::SUB, this, getFrontOperand(i, false), getBackOperand(i, false)); }
	for (int i = 077000; i < 077777; i++)   { names[i] = "SOB";	 table[i] = std::bind(&InstructionSet::SOB, this, getFrontOperandRegister(i, false), getBackOperandConstant(i, false)); }
	for (int i = 020000; i < 027777; i++)   { names[i] = "CMP";	 table[i] = std::bind(&InstructionSet::CMP, this, getFrontOperand(i, false), getBackOperand(i, false)); }
	for (int i = 0100; i < 0177; i++)		{ names[i] = "JMP";	 table[i] = std::bind(&InstructionSet::JMP, this, getBackOperand(i, false)); }
	for (int i = 0400; i < 0777; i++)		{ names[i] = "BR";   table[i] = std::bind(&InstructionSet::BR, this, i); }
	for (int i = 02000; i < 02377; i++)		{ names[i] = "BGE";	 table[i] = std::bind(&InstructionSet::BGE, this, i); }
	for (int i = 01400; i < 01777; i++)		{ names[i] = "BEQ";	 table[i] = std::bind(&InstructionSet::BEQ, this, i); }
	for (int i = 05200; i < 05277; i++)		{ names[i] = "INC";	 table[i] = std::bind(&InstructionSet::INC, this, getBackOperand(i, false)); }
	for (int i = 05300; i < 05377; i++)		{ names[i] = "DEC";	 table[i] = std::bind(&InstructionSet::DEC, this, getBackOperand(i, false)); }

}

InstructionSet::~InstructionSet() {
}

void InstructionSet::MOV(void * src, void * dst) {
	word srcValue = pdpEmulator->GetWord(src);
	pdpEmulator->SetWord(src, dst);
	pdpEmulator->SetFlagN(srcValue < 0);
	pdpEmulator->SetFlagZ(srcValue == 0);
	pdpEmulator->SetFlagV(0);
	// flagC not affected
}

void InstructionSet::MOVB(void * src, void * dst) {
	byte srcValue = pdpEmulator->GetByte(src);
	pdpEmulator->SetByte(src, dst);
	pdpEmulator->SetFlagN(srcValue < 0);
	pdpEmulator->SetFlagZ(srcValue == 0);
	pdpEmulator->SetFlagV(0);
	// flagC not affected
}

void InstructionSet::ADD(void * src, void * dst) {
	word srcValue = pdpEmulator->GetWord(src);
	word dstValue = pdpEmulator->GetWord(dst);
	word result = srcValue + dstValue;
	pdpEmulator->SetWord(&result, dst);
	pdpEmulator->SetFlagN(result < 0);
	pdpEmulator->SetFlagZ(result == 0);
	pdpEmulator->SetFlagV((srcValue >> 15) == (dstValue >> 15) && (dstValue >> 15) != (result >> 15));
	pdpEmulator->SetFlagC(srcValue > PdpConstants::MostPositiveWordUnsigned - dstValue); // mb wrong
}

void InstructionSet::SUB(void * src, void * dst) {
	word srcValue = pdpEmulator->GetWord(src);
	word dstValue = pdpEmulator->GetWord(dst);
	word result = dstValue - srcValue;
	pdpEmulator->SetWord(&result, dst);
	pdpEmulator->SetFlagN(result < 0);
	pdpEmulator->SetFlagZ(result == 0);
	pdpEmulator->SetFlagV((srcValue >> 15) != (dstValue >> 15) && (srcValue >> 15) == (result >> 15));
	pdpEmulator->SetFlagC(dstValue + ~(srcValue) + 1 < (1 << 16));
}

void InstructionSet::SOB(void * src, void * dst) {
	word srcValue = pdpEmulator->GetWord(src);
	word result = srcValue - 1;
	if (result != 0)
	{
		word offset = (word)dst;
		pdpEmulator->SetRegisterValue(7, pdpEmulator->GetRegisterValue(7) - 2 * offset);
	}
	// flags not affected
}

void InstructionSet::CMP(void * src, void * dst) {
	word srcValue = pdpEmulator->GetWord(src);
	word dstValue = pdpEmulator->GetWord(dst);
	word result = srcValue - dstValue;
	pdpEmulator->SetFlagN(result < 0);
	pdpEmulator->SetFlagZ(result == 0);
	pdpEmulator->SetFlagV((srcValue >> 15) != (dstValue >> 15) && (dstValue >> 15) == (result >> 15));
	pdpEmulator->SetFlagC(srcValue + ~(dstValue) + 1 < (1 << 16));
}

void InstructionSet::JMP(void * dst) {
	word dstValue = pdpEmulator->GetWord(dst);
	pdpEmulator->SetRegisterValue(7, dstValue);
	// flags not affected
}

void InstructionSet::BR(int instr) {
	word offset = instr & 0377;
	pdpEmulator->SetRegisterValue(7, pdpEmulator->GetRegisterValue(7) + 2 * offset);
	// flags not affected
}

void InstructionSet::BGE(int instr) {
	word offset = instr & 0377;
	if ((pdpEmulator->GetFlagV() ^ pdpEmulator->GetFlagN()) == 0)
		pdpEmulator->SetRegisterValue(7, pdpEmulator->GetRegisterValue(7) + 2 * offset);
	// flags not affected
}

void InstructionSet::BEQ(int instr) {
	word offset = instr & 0377;
	if (pdpEmulator->GetFlagZ() == 1)
		pdpEmulator->SetRegisterValue(7, pdpEmulator->GetRegisterValue(7) + 2 * offset);
	// flags not affected
}

void InstructionSet::INC(void * dst) {
	word dstValue = pdpEmulator->GetWord(dst);
	word result = dstValue + 1;
	pdpEmulator->SetWord(&result, dst);
	pdpEmulator->SetFlagN(result < 0);
	pdpEmulator->SetFlagZ(result == 0);
	pdpEmulator->SetFlagV(dstValue == ((1 << 15) - 1));
	// flag C not affected
}

void InstructionSet::DEC(void * dst) {
	word dstValue = pdpEmulator->GetWord(dst);
	word result = dstValue - 1;
	pdpEmulator->SetWord(&result, dst);
	pdpEmulator->SetFlagN(result < 0);
	pdpEmulator->SetFlagZ(result == 0);
	pdpEmulator->SetFlagV(dstValue == (1 << 16));
	// flag C not affected
}

void * InstructionSet::chooseAddressByMode(word mode, word number, bool isByte) {
	word result, resultPtr, increment, decrement, pc, valueFromReg, valueFromMem;

	switch (mode) {
	case -1:
		return (void*)number;
		break;
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
		return (void*)pdpEmulator->GetWordFromMemory(resultPtr);
		break;
	case 4:
		decrement = (number <= 5 && isByte) ? 1 : 2;
		pdpEmulator->SetRegisterValue(number, pdpEmulator->GetRegisterValue(number) - decrement);
		return (void*)pdpEmulator->GetRegisterValue(number);
		break;
	case 5:
		pdpEmulator->SetRegisterValue(number, pdpEmulator->GetRegisterValue(number) - 2);
		return (void*)pdpEmulator->GetWordFromMemory(pdpEmulator->GetRegisterValue(number));
		break;
	case 6:
		valueFromReg = pdpEmulator->GetRegisterValue(number);
		pc = pdpEmulator->GetRegisterValue(7);
		valueFromMem = pdpEmulator->GetWordFromMemory(pc);
		pdpEmulator->SetRegisterValue(7, pdpEmulator->GetRegisterValue(7) + 2);
		return (void*)(valueFromReg + valueFromMem);
		break;
	case 7:
		valueFromReg = pdpEmulator->GetRegisterValue(number);
		pc = pdpEmulator->GetRegisterValue(7);
		valueFromMem = pdpEmulator->GetWordFromMemory(pc);
		pdpEmulator->SetRegisterValue(7, pdpEmulator->GetRegisterValue(7) + 2);
		return (void*)pdpEmulator->GetWordFromMemory(valueFromReg + valueFromMem);
		break;
	default:
		break;
	}
	return nullptr;
}

void * InstructionSet::getFrontOperand(word instruction, bool isByte) {
	word number = (instruction >> 6) & 07;
	word mode = (instruction >> 9) & 07;
	return chooseAddressByMode(mode, number, isByte);
}

void * InstructionSet::getBackOperand(word instruction, bool isByte) {
	word number = instruction & 07;
	word mode = (instruction >> 3) & 07;
	return chooseAddressByMode(mode, number, isByte);
}

void * InstructionSet::getFrontOperandRegister(word instruction, bool isByte) {
	word number = (instruction >> 6) & 07;
	return chooseAddressByMode(0, number, isByte);
}

void * InstructionSet::getBackOperandRegister(word instruction, bool isByte) {
	word number = instruction & 07;
	return chooseAddressByMode(0, number, isByte);
}

void * InstructionSet::getBackOperandConstant(word instruction, bool isByte) {
	int number = instruction & 077;
	return chooseAddressByMode(-1, number, isByte);
}