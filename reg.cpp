#include <windows.h>
#include <stdio.h>

/*
	==] Manipulador de registro [==
	Escreve um DWORD na arvore do registro.
	=======================================
	v 1.0 - Inicial
	v 1.1 - Refactor acrescentando exitCode
	
*/

int main(){
	HKEY hRootKey = HKEY_LOCAL_MACHINE;  // ROOT onde vai criar a chave do registro
	LPCTSTR strKey = TEXT("SOFTWARE\\CHS"); // Chave propriamente dita
	LPCTSTR lpValue = TEXT("Parametro");  // Nome do valor pra armazenar
	DWORD data = 10;  // DATA...
	
	int exitCode = 2; // exitCode 2: Nao conseguiu abrir ou criar a chave
	
	HKEY hKeyOpened; // Vai armazenar o HANDLE para a chave que abrir

	LONG nErr = RegOpenKeyEx(hRootKey, strKey, NULL, KEY_ALL_ACCESS, &hKeyOpened);  // Funcao para abrir, caso exista.

	if (nErr==ERROR_FILE_NOT_FOUND)
	{
		printf("Creating registry key: %s.\n", strKey);
		nErr = RegCreateKeyEx(hRootKey, strKey, NULL, NULL, REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hKeyOpened, NULL);  // Se nao existe, cria e abre.
	}

	if (nErr){
		printf("Error: %lu  -  Could not find or create %s.\n", nErr, strKey);
	} else {
		nErr = RegSetValueEx(hKeyOpened, lpValue, NULL, REG_DWORD, (LPBYTE)&data, sizeof(DWORD));  // Escreve no registro
		
		if (nErr){
			printf("Error: %lu  -  Could not save data %lu on value %s.\n", nErr, data, (char*)lpValue);
			exitCode = 1;  // exitCode 1: Nao conseguiu salvar o value na chave
		} else {
			printf("Success: %lu  -  Save OK data %lu on value %s.\n", nErr, data, (char*)lpValue);
			exitCode = 0;  // =P
		}

		RegCloseKey(hKeyOpened);  // Abriu? Entao fecha...  =P
	}
	return exitCode;
}
