// Trata funcoes que lidem com o Buffer
// Vai ser lida e escrita pelo Gateway
	// Vai receber MSGs de Clientes (escrita pelo Gateway)
		// dados de login?
		// 
// Vai ser lida e escrita pelo Server

#include <windows.h>
#include "DLL.h"

//Para verificar ao carregar a dll que a aplica��o ir� ocupar mais mem�ria
char ponteiro[40960];

//Defini��o da vari�vel global
int nDLL = 1234;

//Exportar funcoes para ser utilizadas fora da DLL
