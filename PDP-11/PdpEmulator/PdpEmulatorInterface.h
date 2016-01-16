#ifndef _PDP_EMULATOR_INTERFACE_H_
#define _PDP_EMULATOR_INTERFACE_H_

#ifdef PDPEMULATOR_EXPORTS
#define PDP_EMU_API __declspec(dllexport)
#else
#define PDP_EMU_API __declspec(dllimport)
#endif

#include "PdpConstants.h"

extern "C"
{
	PDP_EMU_API int PerformStep();
	PDP_EMU_API void ResetProgram();
	PDP_EMU_API void GetVideoBuffer(char * buffer);
	PDP_EMU_API void GetCurrentInstruction(char * buffer);
	PDP_EMU_API void GetNextInstruction(char * buffer);
	PDP_EMU_API void GetRegisters(int * buffer);
	PDP_EMU_API byte GetFlags();
	// can be used for checking
	PDP_EMU_API void PerformProgram();
}

const char * getInstruction(offset_t offset);

#endif // _PDP_EMULATOR_INTERFACE_H_