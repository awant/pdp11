#ifndef _PDP_CONSTANTS_H_
#define _PDP_CONSTANTS_H_

typedef char byte;
typedef short word;
typedef unsigned short offset_t;
typedef unsigned short uword;

class PdpConstants
{
public:
	static const word MostPositiveWordUnsigned = 0177777;
	static const word MostPositiveWord = 077777;
	static const word MostNegativeWord = 0100000;
	static const byte MostPositiveByteUnsigned = 0377;
	static const byte MostPositiveByte = 0177;
	static const byte MostNegativeByte = 0200;
	static const offset_t StartOfVideoBuffer = 040000;
	static const offset_t SizeOfVideoBuffer = 512 * 256 / 8;
	static const word ProgramCounterBegin = 0100000;
	static const word StackPointerBegin = 0100000;
};

#endif // _PDP_CONSTANTS_H_s