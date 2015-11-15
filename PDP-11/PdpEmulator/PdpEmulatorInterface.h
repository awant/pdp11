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
	PDP_EMU_API bool PerformStep();
	PDP_EMU_API void GetVideoBuffer(char * buffer);
	PDP_EMU_API void GetCurrentInstruction(char * buffer);
	PDP_EMU_API void GetAllInstructions(char ** buffer);
	PDP_EMU_API void GetRegisters(int * buffer);
	PDP_EMU_API byte GetFlags();
	PDP_EMU_API int GetInstructionNumber();
	// can be used for checking
	PDP_EMU_API void PerformProgram();
}

#endif // _PDP_EMULATOR_INTERFACE_H_