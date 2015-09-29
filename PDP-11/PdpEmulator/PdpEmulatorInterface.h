#ifdef PDPEMULATOR_EXPORTS
#define PDP_EMU_API __declspec(dllexport) 
#else
#define PDP_EMU_API __declspec(dllimport) 
#endif

extern "C"
{
	PDP_EMU_API int Sum(int a, int b);
	PDP_EMU_API int Sub(int a, int b);
}