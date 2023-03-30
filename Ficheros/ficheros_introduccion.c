#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#define RUTA "fichero.txt"
/*
void abrir(char* ruta);
void crear(char* ruta);
void agregar(char* ruta);
int menu();

int main() {
	setlocale(LC_ALL, "");
	
	void(*functions[])(char* ruta) = {abrir,agregar,crear};
	int opc;
	opc = menu();

	while (opc) {
		(*functions[opc - 1])(RUTA);
		opc = menu();
	}
	return 0;
}

int menu() {
	int opc;
	system("cls");
	do {
		printf("\n0.Salir\n1.Abrir fichero.\n2.Agregar texto.\n3.Crear fichero.");
		printf("\nIntroduzca una opción: ");
		scanf("%d", &opc);
		rewind(stdin);
	} while (opc < 0 || opc > 3);
	return opc;
}

void crear(char* ruta) {
	FILE* pf;
	pf = fopen(ruta, "w");
	if (pf == NULL) {
		printf("\nEl fichero no se pudo crear.");
		fclose(pf);
		_getch();
		return;
	}
	char c;
	printf("\nEscribir texto. Para finalizar (*): ");
	c = _getche();
	while (c != '*') {
		putc(c, pf);
		c = _getche();
	}
	printf("\nFichero creado con éxito.");
	fclose(pf);
	_getch();
}

void abrir(char* ruta) {
	FILE* pf;
	pf = fopen(ruta, "r");
	if (pf == NULL) {
		printf("\nEl fichero no se pudo abrir.");
		_getch();
		return;
	}
	char c;
	c = getc(pf);
	while (c != EOF){
		printf("%c", c);
		c = getc(pf);
	}
	printf("\nFichero abierto con éxito.");
	_getch();
}

void agregar(char* ruta) {
	FILE* pf;
	pf = fopen(ruta, "a");
	if (pf == NULL) {
		printf("\nEl fichero no existe.");
		fclose(pf);
		_getch();
		return;
	}
	char c;
	printf("\nEscribir texto. Para finalizar (*): ");
	c = _getche();
	while (c != '*') {
		putc(c, pf);
		c = _getche();
	}
	printf("\Texto agreado con éxito.");
	fclose(pf);
	_getch();
}

*/