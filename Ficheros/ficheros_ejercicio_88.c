#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

/*
main(int argc, char* argv[])
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	//programar a partir de aquí
	char Ent[256], Sal[256];
	char c;
	switch (argc)
	{
	case 1:
		system("cls");
		printf("Fichero de entrada: ");
		gets(Ent);
	case 2:
		system("cls");
		printf("Fichero de salida: ");
		gets(Sal);
		break;
	default:
		strcpy(Ent, argv[1]);
		strcpy(Sal, argv[2]);
	}
	FILE* fe, * fs;
	fe = fopen(Ent, "r");
	if (fe == NULL)
	{
		printf("Error de lectura");
		getch();
		return;
	}
	fs = fopen(Sal, "w");

	if (fs == NULL)
	{
		printf("Error de escritura");
		fclose(fe);
		getch();
		return;
	}
	c = getc(fe);
	while (c != EOF)
	{
		putc(c, fs);
		printf("%c", c);
		c = getc(fe);
	}
	fclose(fe);
	fclose(fs);
}
*/