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
	std::function<bool()> GetInstruction(int number) { return table[number]; }

	bool FreeInstruction() { assert(0); return true; }

	bool HALT(int instr);
	bool MOV(int instr);
	bool MOVB(int instr);
	bool ADD(int instr);
	bool SUB(int instr);
	bool SOB(int instr);
	bool CMP(int instr);
	bool JMP(int instr);
	bool BR(int instr);
	bool BGE(int instr);
	bool BEQ(int instr);
	bool INC(int instr);
	bool DEC(int instr);

private:
	word * getBackOperand(word instruction, bool isByte);
	word * getFrontOperand(word instruction, bool isByte);
	word * getBackOperandRegister(word instruction, bool isByte);
	word * getFrontOperandRegister(word instruction, bool isByte);
	word * getBackOperandConstant(word instruction, bool isByte);
	word * chooseAddressByMode(word mode, word number, bool isByte);

	std::function<bool()>	table[0200000];
	PdpEmulator *			pdpEmulator;
};

#endif // _INSTRUCTION_SET_H_