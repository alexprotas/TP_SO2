// Trata funcoes que lidem com o Buffer
// Vai ser lida e escrita pelo Gateway -> thread que lide com msgs recebidas do gateway -> thread que a envie para o server?
	// Vai receber MSGs de Clientes (escrita pelo Gateway)
		// dados de login?
		// 
// Vai ser lida e escrita pelo Server -> thread que lide com msgs recebidas do server -> thread que as envie para o(s) cliente(s)?

#include <windows.h>
#include "DLL.h"

//Para verificar ao carregar a dll que a aplicação irá ocupar mais memória
char ponteiro[40960];

//Definição da variável global
int nDLL = 1234;

//Exportar funcoes para ser utilizadas fora da DLL
