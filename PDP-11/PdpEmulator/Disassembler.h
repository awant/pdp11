#ifndef _DISASSEMBLER_H_
#define _DISASSEMBLER_H_

#include <string>
#include <map>
#include "PdpConstants.h"

class PdpEmulator;

class Disassembler {
public:
	Disassembler(PdpEmulator * emulator);
	~Disassembler();
	std::string GetInstructionString(uword number, offset_t pc);

private:
	std::string getOperandString(word mode, word number);

	std::string					name[0177777];
	int							numOperands[0177777];
	std::map<std::string, int>	sizeOfOneOperand;
	PdpEmulator *				pdpEmulator;
};

#endif // _DISASSEMBLER_H_