#ifndef _PDP_EMULATOR_INTERFACE_H_
#define _PDP_EMULATOR_INTERFACE_H_

#ifdef PDPEMULATOR_EXPORTS
#define PDP_EMU_API __declspec(dllexport)
#else
#define PDP_EMU_API __declspec(dllimport)
#endif

extern "C"
{
	/*PDP_EMU_API BOOL pdpInitializer();

	PDP_EMU_API char** getAllInstructions();
	PDP_EMU_API int getIndexOfCurrentInstruction();
	PDP_EMU_API int* getRegisters();
	PDP_EMU_API int* getStatusFlags();*/

	PDP_EMU_API void GetVideoBuffer(char * buffer);
	PDP_EMU_API int Check();
}

#endif // _PDP_EMULATOR_INTERFACE_H_