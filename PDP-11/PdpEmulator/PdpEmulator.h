#ifndef _PDP_EMULATOR_H_
#define _PDP_EMULATOR_H_

#include "Singleton.h"

class InstructionSet;

class PdpEmulator : public Singleton<PdpEmulator> {
public:
	PdpEmulator();
	~PdpEmulator();
	int GetTwoBytes(void * pointer);
	void SetTwoBytes(void * fromPointer, void * toPointer);
	int GetOneByte(void * pointer);
	void SetOneByte(void * fromPointer, void * toPointer);
	bool GetFlagC() { return getFlagBit(0); }
	void SetFlagC(bool value) { setFlagBit(0, value); }
	bool GetFlagV() { return getFlagBit(0); }
	void SetFlagV(bool value) { setFlagBit(0, value); }
	bool GetFlagZ() { return getFlagBit(0); }
	void SetFlagZ(bool value) { setFlagBit(0, value); }
	bool GetFlagN() { return getFlagBit(0); }
	void SetFlagN(bool value) { setFlagBit(0, value); }
	void SetRegisterValue(int number, int value) { registers[number] = value; }
	int GetRegisterValue(int number) { return registers[number]; }
	int * GetRegister(int number) { return &registers[number]; }
	int GetFromMemory(int offset) { return 3;  }
	void SetToMemory(int offset, void * value) {}

	int Check(int num);

private:
	bool getFlagBit(int n) { return (processorStatusWord >> n) & 1; }
	void setFlagBit(int n, bool value) { processorStatusWord = (processorStatusWord | (1 << n)) & (~((1 << n) ^ (value << n))); }

	InstructionSet * instructionSet;
	int registers[8];
	BYTE memory[2];
	BYTE processorStatusWord; // IIITNZVC
};

#endif // _PDP_EMULATOR_H_