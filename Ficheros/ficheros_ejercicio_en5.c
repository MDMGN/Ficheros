#define _CRT_SECURE_NO_WARNINGS
#define TAM 15
#define RUTA "Vehiculos.dat"
#include <stdio.h>
#include <windows.h>

/*
typedef struct
{
	char matricula[10];
	char modelo[20];
	char tipo[20];
	float kms;
	int estado;
}VEHICULO;
void GotoXY(int x, int y);
void Inicializar();
void Alta();
void Baja();
void Registrar();
void Consultar();
void Listar();
int Menu();
int PedirPosicion();
void PedirDatos(VEHICULO* reg);
void MostrarDatos(VEHICULO reg);


int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	//programar a partir de aquí
	void (*opciones[6])() = { Inicializar,Alta,Registrar,Baja,Consultar,Listar };
	int opc;
	opc = Menu();
	while (opc != 0)
	{
		(*opciones[opc - 1])();
		opc = Menu();
	}
	return 0;
}




void GotoXY(int x, int y)
{
	HANDLE h;
	COORD pos;
	pos.X = x;
	pos.Y = y;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, pos);
}
void Inicializar()
{
	VEHICULO reg;
	FILE* pf;
	pf = fopen(RUTA, "wb");
	system("cls");
	if (pf == NULL)
	{
		GotoXY(31, 12);
		printf("Error de creación");
		getch();
		return;
	}
	reg.estado = 0;
	for (int i = 0; i < TAM; i++)
	{
		fwrite(&reg, sizeof(reg), 1, pf);
	}
	fclose(pf);
	GotoXY(28, 12);
	printf("Fichero creado con éxito!!");
	getch();
}
void Alta()
{
	FILE* pf;
	VEHICULO reg;
	int pos;
	pf = fopen(RUTA, "rb+");
	system("cls");
	if (pf == NULL)
	{
		GotoXY(31, 12);
		printf("Error de Apertura");
		getch();
		return;
	}
	pos = PedirPosicion();
	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 1)
	{
		system("cls");
		GotoXY(29, 12);
		printf("El registro ya existe");
	}
	else
	{
		PedirDatos(&reg);
		fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, pf);
		system("cls");
		GotoXY(26, 12);
		printf("Registro insertado con éxito");
	}
	getch();
	fclose(pf);


}
void Baja()
{
	FILE* pf;
	VEHICULO reg;
	char resp;
	int pos;
	pf = fopen(RUTA, "rb+");
	system("cls");
	if (pf == NULL)
	{
		GotoXY(31, 12);
		printf("Error de Apertura");
		getch();
		return;
	}
	pos = PedirPosicion();
	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 0)
	{
		system("cls");
		GotoXY(29, 12);
		printf("El registro no existe");
	}
	else
	{
		MostrarDatos(reg);
		printf("Está seguro?");
		resp = toupper(getche());
		if (resp == 'S')
		{
			reg.estado = 0;
			fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
			fwrite(&reg, sizeof(reg), 1, pf);
		}
	}
	getch();
	fclose(pf);
}
void Registrar()
{
	FILE* pf;
	VEHICULO reg;
	float kms;
	int pos;
	pf = fopen(RUTA, "rb+");
	system("cls");
	if (pf == NULL)
	{
		GotoXY(31, 12);
		printf("Error de Apertura");
		getch();
		return;
	}
	pos = PedirPosicion();
	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 0)
	{
		system("cls");
		GotoXY(29, 12);
		printf("El registro no existe");
	}
	else
	{
		MostrarDatos(reg);
		printf("Kilómetros realizados: ");
		scanf("%f", &kms);
		reg.kms += kms;
		fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, pf);

	}
	getch();
	fclose(pf);
}
void Consultar()
{
	FILE* pf;
	VEHICULO reg;
	int pos;
	pf = fopen(RUTA, "rb");
	system("cls");
	if (pf == NULL)
	{
		GotoXY(31, 12);
		printf("Error de Apertura");
		getch();
		return;
	}
	pos = PedirPosicion();
	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado == 0)
	{
		system("cls");
		GotoXY(29, 12);
		printf("El registro no existe");
	}
	else
	{
		MostrarDatos(reg);
	}
	getch();
	fclose(pf);
}
void Listar()
{
	FILE* pf;
	VEHICULO reg;
	int pos;
	pf = fopen(RUTA, "rb");
	system("cls");
	if (pf == NULL)
	{
		GotoXY(31, 12);
		printf("Error de Apertura");
		getch();
		return;
	}
	printf("%10s   %20s   %20s   %10s\n", "MATRÍCULA", "MODELO", "TIPO", "KILÓMETROS");
	for (int i = 0; i < TAM; i++)
	{
		fread(&reg, sizeof(reg), 1, pf);
		if (reg.estado == 1)
		{
			printf("%10s   %20s   %20s   %10.2f\n", reg.matricula, reg.modelo, reg.tipo, reg.kms);
		}
	}
	fclose(pf);
	getch();
}
int Menu()
{
	int opc;
	system("cls");
	printf("0.Salir\n1.Inicializar\n2.Alta\n3.Registrar\n4.Baja\n5.Consultar\n6.Listar\nIntroduce Opción: [ ]");
	do
	{
		GotoXY(19, 7);
		scanf("%d", &opc);
	} while (opc < 0 || opc>6);
	return opc;
}
int PedirPosicion()
{
	int pos = 0;
	system("cls");
	printf("Posición: ");

	do
	{
		GotoXY(10, 0);
		scanf("%d", &pos);
	} while (pos<1 || pos>TAM);
	return pos;
}
void PedirDatos(VEHICULO* reg)
{
	system("cls");
	printf("Matrícula: \nModelo: \nTipo: \n");
	rewind(stdin);
	GotoXY(10, 0);
	gets(reg->matricula);
	GotoXY(8, 1);
	gets(reg->modelo);
	GotoXY(6, 2);
	gets(reg->tipo);
	reg->kms = 0;
	reg->estado = 1;
}
void MostrarDatos(VEHICULO reg)
{
	system("cls");
	printf("Matrícula: %s\nModelo: %s\nTipo: %s\nKms: %.f\n", reg.matricula, reg.modelo, reg.tipo, reg.kms);


}

*/