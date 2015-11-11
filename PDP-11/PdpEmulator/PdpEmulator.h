#ifndef _PDP_EMULATOR_H_
#define _PDP_EMULATOR_H_

#include <string.h>
#include <cstdio>
#include <fstream>
#include <iostream>
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
	byte GetFlagsByte() { return processorStatusWord; }
	bool GetFlagC() { return getFlagBit(0); }
	void SetFlagC(bool value) { setFlagBit(0, value); }
	bool GetFlagV() { return getFlagBit(1); }
	void SetFlagV(bool value) { setFlagBit(1, value); }
	bool GetFlagZ() { return getFlagBit(2); }
	void SetFlagZ(bool value) { setFlagBit(2, value); }
	bool GetFlagN() { return getFlagBit(3); }
	void SetFlagN(bool value) { setFlagBit(3, value); }
	void SetRegisterValue(int number, word value) { registers[number] = value; }
	word GetRegisterValue(int number) { return registers[number]; }
	word * GetRegister(int number) { return &registers[number]; }
	word * GetWordFromMemory(offset_t offset) { return (word*)(memory + offset); }
	void SetWordToMemory(offset_t offset, void * value) { memcpy(memory + offset, value, sizeof(word)); }
	byte * GetByteFromMemory(offset_t offset) { return (memory + offset); }
	void SetByteToMemory(offset_t offset, void * value) { memcpy(memory + offset, value, sizeof(byte)); }
	std::function<void()> GetInstruction(uword number);
	std::string GetInstructionString(uword number, offset_t pc);

	void PerformCurrentInstruction();
	std::string GetCurrentInstruction();
	std::string GetCurrentInstructionAndStep();

	int Check(int val);
	__declspec(dllexport) wchar_t** __stdcall PdpEmulator::GetData();

private:
	bool getFlagBit(int n) { return (processorStatusWord >> n) & 1; }
	void setFlagBit(int n, bool value) { processorStatusWord = (processorStatusWord | (1 << n)) & (~((1 << n) ^ (value << n))); }
	void initProgram();
	void loadProgram();

	InstructionSet * instructionSet;
	Disassembler * disasm;
	word registers[8];
	byte memory[0177777];
	byte processorStatusWord; // IIITNZVC
};

#endif // _PDP_EMULATOR_H_