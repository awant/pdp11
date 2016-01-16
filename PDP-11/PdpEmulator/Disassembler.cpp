#include "stdafx.h"
#include "Disassembler.h"
#include "PdpConstants.h"
#include "PdpEmulator.h"

Disassembler::Disassembler(PdpEmulator * emulator) {
	pdpEmulator = emulator;

	for (int i = 0; i < 0177777; i++)		{ name[i] = "NULL"; numOperands[i] = 0; }

	for (int i = 0; i <= 0; i++)			{ name[i] = "HALT"; numOperands[i] = 0; }
	for (int i = 010000; i < 017777; i++)   { name[i] = "MOV"; numOperands[i] = 2; }
	for (int i = 0110000; i < 0117777; i++) { name[i] = "MOVB"; numOperands[i] = 2; }
	for (int i = 060000; i < 067777; i++)   { name[i] = "ADD"; numOperands[i] = 2; }
	for (int i = 0160000; i < 0167777; i++) { name[i] = "SUB"; numOperands[i] = 2; }
	for (int i = 077000; i < 077777; i++)   { name[i] = "SOB"; numOperands[i] = 2; }
	for (int i = 020000; i < 027777; i++)   { name[i] = "CMP"; numOperands[i] = 2; }
	for (int i = 0100; i < 0177; i++)		{ name[i] = "JMP"; numOperands[i] = 1; sizeOfOneOperand.insert(std::pair<std::string, int>(name[i], 6)); }
	for (int i = 0400; i < 0777; i++)		{ name[i] = "BR"; numOperands[i] = 1; sizeOfOneOperand.insert(std::pair<std::string, int>(name[i], 8)); }
	for (int i = 02000; i < 02377; i++)		{ name[i] = "BGE"; numOperands[i] = 1; sizeOfOneOperand.insert(std::pair<std::string, int>(name[i], 8)); }
	for (int i = 01400; i < 01777; i++)		{ name[i] = "BEQ"; numOperands[i] = 1; sizeOfOneOperand.insert(std::pair<std::string, int>(name[i], 8)); }
	for (int i = 05200; i < 05277; i++)		{ name[i] = "INC"; numOperands[i] = 1; sizeOfOneOperand.insert(std::pair<std::string, int>(name[i], 6)); }
	for (int i = 05300; i < 05377; i++)		{ name[i] = "DEC"; numOperands[i] = 1; sizeOfOneOperand.insert(std::pair<std::string, int>(name[i], 6)); }

}

Disassembler::~Disassembler() {

}

std::pair<std::string, int> Disassembler::GetInstructionString(uword number, offset_t pc) {
	std::string result = std::to_string(pc) + ":" + name[number] + " ";
	int numberOfUsedWords = 1;
	if (numOperands[number] == 2) {
		word srcMode = (number >> 9) & 07;
		word srcReg = (number >> 6) & 07;
		word dstMode = (number >> 3) & 07;
		word dstReg = number & 07;
		// looking for constants from memory: operand is 027 and it can only be source
		if (srcMode == 2 && srcReg == 7) {
			result += "#" + std::to_string(long long(*pdpEmulator->GetWordFromMemory(pc + 2)));
			numberOfUsedWords++;
		} else {
			result += getOperandString(srcMode, srcReg);
		}
		if (dstMode == 2 && dstReg == 7) {
			result += ", #" + std::to_string(long long(*pdpEmulator->GetWordFromMemory(pc + 2)));
			numberOfUsedWords++;
		} else {
			result += ", " + getOperandString(dstMode, dstReg);
		}
	}
	if (numOperands[number] == 1) {
		word dstMode, dstReg, offset;
		int operandSize = sizeOfOneOperand.at(name[number]);
		switch (operandSize) {
		case 6:
			dstMode = (number >> 3) & 07;
			dstReg = number & 07;
			result += getOperandString(dstMode, dstReg);
			break;
		case 8:
			offset = number & 0377;
			if (offset >= 0200)
				offset -= 0400;
			result += std::to_string(offset);
			break;
		default:
			break;
		}
	}
	return std::make_pair(result, numberOfUsedWords);
}

std::string Disassembler::getOperandString(word mode, word number) {
	switch (mode) {
	case 0:
		return "R" + std::to_string(number);
		break;
	case 1:
		return "@R" + std::to_string(number);
		break;
	case 2:
		return "@R" + std::to_string(number) + "++";
		break;
	case 3:
		return "[@R" + std::to_string(number) + "++]";
		break;
	case 4:
		return "--@R" + std::to_string(number);
		break;
	case 5:
		return "[--@R" + std::to_string(number) + "]";
		break;
	case 6:
		return "[R" + std::to_string(number) + "+[R7++]]";
		break;
	case 7:
		return "@[R" + std::to_string(number) + "+[R7++]]";
		break;
	default:
		break;
	}
}