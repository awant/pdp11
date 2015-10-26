#ifndef _DISASSEMBLER_H_
#define _DISASSEMBLER_H_

#include <string>
#include "PdpConstants.h"

class Disassembler {
public:
	Disassembler();
	~Disassembler();
	std::string GetInstructionString(int number);

private:
	std::string getOperandString(word mode, word number);

	std::string	name[0177777];
	int			numOperands[0177777];
};

#endif // _DISASSEMBLER_H_