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

void PdpEmulator::loadProgram() {
	word instr;
	word offset = registers[7];
	instr = 010102; memcpy(memory + offset, &instr, sizeof(word)); offset += 2;
}

int PdpEmulator::Check(int val) {
	GetInstructionSet()->GetInstruction(val)();
	return 2;
}