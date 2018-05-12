// Trata funcoes que lidem com o Buffer
// Vai ser lida e escrita pelo Gateway -> thread que lide com msgs recebidas do gateway -> thread que a envie para o server?
	// Vai receber MSGs de Clientes (escrita pelo Gateway)
		// dados de login?
		// 
// Vai ser lida e escrita pelo Server -> thread que lide com msgs recebidas do server -> thread que as envie para o(s) cliente(s)?
/*
6 FUNCOES

	3 ZONAS DE MEMORIA PARTILHADA

	COMUNICACAO GATEWAY - SERVIDOR
		FUNCOES READ E WRITE
	COMUNICACAO SERVIDOR - GATEWAY
		FUNCOES READ E WRITE
	REPRESENTACAO DO CAMPO PARA O GATEWAY LER
		FUNCOES READ E WRITE
*/

#include <windows.h>
#include "DLL.h"

//Para verificar ao carregar a dll que a aplicação irá ocupar mais memória
char ponteiro[40960];

//Definição da variável global
int nDLL = 1234;

//Exportar funcoes para ser utilizadas fora da DLL

// COMUNICACAO GATEWAY -> SERVIDOR
// FUNCAO READ
// le uma msg
// copia o conteudo da msg da zona de memoria partilhada para o processo 
void readMSGGateway(ContrData * pcdata, Shared_MSG * msg) {
	WaitForSingleObject(pcdata->hRWMutex, INFINITE);
	// 1x CopyMemory - toda a info esta no mesmo sitio
	CopyMemory(msg, pcdata->shared, sizeof(Shared_MSG));
	ReleaseMutex(pcdata->hRWMutex);
}

// FUNCAO WRITE
// escreve uma msg
// copia o conteudo da zona nao partilhada do processo para a memoria partilhada
void writeMSGGateway(ContrData * pcdata, TCHAR * msgtext) {
	WaitForSingleObject(pcdata->hRWMutex, INFINITE);
	pcdata->shared->msgnum++;
	// se nao houver \0 as duas linhas seguintes falham
	// (por isso é que dá, e muito bem, warnings)
	_tcscpy(pcdata->shared->szOP, pcdata->MyName);
	_tcscpy(pcdata->shared->szMessage, msgtext);
	// 2x tcscpy porque a info vem de 2 sitios diferentes (szOP e szMessage)
	ReleaseMutex(pcdata->hRWMutex);
}

// COMUNICACAO SERVIDOR -> GATEWAY
// FUNCAO READ
// le uma msg
// copia o conteudo da msg da zona de memoria partilhada para o processo 
void readMSGServer(ContrData * pcdata, Shared_MSG * msg) {
	WaitForSingleObject(pcdata->hRWMutex, INFINITE);
	// 1x CopyMemory - toda a info esta no mesmo sitio
	CopyMemory(msg, pcdata->shared, sizeof(Shared_MSG));
	ReleaseMutex(pcdata->hRWMutex);
}

// FUNCAO WRITE
// escreve uma msg
// copia o conteudo da zona nao partilhada do processo para a memoria partilhada
void writeMSGServer(ContrData * pcdata, TCHAR * msgtext) {
	WaitForSingleObject(pcdata->hRWMutex, INFINITE);
	pcdata->shared->msgnum++;
	// se nao houver \0 as duas linhas seguintes falham
	// (por isso é que dá, e muito bem, warnings)
	_tcscpy(pcdata->shared->szOP, pcdata->MyName);
	_tcscpy(pcdata->shared->szMessage, msgtext);
	// 2x tcscpy porque a info vem de 2 sitios diferentes (szOP e szMessage)
	ReleaseMutex(pcdata->hRWMutex);
}

// sincronizar msgs recebidas na memoria partilhada
// mecanismo de polling na detecao de msgs novas
unsigned peekMSG(ContrData * pcdata) {
	unsigned msgnum;
	WaitForSingleObject(pcdata->hRWMutex, INFINITE);
	msgnum = pcdata->shared->msgnum;
	ReleaseMutex(pcdata->hRWMutex);
	return msgnum;
}

BOOL WINAPI DllMain(HANDLE hInstance, DWORD razao, LPVOID tipo_declaracao) {
	switch (razao) {
	case DLL_PROCESS_ATTACH:
		if (tipo_declaracao == NULL)
			MessageBox(NULL, TEXT("O processou carregou a biblioteca explicitamente"), TEXT("DLLmain"), MB_OK);
		else
			MessageBox(NULL, TEXT("O processou carregou a biblioteca implicitamente"), TEXT("DLLmain"), MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		if (tipo_declaracao == NULL)
			MessageBox(NULL, TEXT("O processou desmapeou a biblioteca explicitamente"), TEXT("DLLmain"), MB_OK);
		else
			MessageBox(NULL, TEXT("O processou desmapeou a biblioteca implicitamente"), TEXT("DLLmain"), MB_OK);
		break;
	}
	return 1;
}
