#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
/*
main(int argc, char* argv[])
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	//programar a partir de aquí
	if (argc != 2)
	{
		printf("Número de parámetros incorrecto");
		getch();
		return;
	}
	FILE* pf = fopen(argv[1], "r");
	char c;
	if (pf == NULL)
	{
		printf("Error de apertura");
		getch();
		return;
	}
	c = getc(pf);
	while (c != EOF)
	{
		printf("%c", c);
		c = getc(pf);
	}
	fclose(pf);
}*/