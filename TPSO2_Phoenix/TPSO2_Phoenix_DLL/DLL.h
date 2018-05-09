#include <windows.h>
#include <tchar.h>

#ifdef DLL_EXPORTS
#define TPSO2_Phoenix_DLL_IMP_API __declspec(dllexport)
#else
#define TPSO2_Phoenix_DLL_IMP_API __declspec(dllimport)
#endif
extern "C"
{
	//Variável global da DLL
	extern TPSO2_Phoenix_DLL_IMP_API int nDLL;

	//Funções a serem exportadas/importadas
}