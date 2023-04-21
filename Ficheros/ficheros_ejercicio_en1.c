#pragma once
#define TAM 10
#define RUTA "productos.dat"
#define INFO "informe.txt"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
/*
typedef struct
{
	char descripcion[20];
	float precio;
	int existencias;
	int estado;
}PRODUCTO;

//Menu principal
int Menu();
//Opciones menu

void Inicializar();
void Realizar();
void Alta();
void Baja();
void Mostrar();
void Consultar();
//Auxiliares
void GotoXY(int x, int y);
int PedirPos();
void PedirDatos(PRODUCTO* reg);
void MostrarDatos(PRODUCTO reg);

main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	//programar a partir de aquí
	void (*funciones[])() = { Inicializar,Realizar,Alta,Baja,Mostrar,Consultar };
	int opc;
	opc = Menu();
	while (opc != 0)
	{
		(*funciones[opc - 1])();
		opc = Menu();
	}
}
#include "Funcioens.h"

void Inicializar()
{
	FILE* pf;
	PRODUCTO reg;
	pf = fopen(RUTA, "wb");
	system("cls");
	if (pf == NULL)
	{
		printf("Error al crear el fichero");
		getch();
		return;
	}
	reg.estado = 0;
	for (int i = 0; i < TAM; i++)
	{
		fwrite(&reg, sizeof(reg), 1, pf);
	}
	printf("Fichero creado con éxito!!!");
	fclose(pf);
	getch();
	return;
}
void Realizar()
{

}
void Alta()
{
	FILE* pf;
	int pos;
	PRODUCTO reg;
	pf = fopen(RUTA, "rb+");
	system("cls");
	if (pf == NULL)
	{
		printf("Error al abrir el fichero");
		getch();
		return;
	}
	pos = PedirPos();
	fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 1)
	{
		printf("El registro especificado ya existe.");
	}
	else
	{
		PedirDatos(&reg);
		fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, pf);
		printf("Registro guardado con éxito!");
	}
	fclose(pf);
	getch();
}
void Baja()
{
	FILE* pf;
	int pos;
	char resp;
	PRODUCTO reg;
	pf = fopen(RUTA, "rb+");
	system("cls");
	if (pf == NULL)
	{
		printf("Error al abrir el fichero");
		getch();
		return;
	}
	pos = PedirPos();
	fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 0)
	{
		printf("El registro especificado no existe.");
	}
	else
	{
		MostrarDatos(reg);
		printf("Está seguro que desea eliminar el registro?");
		resp = toupper(getche());
		if (resp == 'S')
		{
			reg.estado = 0;
			fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
			fwrite(&reg, sizeof(reg), 1, pf);
			printf("Registro eliminado con éxito!");
		}
		else {
			printf("Se canceló la operación.");
		}
	}
	fclose(pf);
	getch();
}
void Mostrar()
{
	FILE* pf, * info;
	PRODUCTO reg;
	pf = fopen(RUTA, "rb");
	system("cls");
	if (pf == NULL)
	{
		printf("Error de apertura");
		getch();
		return;
	}
	info = fopen(INFO, "w");
	if (info == NULL)
	{
		printf("No se puede generar el informe");
		getch();
		fclose(pf);
		return;
	}
	fprintf(info, "%6s   %20s   %8s   %6s\n", "CÓDIGO", "DESCRIPCIÓN", "UNIDADES", "PRECIO");
	for (int i = 0; i < TAM; i++)
	{
		fread(&reg, sizeof(reg), 1, pf);
		if (reg.estado != 0)
		{
			fprintf(info, "%6d   %20s   %8d   %6.2f\n", i + 1, reg.descripcion, reg.existencias, reg.precio);
		}
	}
	fclose(pf);
	fclose(info);
	printf("Informe generado con éxito!!!");
	getch();

}
void Consultar()
{
	FILE* pf;
	int pos;
	PRODUCTO reg;
	pf = fopen(RUTA, "rb");
	system("cls");
	if (pf == NULL)
	{
		printf("Error al abrir el fichero");
		getch();
		return;
	}
	pos = PedirPos();
	fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 0)
	{
		printf("El registro especificado no existe.");
	}
	else
	{
		MostrarDatos(reg);

	}
	fclose(pf);
	getch();
}
int Menu()
{
	int opc = 0;
	system("cls");
	printf("0.Salir\n1.Crear\n2.Realizar\n3.Alta\n4.Baja\n5.Mostrar\n6.Consultar\nIntroduce Opcion: ");
	do
	{
		GotoXY(19, 7);
		scanf("%d", &opc);
	} while (opc < 0 || opc>6);

	return opc;
}

void GotoXY(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, pos);
}

int PedirPos()
{
	int pos;
	system("cls");
	printf("Posición: ");
	do
	{
		GotoXY(10, 0);
		scanf("%d", &pos);

	} while (pos<1 || pos>TAM);
	return pos;
}
void PedirDatos(PRODUCTO* reg)
{
	system("cls");
	printf("Descripción: \n");
	printf("Precio: \n");
	printf("Existencias: \n");
	GotoXY(13, 0);
	rewind(stdin);
	gets(reg->descripcion);
	GotoXY(8, 1);
	scanf("%f", &reg->precio);
	GotoXY(13, 2);
	scanf("%d", &reg->existencias);
	reg->estado = 1;
}
void MostrarDatos(PRODUCTO reg)
{
	system("cls");
	printf("Descripción: %s\n", reg.descripcion);
	printf("Precio: %.2f\n", reg.precio);
	printf("Existencias: %d\n", reg.existencias);

}

*/