#ifndef _INSTRUCTION_SET_H_
#define _INSTRUCTION_SET_H_

#include <functional>
#include <assert.h>
#include "PdpConstants.h"

class PdpEmulator;

class InstructionSet {
public:
	InstructionSet(PdpEmulator * emulator);
	~InstructionSet();
	std::function<void()> GetInstruction(int number) { return table[number]; }

	void FreeInstruction() { assert(0); }

	void MOV(int instr);
	void MOVB(int instr);
	void ADD(int instr);
	void SUB(int instr);
	void SOB(int instr);
	void CMP(int instr);
	void JMP(int instr);
	void BR(int instr);
	void BGE(int instr);
	void BEQ(int instr);
	void INC(int instr);
	void DEC(int instr);

private:
	word * getBackOperand(word instruction, bool isByte);
	word * getFrontOperand(word instruction, bool isByte);
	word * getBackOperandRegister(word instruction, bool isByte);
	word * getFrontOperandRegister(word instruction, bool isByte);
	word * getBackOperandConstant(word instruction, bool isByte);
	word * chooseAddressByMode(word mode, word number, bool isByte);

	std::function<void()>	table[0177777];
	PdpEmulator *			pdpEmulator;
};

#endif // _INSTRUCTION_SET_H_