#include <windows.h>
#include <tchar.h>

#ifdef DLL_EXPORTS							// modo standard de criar macros que tornam a exporta��o fun��es e vari�veis mais simples.
#define DLL_IMP_API _declspec(dllexport)	// Todos os ficheiros neste projeto DLL compilados com o s�mbolo DLL_IMP_EXPORTS definido
#else
#define DLL_IMP_API _declspec(dllimport)
#endif

extern C
{
	//Vari�vel global da DLL
	extern DLL_IMP_API int nDLL;

	//Fun��es a serem exportadas/importadas
}