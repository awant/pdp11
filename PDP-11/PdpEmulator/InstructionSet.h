#ifndef _INSTRUCTION_SET_H_
#define _INSTRUCTION_SET_H_

#include <functional>

class PdpEmulator;

class InstructionSet {
public:
	InstructionSet(PdpEmulator * emulator);
	~InstructionSet();
	std::function<void()> GetInstruction(int number) { return table[number]; }

	void FreeInstruction() {}
	void Add(void * src, void * dest);
	void Move(void * src, void * dest);

private:
	void * getBackOperand(int instruction, bool isByte);
	void * getFrontOperand(int instruction, bool isByte);
	void * getBackOperandRegister(int instruction, bool isByte);
	void * getFrontOperandRegister(int instruction, bool isByte);
	void * chooseAddressByMode(int mode, int number, bool isByte);

	std::function<void()> table[0177777];
	PdpEmulator * pdpEmulator;
};

#endif // _INSTRUCTION_SET_H_