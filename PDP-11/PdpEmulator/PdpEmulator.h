#ifndef _PDP_EMULATOR_H_
#define _PDP_EMULATOR_H_

#include <string.h>
#include "Singleton.h"
#include "PdpConstants.h"
#include "Disassembler.h"
#include "InstructionSet.h"

class PdpEmulator : public Singleton<PdpEmulator> {
public:
	PdpEmulator();
	~PdpEmulator();
	word GetWord(void * pointer) { return *(word*)pointer; }
	void SetWord(void * fromPointer, void * toPointer) { memcpy(toPointer, fromPointer, sizeof(word)); }
	byte GetByte(void * pointer) { return *(byte*)pointer; }
	void SetByte(void * fromPointer, void * toPointer) { memcpy(toPointer, fromPointer, sizeof(byte)); }
	bool GetFlagC() { return getFlagBit(0); }
	void SetFlagC(bool value) { setFlagBit(0, value); }
	bool GetFlagV() { return getFlagBit(0); }
	void SetFlagV(bool value) { setFlagBit(0, value); }
	bool GetFlagZ() { return getFlagBit(0); }
	void SetFlagZ(bool value) { setFlagBit(0, value); }
	bool GetFlagN() { return getFlagBit(0); }
	void SetFlagN(bool value) { setFlagBit(0, value); }
	void SetRegisterValue(int number, word value) { registers[number] = value; }
	word GetRegisterValue(int number) { return registers[number]; }
	word * GetRegister(int number) { return &registers[number]; }
	word * GetWordFromMemory(word offset) { return (word*)(memory + offset); }
	void SetWordToMemory(word offset, void * value) { memcpy(memory + offset, value, sizeof(word)); }
	byte * GetByteFromMemory(word offset) { return (memory + offset); }
	void SetByteToMemory(word offset, void * value) { memcpy(memory + offset, value, sizeof(byte)); }
	std::function<void()> GetInstruction(int number);
	std::string GetInstructionString(int number);


	int Check(int val);
	__declspec(dllexport) wchar_t** __stdcall PdpEmulator::GetData();

private:
	bool getFlagBit(int n) { return (processorStatusWord >> n) & 1; }
	void setFlagBit(int n, bool value) { processorStatusWord = (processorStatusWord | (1 << n)) & (~((1 << n) ^ (value << n))); }
	void loadProgram();

	InstructionSet * instructionSet;
	Disassembler * disasm;
	word registers[8];
	byte memory[0177777];
	byte processorStatusWord; // IIITNZVC
};

#endif // _PDP_EMULATOR_H_