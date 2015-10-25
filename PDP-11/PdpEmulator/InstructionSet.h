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

	void MOV(void * src, void * dst);
	void MOVB(void * src, void * dst);
	void ADD(void * src, void * dst);
	void SUB(void * src, void * dst);
	void SOB(void * src, void * dst);
	void CMP(void * src, void * dst);
	void JMP(void * dst);
	void BR(int instr);
	void BGE(int instr);
	void BEQ(int instr);
	void INC(void * dest);
	void DEC(void * dest);

private:
	void * getBackOperand(word instruction, bool isByte);
	void * getFrontOperand(word instruction, bool isByte);
	void * getBackOperandRegister(word instruction, bool isByte);
	void * getFrontOperandRegister(word instruction, bool isByte);
	void * getBackOperandConstant(word instruction, bool isByte);
	void * chooseAddressByMode(word mode, word number, bool isByte);

	std::function<void()>	table[0177777];
	std::string				names[0177777];
	PdpEmulator *			pdpEmulator;
};

#endif // _INSTRUCTION_SET_H_