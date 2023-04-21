#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define RUTA "cuentas.dat"
#define INFORME "saldos.txt"
#define TAM 10
#include <stdio.h>
#include <windows.h>

/*
typedef struct
{
	char Titular[25];
	int IdCuenta;
	float Saldo;
	int Estado;
}CUENTA;
int Menu();
void InicializarFichero();
void AltaCuenta();
void RealizarTransaccion();
void BajaCuenta();
void MostrarSaldo();
int PedirPos();
void PedirDatos(CUENTA* reg);
void MostrarDatos(CUENTA reg);
char PedirOperacion();

main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	//programar a partir de aquí
	int opc;
	void (*funciones[])() = { InicializarFichero,AltaCuenta,RealizarTransaccion,BajaCuenta,MostrarSaldo };
	opc = Menu();
	while (opc != 6)
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
		printf("1.Inicializar fichero\n2.Alta Cuenta\n3.Realizar Transaccion\n4.Baja Cuenta\n5.Mostrar saldos\n6.Salir\nIntroduce opcion: ");
		scanf("%d", &opc);
	} while (opc < 1 || opc>6);
	return opc;
}

void InicializarFichero()
{
	FILE* pf;
	system("cls");
	pf = fopen(RUTA, "wb");
	CUENTA reg;
	if (pf == NULL)
	{
		printf("Error al abrir el fichero");
		getch();
		return;
	}
	reg.Estado = 0;
	for (int i = 0; i < TAM; i++)
	{
		fwrite(&reg, sizeof(reg), 1, pf);
	}
	fclose(pf);
}
void AltaCuenta()
{
	FILE* pf;
	CUENTA reg;
	pf = fopen(RUTA, "rb+");
	int pos;
	if (pf == NULL)
	{
		printf("Error al abrir el fichero");
		getch();
		return;
	}
	pos = PedirPos();
	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.Estado == 1)
	{
		printf("Error, la cuenta ya existe");
		getch();
	}
	else
	{
		PedirDatos(&reg);
		fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, pf);
		printf("Registro dado de alta");
	}
	fclose(pf);

}
void RealizarTransaccion()
{
	char op;
	int pos;
	CUENTA reg;
	float cant;
	FILE* pf;
	pf = fopen(RUTA, "rb+");
	system("cls");
	if (pf == NULL)
	{
		printf("Error al abrir el fichero");
		getch();
		return;
	}
	op = PedirOperacion();
	pos = PedirPos();
	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.Estado == 0)
	{
		printf("El registro no existe");
		getch();
	}
	else
	{
		printf("Cantidad: ");
		scanf("%f", &cant);
		if (op == 'I')
		{
			reg.Saldo += cant;
			fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
			fwrite(&reg, sizeof(reg), 1, pf);
		}
		else
		{
			if (reg.Saldo >= cant)
			{
				reg.Saldo -= cant;
				fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
				fwrite(&reg, sizeof(reg), 1, pf);
			}
			else
			{
				printf("No hay saldo suficiente");
				getch();
			}
		}
	}
	fclose(pf);
}
void BajaCuenta()
{
	FILE* pf;
	CUENTA reg;
	char resp;
	pf = fopen(RUTA, "rb+");
	int pos;
	if (pf == NULL)
	{
		printf("Error al abrir el fichero");
		getch();
		return;
	}

	pos = PedirPos();
	fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.Estado == 0)
	{
		printf("Error, la cuenta no existe");
		getch();
	}
	else
	{
		MostrarDatos(reg);
		printf("Desea borrar el registro?");
		resp = toupper(getch());
		if (resp == 'S')
		{
			reg.Estado = 0;
			fseek(pf, sizeof(reg) * (pos - 1), SEEK_SET);
			fwrite(&reg, sizeof(reg), 1, pf);
			printf("Registro Borrado");
		}
		else
		{
			printf("El registro no se borró");
		}
		getch();
	}

	fclose(pf);
}
void MostrarSaldo()
{
	FILE* pf, * inf;
	CUENTA reg;
	pf = fopen(RUTA, "rb");
	system("cls");
	if (pf == NULL)
	{
		printf("Error al abrir el fichero");
		getch();
		return;
	}
	inf = fopen(INFORME, "w");
	if (inf == NULL)
	{
		printf("Error al crear el informe");
		fclose(pf);
		return;
	}
	fprintf(inf, "%6s   %25s  %10s\n", "CÓDIGO", "NOMBRE", "SALDO");
	for (int i = 0; i < TAM; i++)
	{
		fread(&reg, sizeof(reg), 1, pf);
		if (reg.Estado == 1)
		{

			fprintf(inf, "%6d   %25s  %10.2f\n", reg.IdCuenta, reg.Titular, reg.Saldo);
		}
	}
	fclose(pf);
	fclose(inf);
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

void PedirDatos(CUENTA* reg)
{
	system("cls");
	rewind(stdin);
	system("cls");
	printf("Titular: ");
	gets(reg->Titular);
	printf("IdCuenta: ");
	scanf("%d", &reg->IdCuenta);
	printf("Saldo: ");
	scanf("%f", &reg->Saldo);
	reg->Estado = 1;
}
void MostrarDatos(CUENTA reg)
{
	system("cls");
	printf("Titular: %s\n", reg.Titular);
	printf("Cuenta: %d\n", reg.IdCuenta);
	printf("Saldo: %.2f\n", reg.Saldo);
	getch();
}

char PedirOperacion()
{
	char op;
	system("cls");
	printf("¿Qué deseas hacer? (I:Ingreso/R:Reintegro");
	op = toupper(getche());
	return op;
}

*/