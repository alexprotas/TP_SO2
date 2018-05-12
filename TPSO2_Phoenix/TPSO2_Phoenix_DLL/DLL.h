#include <windows.h>
#include <tchar.h>
#include <string>

#define OPNAME_SZ 30
#define MSGTEXT_SZ 75
#define MSGBUFSIZE sizeof(Shared_MSG)
#define MUTEX_NAME TEXT("RWMUTEX")

TCHAR szName[] = TEXT("fmMSGSpace");

// estrutura de dados para conter uma msg
typedef struct _MSG {
	unsigned msgnum;
	TCHAR szOP[OPNAME_SZ];
	TCHAR szMessage[MSGTEXT_SZ];
}Shared_MSG;

// a zona de memoria partilhada ira conter uma unica msg
// existira uma unica vista dessa zona, que coincidira com a totalidade da memoria partilhada
typedef struct _ControlData {
	HANDLE hMapFile;
	Shared_MSG * shared;
	int ThreadDeveContinuar;
	TCHAR MyName[OPNAME_SZ];
	HANDLE hRWMutex;
}ContrData;



#ifdef TPSO2_Phoenix_EXPORTS
#define TPSO2_Phoenix_DLL_IMP_API __declspec(dllexport)
#else
#define TPSO2_Phoenix_DLL_IMP_API __declspec(dllimport)
#endif



extern "C"
{
	//Variável global da DLL
	extern TPSO2_Phoenix_DLL_IMP_API int nDLL;

	//Funções a serem exportadas/importadas
	TPSO2_Phoenix_DLL_IMP_API void readMSGGateway(ContrData * pcdata, Shared_MSG * msg);
	TPSO2_Phoenix_DLL_IMP_API void writeMSGGateway(ContrData * pcdata, TCHAR * msgtext);
	TPSO2_Phoenix_DLL_IMP_API void readMSGServer(ContrData * pcdata, Shared_MSG * msg);
	TPSO2_Phoenix_DLL_IMP_API void writeMSGServer(ContrData * pcdata, TCHAR * msgtext);
	TPSO2_Phoenix_DLL_IMP_API unsigned peekMSG(ContrData * pcdata);
}