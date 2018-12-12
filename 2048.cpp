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
#include <stdbool.h>
#include <iostream>
#include <conio.h>






int main()
{
	int number[] = { 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
	int** matrix;
	char key, key2;
	int direction = 0;
	int errors_and_mods[2];
	char name[SIZE];
	int save_slot, counter = 0;
	errors_and_mods[0] = show_menu();
	//new game

	if (errors_and_mods[0] == 1)
	{
		system("cls");
		printf("input your name without space(maximum chararcter is 20) : ");
		scanf_s("%s", name, sizeof(name));
		system("cls");
		
		matrix = createMatrix(MAT, MAT);
		load_intit_matrix(matrix);
		printMatrix(matrix, MAT, MAT);
		errors_and_mods[1] = matrix_add_2(matrix);
		if (errors_and_mods[1] == 98)
		{
			exit(98);
		}
		while (1)
		{
			system("cls");
			printMatrix(matrix, MAT, MAT);
			printf("\n For movement use arrows or wsad , for exit !without save! press 'esc' and for save and exit press 'u'\n");
			key = _getch();
			key2 = 0;
			if (key == -32)
			{
				key2 = _getch();
			}

			//ESC
			if (key == 27)
			{
				add_stat(name, score(matrix, number));
				exit(0);
			}
			else if (key2 == 72 || key == 87 || key == 119) {
				//klavesa UP
				direction = 1;
			}
			else if (key2 == 80 || key == 83 || key == 115) {
				//klavesa DOWN
				direction = 2;
			}
			else if (key2 == 75 || key == 65 || key == 97) {
				//klavesa LEFT
				direction = 3;
			}
			else if (key2 == 77 || key == 68 || key == 100) {
				//klavesa RIGHT
				direction = 4;
			}
			else if (key == 85 || key == 117)
			{
				save(matrix, name);
			}
			else
			{
				printf("try another key");
			}
			errors_and_mods[1] = adjust_matrix(matrix, direction, number);
			if (errors_and_mods[1] == 96)
			{
				exit(96);
			}

			if (errors_and_mods[1] == 2048)
			{
				for (int i = 0; i < 22; i++)
				{
					if (i == 22)
					{
						printf("*\n");
					}
					else
					{
						printf("*");
					}
				}
				for (int j = 0; j < 10; j++)
				{
					if (j == 4)
					{
						printf("*       winner       *\n");
					}
					else
					{
						printf("*                    *\n");
					}
				}
				for (int i = 0; i < 22; i++)
				{
					if (i == 21)
					{
						printf("*\n");
					}
					else
					{
						printf("*");
					}
				}
				add_stat(name, score(matrix, number));
				break;
			}
			else if (errors_and_mods[1] == 90)
			{
				errors_and_mods[2] = check_for_end(matrix);
				if (errors_and_mods[2] == 91)
				{
					printf("end game, your stats have been add in statistick");
					add_stat(name, score(matrix, number));
					break;
				}
				else if (errors_and_mods[2])
				{
					exit(97);
				}


			}
			else if (errors_and_mods[1] != 90 && errors_and_mods[1] != 89)
			{
				errors_and_mods[2] = matrix_add_2(matrix);
				if (errors_and_mods[2] == 98)
				{
					exit(98);
				}
			}
			auto_save(matrix, name);

		}



	}
	//continue
	else if (errors_and_mods[0] == 2)
	{
	system("cls");
	matrix = createMatrix(MAT, MAT);
	struct actual_stats names;
	names = load_name_auto();
	if (names.score == -2 || names.score == -1)
	{
		exit(names.score);
	}
	errors_and_mods[1] = load_matrix_auto(matrix);
	if (errors_and_mods[1] == 95 || errors_and_mods[1] == 94)
	{
		exit(errors_and_mods[1]);
	}
	while (1)
	{
		system("cls");
		printMatrix(matrix, MAT, MAT);
		printf("\n For movement use arrows or wsad , for exit !without save! press 'esc' and for save press 'u'\n");
		key = _getch();
		key2 = 0;
		if (key == -32)
		{
			key2 = _getch();
		}

		//ESC
		if (key == 27) {
			add_stat(names.id, score(matrix, number));
			exit(0);
		}
		else if (key2 == 72 || key == 87 || key == 119) {
			//klavesa UP
			direction = 1;
		}
		else if (key2 == 80 || key == 83 || key == 115) {
			//klavesa DOWN
			direction = 2;
		}
		else if (key2 == 75 || key == 65 || key == 97) {
			//klavesa LEFT
			direction = 3;
		}
		else if (key2 == 77 || key == 68 || key == 100) {
			//klavesa RIGHT
			direction = 4;
		}
		else if (key == 85 || key == 117)
		{
			save(matrix, names.id);
		}
		else
		{
			printf("try another key");
		}
		errors_and_mods[1] = adjust_matrix(matrix, direction, number);
		if (errors_and_mods[1] == 96)
		{
			exit(96);
		}

		if (errors_and_mods[1] == 2048)
		{
			for (int i = 0; i < 22; i++)
			{
				if (i == 22)
				{
					printf("*\n");
				}
				else
				{
					printf("*");
				}
			}
			for (int j = 0; j < 10; j++)
			{
				if (j == 4)
				{
					printf("*       winner       *\n");
				}
				else
				{
					printf("*                    *\n");
				}
			}
			for (int i = 0; i < 22; i++)
			{
				if (i == 21)
				{
					printf("*\n");
				}
				else
				{
					printf("*");
				}
			}
			add_stat(names.id, score(matrix, number));
			break;
		}
		else if (errors_and_mods[1] == 90)
		{
			errors_and_mods[2] = check_for_end(matrix);
			if (errors_and_mods[2] == 91)
			{
				printf("end game, your stats have been add in statistick");
				add_stat(names.id, score(matrix, number));
				break;
			}
			else if (errors_and_mods[2])
			{
				exit(97);
			}


		}
		else if (errors_and_mods[1] != 90 && errors_and_mods[1] != 89)
		{
			errors_and_mods[2] = matrix_add_2(matrix);
			if (errors_and_mods[2] == 98)
			{
				exit(98);
			}
		}
		auto_save(matrix, names.id);

	}
	}
	//load game
	else if (errors_and_mods[0] == 3)
	{
		system("cls");
		while (counter < 5)
		{
			if (counter == 0)
			{
				printf("input from which slot you want load:  ");
				scanf_s("%d", &save_slot);
				
			}
			else if (counter < 5 && counter > 0 && save_slot < 0 || save_slot > 3)
			{
				printf("wrong input try again\ninput from which slot you want load:  ");
				scanf_s("%d", &save_slot);
				
			}
			else if (save_slot > 0 && save_slot < 4)
			{
				break;
			}
			else
			{
				printf("wrong inputs restart game");
				exit(1);
			}
			counter++;
		}
		matrix = createMatrix(MAT, MAT);
		struct actual_stats names;
		names = load_name(save_slot);
		if(names.score== -2 || names.score == -1)
		{ 
			exit(names.score);
		}
		errors_and_mods[1] = load_matrix(matrix, save_slot);
		if (errors_and_mods[1] == 95 || errors_and_mods[1] == 94)
		{
			exit(errors_and_mods[1]);
		}
		while (1)
		{
			system("cls");
			printMatrix(matrix, MAT, MAT);
			printf("\n For movement use arrows or wsad , for exit !without save! press 'esc' and for save press 'u'\n");
			key = _getch();
			key2 = 0;
			if (key == -32)
			{
				key2 = _getch();
			}

			//ESC
			if (key == 27) {
				add_stat(names.id, score(matrix, number));
				exit(0);
			}
			else if (key2 == 72 || key == 87 || key == 119) {
				//klavesa UP
				direction = 1;
			}
			else if (key2 == 80 || key == 83 || key == 115) {
				//klavesa DOWN
				direction = 2;
			}
			else if (key2 == 75 || key == 65 || key == 97) {
				//klavesa LEFT
				direction = 3;
			}
			else if (key2 == 77 || key == 68 || key == 100) {
				//klavesa RIGHT
				direction = 4;
			}
			else if (key == 85 || key == 117)
			{
				save(matrix, names.id);
			}
			else
			{
				printf("try another key");
			}
			errors_and_mods[1] = adjust_matrix(matrix, direction, number);
			if (errors_and_mods[1] == 96)
			{
				exit(96);
			}

			if (errors_and_mods[1] == 2048)
			{
				for (int i = 0; i < 22; i++)
				{
					if (i == 22)
					{
						printf("*\n");
					}
					else
					{
						printf("*");
					}
				}
				for (int j = 0; j < 10; j++)
				{
					if (j == 4)
					{
						printf("*       winner       *\n");
					}
					else
					{
						printf("*                    *\n");
					}
				}
				for (int i = 0; i < 22; i++)
				{
					if (i == 21)
					{
						printf("*\n");
					}
					else
					{
						printf("*");
					}
				}
				add_stat(names.id, score(matrix, number));
				break;
			}
			else if (errors_and_mods[1] == 90)
			{
				errors_and_mods[2] = check_for_end(matrix);
				if (errors_and_mods[2] == 91)
				{
					printf("end game, your stats have been add in statistick");
					add_stat(names.id, score(matrix, number));
					break;
				}
				else if (errors_and_mods[2])
				{
					exit(97);
				}


			}
			else if (errors_and_mods[1] != 90 && errors_and_mods[1] != 89)
			{
				errors_and_mods[2] = matrix_add_2(matrix);
				if (errors_and_mods[2] == 98)
				{
					exit(98);
				}
			}

			auto_save(matrix, names.id);
		}
	}
	// statistic
	else if (errors_and_mods[0] == 4)
	{
		system("cls");
		errors_and_mods[1] = show_stat();
	}
	// exit
	else if (errors_and_mods[0] == 5)
	{
		exit(0);
	}
	else if (errors_and_mods[0] == 6)
	{
	credits();
	}
	// wrong input -> exit
	else 
	{

		exit(errors_and_mods[0]);
	}




	return 0;
}


