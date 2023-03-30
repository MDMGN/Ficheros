#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>

int menu();
void crear();
void visualizar();
void copiar();


/*
int main() {
	setlocale(LC_ALL, "");
	void (*function[])() = {crear,visualizar,copiar};

	int opc = menu();
	
	while (opc != 4) {
		(*function[opc - 1])();
		opc = menu();
	}
	return 0;
}

int menu() {
	system("cls");
	int opc;
	do {

		printf("\n1.Crear.\n2.Visualizar\n3.Copiar.\n4.Salir.");
		printf("\nIntroduzca una opción: ");
		scanf("%d", &opc);
		rewind(stdin);
	} while (opc < 1 || opc > 4);
	return opc;
}

void crear() {
	char file[25],c;
	FILE* pf;
	system("cls");
	printf("\nNombre del fichero: ");
	gets(file);
	pf = fopen(file, "w");

	if (pf == NULL) {
		printf("\nEl fichero no se pudo crear.");
		fclose(pf);
		_getch();
		return;
	}

	printf("Escriba un texto. Finalizar con (*): ");
	c = _getche();
	while (c != '*') {
		putc(c, pf);
		c = _getche();
	}
	fclose(pf);
	_getch();
}

void visualizar() {
	char file[25], c;
	FILE* pf;
	system("cls");
	printf("\nNombre del fichero: ");
	gets(file);
	pf = fopen(file, "r");

	if (pf == NULL) {
		printf("\nEl fichero no se pudo abrir.");
		fclose(pf);
		_getch();
		return;
	}

	c = getc(pf);
	while (c != EOF) {
		printf("%c", c);
		c = getc(pf);
	}
	printf("\nFichero abierto con exito!");
	fclose(pf);
	_getch();
}

void copiar() {
	char file[25], cfile[25], c;

	FILE* pf;
	FILE* cpf;
	system("cls");
	printf("\nNombre del fichero a copiar: ");
	gets(cfile);
	printf("\nNombre del fichero a crear: ");
	gets(file);
	pf = fopen(file, "w");
	cpf = fopen(cfile, "r");

	if (cpf == NULL) {
		printf("\nEl fichero no se pudo abrir.");
		fclose(pf);
		_getch();
		return;
	}else if (pf == NULL) {
		printf("\nEl fichero no se pudo crear.");
		fclose(pf);
		_getch();
		return;
	}

	c = getc(cpf);
	while (c != EOF) {
		putc(c, pf);
		c = getc(cpf);
	}
	printf("\nFichero creado con exito!");
	fclose(cpf);
	fclose(pf);
	_getch();
}

*/