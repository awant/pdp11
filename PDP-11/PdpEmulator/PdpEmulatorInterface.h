#ifdef PDPEMULATOR_EXPORTS
#define PDP_EMU_API __declspec(dllexport) 
#else
#define PDP_EMU_API __declspec(dllimport) 
#endif

#include <vector>

extern "C"
{
	PDP_EMU_API BOOL pdpInitializer();

	PDP_EMU_API char** getAllInstructions();
	PDP_EMU_API int getIndexOfCurrentInstruction();
	PDP_EMU_API int* getRegisters();
	PDP_EMU_API int* getStatusFlags();
}