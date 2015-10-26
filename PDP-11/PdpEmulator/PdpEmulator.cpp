#include "stdafx.h"
#include "PdpEmulator.h"
#include "PdpConstants.h"
#include "InstructionSet.h"

PdpEmulator::PdpEmulator() {
	instructionSet = new InstructionSet(this);

	for (int i = 0; i < 6; i++)
		registers[i] = 0;
	registers[6] = 020000;
	registers[7] = 040000;
	processorStatusWord = 0;

	loadProgram();
}

PdpEmulator::~PdpEmulator() {
	if (instructionSet)	delete instructionSet;	 instructionSet = nullptr;
}

std::function<void()> PdpEmulator::GetInstruction(int number) {
	return instructionSet->GetInstruction(number);
}

std::string PdpEmulator::GetInstructionString(int number) {
	return disasm->GetInstructionString(number);
}

void PdpEmulator::loadProgram() {
	word instr;
	word offset = registers[7];
	instr = 010102; memcpy(memory + offset, &instr, sizeof(word)); offset += 2;
}

int PdpEmulator::Check(int val) {
	return 2;
}

__declspec(dllexport) wchar_t** __stdcall PdpEmulator::GetData() {
	wchar_t** wct = new wchar_t*[2];
	wct[0] = L"Awant begin";
	wct[1] = L"Awant end";
	return wct;
}