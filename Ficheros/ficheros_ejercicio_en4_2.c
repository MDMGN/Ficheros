#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#define RUTA "agenda.dat"

typedef struct {
	char fecha[10];
	char descripcion[15];
	int realizado;
}Agenda;

void introducirTareas();
void realizar();
void consultar();
int menu();
int validarFecha(char*);

int main() {
	setlocale(LC_ALL, "");
	int opc;
	void(*function[])() = {introducirTareas,realizar,consultar};

	opc = menu();

	while (opc != 4) {
		(*function[opc - 1])();
		opc = menu();
	}
	return 0;
}

int menu() {
	int opc;
	do {
		system("cls");
		printf("\n1. Introducir tareas.\n2. Realizar.\n3. Consultar.\n4. Salir.");
		printf("\nIntroduzca una opción: ");
		scanf("%d", &opc);
		rewind(stdin);
	} while (opc < 1 || opc > 4);
	return opc;
}

void introducirTareas() {
	Agenda agenda;
	FILE* pf;

	do {
		printf("\nFecha (dd/mm/aaaa): ");
		fgets(agenda.fecha, 10, stdin);
		fflush(stdin);
	} while (validarFecha(agenda.fecha) == -1);

	strtok(agenda.fecha, "\n");
	printf("\nDescripción: ");
	fgets(agenda.descripcion,15,stdin);
	fflush(stdin);
	strtok(agenda.descripcion, "\n");
	agenda.realizado = 0;

	pf = fopen(RUTA, "ab+");
	if (pf == NULL) {
		printf("\n Error al crear o abrir el fichero.");
		fclose(pf);
		_getch();
		return;
	}
	fwrite(&agenda, sizeof(agenda), 1, pf);
	fclose(pf);
	printf("\nRegistro exitoso!");
	_getch();
}
void realizar() {
	Agenda agenda;
	char descrip[15];
	FILE* pf;
	printf("\nDescripción: ");
	fgets(descrip, 15, stdin);
	fflush(stdin);
	strtok(descrip, "\n");
	pf=fopen(RUTA, "rb+");
	if (pf == NULL) {
		printf("\n Error al crear o abrir el fichero.");
		fclose(pf);
		_getch();
		return;
	}

	fseek(pf, 0, SEEK_SET);

	while (fread(&agenda, sizeof(Agenda), 1, pf) == 1) {
		if (strcmp(agenda.descripcion, descrip)==0) {
			agenda.realizado = 1;
			fwrite(&agenda, sizeof(agenda), 1, pf);
			printf("\nRegistro actualizado...");
			_getch();
			fclose(pf);
			return;
		}
	}

	printf("\nNo se encontro el registro...");
	_getch();
	fclose(pf);
}

void consultar() {
	Agenda agenda;
	char fecha[10];
	int count = 1, encontrado = 0;
	FILE* pf;
	do {
		printf("\nFecha (dd/mm/aaaa): ");
		fgets(fecha, 10, stdin);
		fflush(stdin);
	} while (validarFecha(fecha) == -1);

	pf = fopen(RUTA, "rb+");
	if (pf == NULL) {
		printf("\n Error al crear o abrir el fichero.");
		fclose(pf);
		_getch();
		return;
	}

	fseek(pf, 0, SEEK_SET);
	while (fread(&agenda, sizeof(Agenda), 1, pf) == 1) {
		printf("\n%s\n", agenda.fecha);
		if (strcmp(agenda.fecha, fecha) == 0 && agenda.realizado==0) {
			if (!encontrado) {
				encontrado = 1;
				printf("\nTareas pendientes: ");
			}
			printf("\n%d. %s.",count,agenda.descripcion);
		}
		count++;
	}

	if(!encontrado) printf("\nNo se encontro tareas pendientes...");
	_getch();
	fclose(pf);
}

int validarFecha(char* fecha_str) {
	struct tm fecha;

	if (sscanf(fecha_str, "%d/%d/%d", &fecha.tm_mday, &fecha.tm_mon, &fecha.tm_year) != 3) {
		return -1;
	}

	fecha.tm_year -= 1900;  // ajuste para el formato de fecha de la estructura tm
	fecha.tm_mon -= 1;      // ajuste para el formato de fecha de la estructura tm
	time_t t= mktime(&fecha);
	return t;
}

