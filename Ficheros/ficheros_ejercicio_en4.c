#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define RUTA "alumnos.dat"
#define INFORME "suspendidos.txt"
#define TAM 20
#include <stdio.h>
#include <windows.h>
/*
typedef struct
{
	char Nombre[20];
	float Acumulado;
	int Examenes;
}ALUMNO;
int Menu();
void CrearFichero();
void RegistrarNota();
void VerSuspendidos();
int PedirPos();
float PedirNota(ALUMNO reg);
void VerSuspendidosOrd();
float CalcularNota(ALUMNO reg);

main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	//programar a partir de aquí

	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	//programar a partir de aquí
	int opc;
	void (*funciones[])() = { CrearFichero,RegistrarNota,VerSuspendidosOrd };
	opc = Menu();
	while (opc != 4)
	{
		(*funciones[opc - 1])();
		opc = Menu();
	}

}

int Menu()
{
	int opc;
	do
	{
		system("cls");
		printf("1.Crear Fichero\n2.Nueva Nota\n3.Ver Suspendidos\n4.Salir\nIntroduce opcion: ");
		scanf("%d", &opc);
	} while (opc < 1 || opc>4);
	return opc;
}

int PedirPos()
{
	int pos;
	do
	{
		system("cls");
		printf("Posicion: ");
		scanf("%d", &pos);
	} while (pos<1 || pos>TAM);
	return pos;
}
float PedirNota(ALUMNO reg)
{
	float nota;
	do
	{
		system("cls");
		printf("Nota para %s: ", reg.Nombre);
		scanf("%f", &nota);
	} while (nota < 0 || nota>10);
	return nota;
}
float CalcularNota(ALUMNO reg)
{
	if (reg.Examenes == 0)
	{
		return 0;
	}
	else
	{
		return reg.Acumulado / reg.Examenes;
	}
}
void CrearFichero()
{
	FILE* pf;
	ALUMNO reg;
	pf = fopen(RUTA, "wb");
	system("cls");
	if (pf == NULL)
	{
		printf("Error de apertura");
		getch();
		return;
	}
	reg.Acumulado = reg.Examenes = 0;
	rewind(stdin);
	for (int i = 0; i < TAM; i++)
	{
		system("cls");
		printf("Nombre: ");
		gets(reg.Nombre);
		fwrite(&reg, sizeof(reg), 1, pf);
	}
	fclose(pf);
}
void Ordenar(ALUMNO alumnos[])
{
	ALUMNO aux;
	for (int i = 0; i < TAM - 1; i++)
		for (int j = TAM - 1; j > i; j--)
		{
			if (strcmp(alumnos[j].Nombre, alumnos[j - 1].Nombre) < 0)
			{
				aux = alumnos[j];
				alumnos[j] = alumnos[j - 1];
				alumnos[j - 1] = aux;
			}
		}
}
void RegistrarNota()
{
	FILE* pf;
	ALUMNO reg;
	int pos;
	float nota;
	pf = fopen(RUTA, "rb+");
	system("cls");
	if (pf == NULL)
	{
		printf("Error de apertura");
		getch();
		return;
	}
	pos = PedirPos();

	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	nota = PedirNota(reg);
	reg.Acumulado += nota;
	reg.Examenes++;
	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fwrite(&reg, sizeof(reg), 1, pf);
	fclose(pf);
}
void VerSuspendidos()
{
	FILE* pf, * inf;
	ALUMNO reg;
	int cont = 0;
	float media;
	pf = fopen(RUTA, "rb");
	system("cls");
	if (pf == NULL)
	{
		printf("Error de apertura");
		getch();
		return;
	}
	inf = fopen(INFORME, "w");
	if (inf == NULL)
	{
		printf("Error al crear el informe");
		fclose(pf);
		getch();
		return;
	}
	fprintf(inf, "%20s  %10s\n", "Nombre", "Nota Media");
	for (int i = 0; i < TAM; i++)
	{
		fread(&reg, sizeof(reg), 1, pf);
		media = CalcularNota(reg);
		if (media < 5)
		{
			fprintf(inf, "%20s  %10.2f\n", reg.Nombre, media);
			cont++;
		}
	}
	fprintf(inf, "Total de suspensos: %d", cont);
	fclose(pf);
	fclose(inf);
}
void VerSuspendidosOrd()
{
	FILE* pf, * inf;
	ALUMNO reg[TAM];
	int cont = 0;
	float media;
	pf = fopen(RUTA, "rb");
	system("cls");
	if (pf == NULL)
	{
		printf("Error de apertura");
		getch();
		return;
	}
	inf = fopen(INFORME, "w");
	if (inf == NULL)
	{
		printf("Error al crear el informe");
		fclose(pf);
		getch();
		return;
	}
	fprintf(inf, "%20s  %10s\n", "Nombre", "Nota Media");
	fread(reg, sizeof(ALUMNO), TAM, pf);
	Ordenar(reg);
	for (int i = 0; i < TAM; i++)
	{

		media = CalcularNota(reg[i]);
		if (media < 5)
		{
			fprintf(inf, "%20s  %10.2f\n", reg[i].Nombre, media);
			cont++;
		}
	}
	fprintf(inf, "Total de suspensos: %d", cont);
	fclose(pf);
	fclose(inf);
}

*/