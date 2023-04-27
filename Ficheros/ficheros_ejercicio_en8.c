#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#define RUTA "citas.dat"
#define TAM 40

typedef struct {
	char nombre[20];
	char dia_semana[10];
	int hora;
}CITA;

int menu();
void inicializarSemana();
void borrarCita();
int comprobarNCita(int nCita);
void consultarCita();
void concertarCita();
void informeCita();
int totalCitas(FILE*);

int main() {
	setlocale(LC_ALL, "");
	int opc;
	void (*function[])() = {inicializarSemana,concertarCita,borrarCita,consultarCita,informeCita};
	opc = menu();
	while (opc != 0) {
		(*function[opc - 1])();
		opc = menu();
	}
	printf("\nSaliendo...");
	_getch();
	return 0;
}


int menu() {
	system("cls");
	int opc;
	do {
		printf("\n0. Salir.\n1. Inicializar semana.\n2. Concertar cita.\n3. Cancerlar cita.\n4. Consultar cita.\n5. Informe de la semana.");
		printf("\nIntroduca una opción: ");
		scanf("%d", &opc);
		rewind(stdin);
	} while (opc < 0 || opc > 5);
	return opc;
}

void inicializarSemana() {
	system("cls");
	FILE* pf;
	CITA cita;
	int count=0;
	pf = fopen(RUTA, "wb");

	if (pf == NULL) {
		printf("\nError al abrir el fichero.");
		fclose(pf);
		_getch();
		return;
	}
	strcpy(cita.nombre, "Libre");
	char* dias[] = { "Lunes","Martes","Miércoles","Jueves","Viernes" };
	for (int i = 0; i < TAM; i++)
	{
		if (i % 8 == 0) {
			count++;
		}

		strcpy(cita.dia_semana, dias[count-1]);
		fwrite(&cita,sizeof(cita),1,pf);
	}
	printf("\nFichero inicilizado con exito!");
	_getch();
	fclose(pf);
}

void concertarCita() {
	system("cls");
	FILE* pf;
	CITA cita;
	int libre=1, nCita,isNcita,lastNCita;
	pf = fopen(RUTA, "ab+");
	lastNCita = totalCitas(pf);
	if (pf == NULL) {
		printf("\nError al abrir el fichero.");
		fclose(pf);
		_getch();
		return;
	}
	do {
		printf("\nNº de cita: ");
		scanf("%d", &nCita);
		rewind(stdin);
		isNcita = comprobarNCita(nCita,lastNCita);
		if (isNcita) {
			fseek(pf, (nCita - 1) * sizeof(cita), SEEK_SET);

				fread(&cita, sizeof(cita), 1, pf);

				if (!strcmp(cita.nombre, "Libre")) {
					printf("\nNombre: ");
						gets(cita.nombre);
						libre = 0;
						printf("\nCita guardada exitosamente!");
				}
				else {
					printf("\nLa cita ya está ocupado.");
				}
		}else{
			printf("\nNº de cita incorrecta.");
		}
		_getch();
	} while (libre && !isNcita);

	fclose(pf);
}

void borrarCita() {
	system("cls");
	FILE* pf;
	CITA cita;
	int nCita,lastNcita;
	pf = fopen(RUTA, "ab+");
	lastNcita = totalCitas(pf);
	if (pf == NULL) {
		printf("\nError al abrir el fichero.");
		fclose(pf);
		_getch();
		return;
	}
	printf("\nNº de cita: ");
	scanf("%d", &nCita);
	rewind(stdin);
	if (comprobarNCita(nCita,lastNcita)) {
		fseek(pf, (nCita - 1) * sizeof(cita), SEEK_SET);
		fread(&cita, sizeof(cita), 1, pf);
		printf("\nNombre: %s",cita.nombre);
		strcpy(cita.nombre, "Libre");
		fwrite(&cita, (nCita - 1) * sizeof(cita),1,pf);
		printf("\nCita Libre");
	}
	else {
		printf("\nEl nº de cita es incorrecto.");
	}
	_getch();
	fclose(pf);
}

void consultarCita() {
	system("cls");
	FILE* pf;
	CITA cita;
	int  nCita,lastNCita;
	pf = fopen(RUTA, "rb");

	if (pf == NULL) {
		printf("\nError al abrir el fichero.");
		fclose(pf);
		_getch();
		return;
	}
	printf("\nNº de cita: ");
	scanf("%d", &nCita);
	rewind(stdin);
	lastNCita = totalCitas(pf);
	if (comprobarNCita(nCita,lastNCita)) {
		fseek(pf, (nCita - 1) * sizeof(cita), SEEK_SET);
		fread(&cita, sizeof(cita), 1, pf);
		printf("\nNombre: %s", cita.nombre);
		printf("\nCita ocupada.");
	}
	else {
		printf("\nEl nº de cita es incorrecto.");
	}
	_getch();
	fclose(pf);
}

void informeCita() {
	system("cls");
	FILE* preg,*pf;
	CITA cita;
	preg = fopen(RUTA, "rb");
	pf = fopen("citas.txt", "w");
	if (preg == NULL) {
		printf("\nError al abrir el fichero de registros.");
		fclose(preg);
		_getch();
		return;
	}

	if (pf == NULL) {
		printf("\nError al abrir el fichero de informes.");
		fclose(pf);
		fclose(preg);
		_getch();
		return;
	}

	fprintf(pf, "\n%6s %10s\n", "CITA", "NOMBRE");
	printf("\n%6s %10s\n", "CITA", "NOMBRE");
	fseek(preg, 0, SEEK_SET);
	while (fwrite(&cita,sizeof(cita),1, preg))
	{
		fprintf(pf, "%6s %10s\n",cita.dia_semana,cita.nombre);
		printf("%6s %10s\n", cita.dia_semana, cita.nombre);
	}
	fclose(pf);
	fclose(preg);
	_getch();
}

int comprobarNCita(int nCita,int lastNCita) {
	return !(nCita <= 0 || nCita >40 || nCita > lastNCita);
}

int totalCitas(FILE* pf) {
	int tam;
	CITA cita;
	fseek(pf, 0, SEEK_END);
	tam = ftell(pf);
	fseek(pf, 0, SEEK_SET);
	tam -= ftell(pf);
	return (tam / sizeof(cita));
}

