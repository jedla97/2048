//xjedli24
#include "pch.h"
#include "school_lib.h"
#include "our_lib.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


int main()
{
	int counter = 0;
	initialization_file();
	show_menu();
	char name[SIZE];
	int gamemode=0;
	scanf_s("%d",&gamemode);
	//new game
	if (gamemode == 1)
	{
		printf("input your name without space(maximum chararcter is 20) : ");
		if (scanf_s("%s", name, sizeof(name)) == 1);
		//add_stat(name, 10);
		createMatrix(MAT, MAT);
	}
	//continue
	else if (gamemode == 2)
	{

	}
	//load game
	else if (gamemode == 3)
	{

	}
	// statistic
	else if (gamemode == 4)
	{

	}
	// exit
	else if (gamemode == 5)
	{
		exit(0);
	}
	// wrong input -> exit
	else
	{
		exit(0);
	}

/*	//m = radky, n = sloupce
	int m, n;
	int mActual = 0, nActual = 0;
	int** matrix;



	printf("Zadej velikost matice MxN: ");
	scanf_s("%d %d", &m, &n);
	system("cls");



	matrix = createMatrix(m, n);

	initMatrix(matrix, m, n);
	matrix[0][0] = 0;

	//skryti kursoru
	showConsoleCursor(false);

	int counter = 2;

	unsigned int key;
	char direction;



	while (counter > 1) {
		printf("Do startu zbyva: %d s", counter);
		counter -= simpleTimer(1);
		system("cls");
	}

	printMatrix(matrix, m, n);

	while (1)
	{
		key = getchar();
		//Odstraneni prebytecnych znaku odesilanych pri stisku smerovych sipek
		if (key == 0 || key == 0xE0) {
			key = getchar();
		}

		//ESC
		if (key == 27) {
			break;
		}
		else if (key == 72) {
			//klavesa UP
			direction = 'u';
		}
		else if (key == 80) {
			//klavesa DOWN
			direction = 'd';
		}
		else if (key == 75) {
			//klavesa LEFT
			direction = 'l';
		}
		else if (key == 77) {
			//klavesa RIGHT
			direction = 'r';
		}
		moveNumber(matrix, m, n, direction, &mActual, &nActual);
	}
	
	deleteMatrix(matrix, m);*/

	return 0;
}

