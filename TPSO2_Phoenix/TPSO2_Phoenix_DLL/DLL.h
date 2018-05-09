#include <windows.h>
#include <tchar.h>

#ifdef DLL_EXPORTS							// modo standard de criar macros que tornam a exportação funções e variáveis mais simples.
#define DLL_IMP_API _declspec(dllexport)	// Todos os ficheiros neste projeto DLL compilados com o símbolo DLL_IMP_EXPORTS definido
#else
#define DLL_IMP_API _declspec(dllimport)
#endif

extern C
{
	//Variável global da DLL
	extern DLL_IMP_API int nDLL;

	//Funções a serem exportadas/importadas
}