#include "pch.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#define getch() _getch()

//Vytvoreni dynamicke 2D matice
int **createMatrix(int m, int n) {
	int** matrix = new int*[m];
	for (int i = 0; i < m; i++)
	{
		matrix[i] = new int[n];
	}
	return matrix;
}

//Naplneni matice nulami
void initMatrix(int **matrix, int m, int n) {
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

//Nastaveni kurzoru v konzoli na pozici x = sloupce, y = radky
void setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	fflush(stdin);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

//Tisk matice + nastaveni barev v konzoli
//switch from null matrix always show actual matrix
//edit every value have different color
void printMatrix(int **matrix, int m, int n) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	int stringSize = ((n * 2) + 2) * m;
	char *matrixString = new char[stringSize];

	printf("\n");
	SetConsoleTextAttribute(hConsole, 0x000f);
	for (int i = 0; i < m; i++)
	{
		printf("	|");
		for (int j = 0; j < n; j++)
		{
				if (matrix[i][j] < 10)
				{
					if (matrix[i][j] == 0)
					{
						SetConsoleTextAttribute(hConsole, 0x000f);
						printf(" %d  ", matrix[i][j]);
					}
					else if (matrix[i][j] == 2)
					{
						SetConsoleTextAttribute(hConsole, 0x000e);
						printf(" %d  ", matrix[i][j]);
					}
					else if (matrix[i][j] == 4)
					{
						SetConsoleTextAttribute(hConsole, 0x000d);
						printf(" %d  ", matrix[i][j]);
					}
					else if (matrix[i][j] == 8)
					{
						SetConsoleTextAttribute(hConsole, 0x000c);
						printf(" %d  ", matrix[i][j]);
					}
					
					
				}
				else if (matrix[i][j] > 10 && matrix[i][j] < 100)
				{
					if (matrix[i][j] == 16)
					{
						SetConsoleTextAttribute(hConsole, 0x000b);
						printf(" %d ", matrix[i][j]);
					}
					else if (matrix[i][j] == 32)
					{
						SetConsoleTextAttribute(hConsole, 0x000a);
						printf(" %d ", matrix[i][j]);
					}
					else if (matrix[i][j] == 64)
					{
						SetConsoleTextAttribute(hConsole, 0x000e);
						printf(" %d ", matrix[i][j]);
					}
					
					
				}
				else if (matrix[i][j] > 100 && matrix[i][j] < 1000)
				{
					if (matrix[i][j] == 128)
					{
						SetConsoleTextAttribute(hConsole, 0x000d);
						printf("%d ", matrix[i][j]);
					}
					else if (matrix[i][j] == 256)
					{
						SetConsoleTextAttribute(hConsole, 0x000c);
						printf("%d ", matrix[i][j]);
					}
					else if (matrix[i][j] == 512)
					{
						SetConsoleTextAttribute(hConsole, 0x000b);
						printf("%d ", matrix[i][j]);
					}
					
				}
				else
				{
					if (matrix[i][j] == 1024)
					{
						SetConsoleTextAttribute(hConsole, 0x000a);
						printf("%d", matrix[i][j]);
					}
					else if (matrix[i][j] == 2048)
					{
						SetConsoleTextAttribute(hConsole, 0x0009);
						printf("%d", matrix[i][j]);
					}
					
				}
				SetConsoleTextAttribute(hConsole, 0x000f);

				printf("|");
		}
		printf("\n");
	}
	SetConsoleTextAttribute(hConsole, saved_attributes);
}

//Vyprazdneni pameti od alokovane matice
void deleteMatrix(int **matrix, int m) {
	for (int i = 0; i < m; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

//Tisk bodu do koonzoloveho okna
void printPoint(int **matrix, int *mActual, int *nActual, int mOld, int nOld) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	matrix[*mActual][*nActual] = 0;
	//"magicke" konstanty pro vypoce spravne pozice bodu
	setCursorPosition(nOld * 2 + 2, mOld + 1);
	printf(" ");
	matrix[*mActual][*nActual] = 1;
	setCursorPosition(*nActual * 2 + 2, *mActual + 1);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	printf("O");
	fflush(stdin);

	SetConsoleTextAttribute(hConsole, saved_attributes);
}

//Posun bodu dle stisknute klavesy, s ochranou proti vstupu mimo oblast hraciho pole
void moveNumber(int **matrix, int m, int n, int d, int *mActual, int *nActual) {
	int mOld = *mActual, nOld = *nActual;
	if (d == 1 && *mActual - 1 >= 0) {
		(*mActual)--;
		printPoint(matrix, mActual, nActual, mOld, nOld);
	}

	if (d == 2 && *mActual + 1 < m) {
		(*mActual)++;
		printPoint(matrix, mActual, nActual, mOld, nOld);
	}

	if (d == 3 && *nActual - 1 >= 0) {
		(*nActual)--;
		printPoint(matrix, mActual, nActual, mOld, nOld);
	}

	if (d == 4 && *nActual + 1 < n) {
		(*nActual)++;
		printPoint(matrix, mActual, nActual, mOld, nOld);
	}
}

//Jednoduchy casovac zajistujici pocatecni zpozdeni
int simpleTimer(int n_seconds) {
	time_t start, now;

	start = time(NULL);
	now = start;
	//rozdil aktualniho a predchoziho casu CPU
	while (difftime(now, start) < (double)n_seconds) {
		now = time(NULL);
	}

	return 1;
}

//funkce pro skryti kursoru v konzoli
void showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}



