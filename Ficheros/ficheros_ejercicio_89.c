#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#define TAM 10
#define RUTA "productos.dat"
#define INFO "informe.txt"


typedef struct {
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

int main() {
	setlocale(LC_ALL, "");
	void (*funciones[])() = { Inicializar,Realizar,Alta,Baja,Mostrar,Consultar };
	int opc;
	opc = Menu();
	while (opc != 0)
	{
		(*funciones[opc - 1])();
		opc = Menu();
	}
}

void Inicializar()
{
	FILE* pf;
	PRODUCTO reg;
	pf = fopen(RUTA, "wb");
	system("cls");
	if (pf == NULL)
	{
		printf("\nError al crear el fichero");
		_getch();
		return;
	}
	reg.estado = 0;
	for (int i = 0; i < TAM; i++)
	{
		fwrite(&reg, sizeof(reg), 1, pf);
	}
	printf("\nFichero creado con éxito!!!");
	fclose(pf);
	_getch();
}
void Realizar()
{
	FILE* pf;
	char resp; int pos, unid;
	PRODUCTO reg;
	do {
		printf("\nQuieres comprar o vender? (c/v): ");
		resp = tolower(_getche());
	} while (resp != 'c' && resp != 'v');
	pos = PedirPos();
	printf("\nNúmero de unidades: ");
	scanf("%d", &unid);
	rewind(stdin);
	pf = fopen(RUTA, "rb+");
	if (pf == NULL) {
		printf("\nError al abrir el fichero");
		_getch();
		return;
	}
	fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.existencias < unid) {
		printf("\nNo se pueden vender más inodades de las existencias.");
	}
	else {
		if (resp == 'c') {
			reg.existencias += unid;
		}
		else {
			reg.existencias -= unid;
		}
		fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, pf);
	}
	fclose(pf);
	_getch();
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
		printf("\nError al abrir el fichero");
		_getch();
		return;
	}
	pos = PedirPos();
	fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 1)
	{
		printf("\nEl registro especificado ya existe.");
	}
	else
	{
		PedirDatos(&reg);
		fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, pf);
		printf("\nRegistro guardado con éxito!");
	}
	fclose(pf);
	_getch();
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
		printf("\nError al abrir el fichero");
		_getch();
		return;
	}
	pos = PedirPos();
	fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 0)
	{
		printf("\nEl registro especificado no existe.");
	}
	else
	{
		MostrarDatos(reg);
		printf("\nEstá seguro que desea eliminar el registro?");
		resp = toupper(_getche());
		if (resp == 'S')
		{
			reg.estado = 0;
			fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
			fwrite(&reg, sizeof(reg), 1, pf);
			printf("\nRegistro eliminado con éxito!");
		}
		else {
			printf("\nSe canceló la operación.");
		}
	}
	fclose(pf);
	_getch();
}
void Mostrar()
{
	FILE* pf, * info;
	PRODUCTO reg;
	pf = fopen(RUTA, "rb");
	system("cls");
	if (pf == NULL)
	{
		printf("\nError de apertura");
		_getch();
		fclose(pf);
		return;
	}
	info = fopen(INFO, "w");
	if (info == NULL)
	{
		printf("\nNo se puede generar el informe");
		_getch();
		fclose(info);
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
	printf("\nInforme generado con éxito!!!");
	_getch();

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
		printf("\nError al abrir el fichero");
		fclose(pf);
		_getch();
		return;
	}
	pos = PedirPos();
	fseek(pf, (pos - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 0)
	{
		printf("\nEl registro especificado no existe.");
	}
	else
	{
		MostrarDatos(reg);

	}
	fclose(pf);
	_getch();
}
int Menu()
{
	int opc = 0;
	system("cls");
	printf("\n0.Salir\n1.Crear\n2.Realizar\n3.Alta\n4.Baja\n5.Mostrar\n6.Consultar\nIntroduce Opcion: ");
	do
	{
		GotoXY(19, 8);
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
	printf("\nPosición: ");
	do
	{
		GotoXY(10, 1);
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
	printf("\nDescripción: %s", reg.descripcion);
	printf("\nPrecio: %.2f", reg.precio);
	printf("\nExistencias: %d", reg.existencias);

}