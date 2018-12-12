//xjedli24
#include "pch.h"
#include "our_lib.h"
#include "school_lib.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
void credits()
{
	system("cls");
	printf("\n\nthis game was created by Jakub Jedèka(xjedli24) and Maxim Ilyushchenkov(xilyus00) \n\n");
	printf("students of BUT FEEC\n\n");
	printf("for contacts use mainly xjedli24@stud.feec.vutbr.cz\n\n");
	printf("this game is semestral project in BPC1T\n\n\n\n");

}
int show_menu()
{
	char gamemode[BUFFER_SIZE];
	char *end;
	long gamemod;
	int counter = 0;
	printf("********	welcome in our 2048		********\n\n");
	printf("		  1. new game \n");
	printf("		  2. continue\n");
	printf("		  3. load game\n");
	printf("		  4. statistics\n");
	printf("		  5. close 2048\n");
	printf("		  6. credits\n\n");
	printf("press number which corresponds your next step (e.g 1 for new game): ");
	while (counter < 5)
	{
		if (counter == 0)
		{
			scanf_s("%s", &gamemode,BUFFER_SIZE);
			if (isdigit(gamemode[0]))
			{
				if (strlen(gamemode) < 2)
				{
					gamemod = strtol(gamemode, &end, 7); // 6 for read and change numbers from 0-5
					if (gamemod == 1 || gamemod == 2 || gamemod == 3 || gamemod == 4 || gamemod == 5 || gamemod == 6)
					{
						return gamemod;
					}
					counter++;
				}
				else
				{
					counter++;
				}
			}
			else
			{
				printf("enter digit not char\n");
				counter++;
			}
		}
		else
		{
			printf("wrong gamemode input, please try it again: ");
			scanf_s("%s", &gamemode, BUFFER_SIZE);
			if (isdigit(gamemode[0]))
			{
				if (strlen(gamemode) < 2)
				{
					gamemod = strtol(gamemode, &end, 7); //range number input
					if (gamemod == 1 || gamemod == 2 || gamemod == 3 || gamemod == 4 || gamemod == 5 || gamemod == 6)
					{
						return gamemod;
					}
					counter++;
				}
				else
				{
					counter++;
				}
			}
			else
			{
				printf("enter digit not char");
				counter++;
			}
		}
	}
	return 99;
}
int random_number(int max_number)
{
	int x = 0; 
	x = rand() % max_number;
	return x;
}
void statistics_write(char *name, int score)
{
	FILE *open;
	errno_t errorCode = fopen_s(&open, "statistics_name.txt", "a+");
	fprintf(open, "%s|||%d \n", name, score);
	fclose(open);

}
void statistics_rewrite(char *name, int score)
{
	FILE *open;
	errno_t errorCode = fopen_s(&open, "statistics_name.txt", "w");
	fprintf(open, "%s|||%d \n", name, score);
	fclose(open);

}
actual_stats save_to_structure(char* str, int count)
{
	struct actual_stats st;
	int flag = 0;
	char separators[] = "|";
	char *token1;
	char *token = strtok_s(str, separators, &token1);
	while (token != NULL)
	{
		if (0 == flag)
		{
			strcpy_s(st.id, SIZE, token);
		}
		else if (1 == flag)
		{
			st.score = atoi(token);
		}
		flag++;
		token = strtok_s(NULL, separators, &token1);
	}

	return st;
}
void print(actual_stats* arr, int size)
{
	char help[] = "player name";
	char help2[] = "high score";
	printf("*******		STATISTICS	   *******\n%16s%21s\n", help, help2);
	for (int i = 0; i < size; i++)
	{
		printf("%21s|%21d|\n", arr[i].id,  arr[i].score);
	}
}
int compare(const void* l, const void* r)
{
	actual_stats *a = (actual_stats *)l;
	actual_stats *b = (actual_stats *)r;
	return (b->score- a->score);
}
int show_stat()
{
	int counter = 0, i=0;
	struct actual_stats arr[BUFFER_SIZE];
	FILE* open;
	errno_t errorCode = fopen_s(&open, "statistics_name.txt", "r");
	if (open == NULL)
	{
		return -1;
	}

	char buffer[BUFFER_SIZE];
	int flag = 0;
	while (fgets(buffer, BUFFER_SIZE, open))
	{
		arr[flag] = save_to_structure(buffer, counter);
		flag++;
		counter++;
	}
	qsort(arr, counter, sizeof(actual_stats), compare);
	fclose(open);
	if(counter<10)
	{
		print(arr, counter);
		return 1;
	}
	else
	{
		print(arr, 10);
		return 1;
	}
	if (counter == 99)
	{
		change_stat_txt(arr);
		return 1;
	}
}
void change_stat_txt(actual_stats *arr)
{
	int i = 0;
	while (i < 15)
	{
		if (i != 0)
		{
			statistics_write(arr[i].id, arr[i].score);
			i++;
		}
		else
		{
			statistics_rewrite(arr[i].id, arr[i].score);
			i++;
		}
	}
	
}
void add_stat(char *name, int score)
{
	struct actual_stats *st;
	st = (actual_stats *) malloc(sizeof(actual_stats));
	strcpy_s(st->id, SIZE, name);
	st->score = score;
	statistics_write(st->id, st->score);
	free(st);
}
int score(int **matrix, int *arr)
{
	int counter = 0;
	int score = 0;
	for (int i = 0; i < MAT; i++)
	{
		for (int j = 0; j < MAT; j++)
		{
			
			for (int k = 0; k < 11; k++)
			{
				if(arr[k] == matrix[i][j])
				{
					counter++;
					k = 11;
				}
				else
				{
					counter++;
				}
				if (counter == 11)
				{
					counter = 0;
				}
			}
			score = score + arr[counter-1] * (counter);
			counter = 0;
		
		}
	}
	return score;
}
int auto_save(int **matrix, char *name)
{
	FILE* fp;
	errno_t errorCode = fopen_s(&fp, "auto_save.txt", "w");
	if (fp== NULL)
	{
		return -1;
	}
	fprintf(fp, "%s\n", name);
	for (int i = 0; i < MAT; i++)
	{
		for (int j = 0; j < MAT; j++)
		{
			if (j == 3 && i < 3)
			{
					fprintf(fp, "%d\n", matrix[i][j]);
			}
			else if (j == 3 && i == 3)
			{
					fprintf(fp, "%d", matrix[i][j]);
			}
			else
			{
					fprintf(fp, "%d|", matrix[i][j]);
			}
		}
	}
	fclose(fp);
	return 1;
}
int save(int **matrix, char *name)
{
	int counter = 0;
	int save_slot;
	while (counter < 5)
	{
		printf("input which slot you want to save from 1 to 3 or 0 to exit without save: ");
		scanf_s("%d", &save_slot);
		if (save_slot == 1 || save_slot == 2 || save_slot == 3)
		{
			FILE* fp;
			if (save_slot == 1)
			{
				
				errno_t errorCode = fopen_s(&fp, "save1.txt", "w");
				if (fp == NULL)
				{
					return -1;
				}
				fprintf(fp, "%s\n", name);
				for (int i = 0; i < MAT; i++)
				{
					for (int j = 0; j < MAT; j++)
					{
						if (j == 3 && i < 3)
						{
							fprintf(fp, "%d\n", matrix[i][j]);
						}
						else if (j == 3 && i == 3)
						{
							fprintf(fp, "%d", matrix[i][j]);
						}
						else
						{
							fprintf(fp, "%d|", matrix[i][j]);
						}
					}
				}
				fclose(fp);
				return 1;
			}
			else if (save_slot == 2)
			{
				errno_t errorCode = fopen_s(&fp, "save2.txt", "w");
				if (fp == NULL)
				{
					return -1;
				}
				fprintf(fp, "%s\n", name);
				for (int i = 0; i < MAT; i++)
				{
					for (int j = 0; j < MAT; j++)
					{
						if (j == 3 && i < 3)
						{
							fprintf(fp, "%d\n", matrix[i][j]);
						}
						else if (j == 3 && i == 3)
						{
							fprintf(fp, "%d", matrix[i][j]);
						}
						else
						{
							fprintf(fp, "%d|", matrix[i][j]);
						}
					}
				}
				fclose(fp);
				return 1;
			}
			else if (save_slot == 3)
			{
				errno_t errorCode = fopen_s(&fp, "save3.txt", "w");
				if (fp == NULL)
				{
					return -1;
				}
				fprintf(fp, "%s\n", name);
				for (int i = 0; i < MAT; i++)
				{
					for (int j = 0; j < MAT; j++)
					{
						if (j == 3 && i < 3)
						{
							fprintf(fp, "%d\n", matrix[i][j]);
						}
						else if (j == 3 && i == 3)
						{
							fprintf(fp, "%d", matrix[i][j]);
						}
						else
						{
							fprintf(fp, "%d|", matrix[i][j]);
						}
					}
				}
				fclose(fp);
				return 1;
			}
			else
			{
				counter++;
				if (counter == 4)
				{
					exit(99);
				}
			}
		}
		else if (save_slot == 0)
		{
			auto_save(matrix,name);
			return 1;
		}
		else
		{
			return 99;
		}
	}
	
	return 1;
}
bool reach_end(int **matrix, int *arr)
{
	int counter = false;
	for (int i = 0; i < MAT; i++)
	{
		for (int j = 0; j < MAT; j++)
		{

			if (arr[9] == matrix[i][j])
			{
				counter = true;
				return counter;
			}
			else
			{
				counter = false;
			}

		}
	}
	return counter;
}
int adjust_matrix(int **matrix, int direct, int *arr)
{
	int pointer;
	int counter = 0, count = 0;
	if (reach_end(matrix, arr) == true)
	{
		return 2048;
	}
	if (direct == 1)//up
	{
		for (int i=0; i < 4; i++)
		{
			pointer = 3;
			//0 x x x
			if (matrix[pointer][i] == 0)
			{
				//0 0 x x 
				if (matrix[pointer - 1][i] == 0)
				{
					//0 0 0 x
					if (matrix[pointer - 2][i] == 0)
					{
						//0 0 0 0 -> 0 0 0 0
						
							if (count == 3)
							{
								return 89;
							}
							count++;
						
						//0 0 0 2 -> 0 0 0 2
					}
					//0 0 2 x
					else
					{
						//0 0 2 0 -> 0 0 0 2
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i];
							matrix[pointer - 2][i] = 0;
						}
						//0 0 2 2 -> 0 0 0 4
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = 0;
						}
						else
						{
							if (count == 3)
							{
								return 89;
							}
							count++;
						}
						//0 0 2 4 -> 0 0 2 4

					}
				}
				//0 2 x x
				else
				{
					//0 2 0 x
					if (matrix[pointer - 2][i] == 0)
					{
						//0 2 0 0 -> 0 0 0 2
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = 0;
						}
						//0 2 0 2 -> 0 0 0 4
						else if (matrix[pointer - 3][i] == matrix[pointer - 1][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 1][i] = 0;
						}
						//0 2 0 4 -> 0 0 2 4
						else
						{
							matrix[pointer - 2][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = 0;
						}
					}
					//0 2 2 x
					else if (matrix[pointer - 1][i] == matrix[pointer - 2][i])
					{
						//0 2 2 0 -> 0 0 0 4
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i] * 2;
							matrix[pointer - 1][i] = 0;
							matrix[pointer - 2][i] = 0;
						}
						//0 2 2 2 -> 0 0 2 4
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = 0;
						}
						//0 2 2 4 -> 0 0 4 4
						else
						{
							matrix[pointer - 2][i] = matrix[pointer - 2][i] * 2;
							matrix[pointer - 1][i] = 0;
						}
					}
					//0 2 4 x
					else
					{
						//0 2 4 0 -> 0 0 2 4
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i];
							matrix[pointer - 2][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = 0;
						}
						//0 2 4 4 -> 0 0 2 8
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = 0;
						}
						else
						{
							if (count == 3)
							{
								return 89;
							}
							count++;
						}
						//0 2 4 8 -> 0 2 4 8
					}
				}
			}
			//2 x x x
			else
			{
				//2 0 x x
				if (matrix[pointer - 1][i] == 0)
				{
					//2 0 0 x
					if (matrix[pointer - 2][i] == 0)
					{
						//2 0 0 0 -> 0 0 0 2
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 0 0 2 -> 0 0 0 4
						else if (matrix[pointer - 3][i] == matrix[pointer][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer][i] = 0;
						}
						//2 0 0 4 -> 0 0 2 4
						else
						{
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
					//2 0 2 x
					else if (matrix[pointer - 2][i] == matrix[pointer][i])
					{
						//2 0 2 0 -> 0 0 0 4
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i] * 2;
							matrix[pointer - 2][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 0 2 2 -> 0 0 2 4
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 0 2 4 -> 0 0 4 4
						else
						{
							matrix[pointer - 2][i] = matrix[pointer - 2][i] * 2;
							matrix[pointer][i] = 0;
						}
					}
					//2 0 4 x
					else
					{
						//2 0 4 0 -> 0 0 2 4
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i];
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 0 4 4 -> 0 0 2 8
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 0 4 2 -> 0 2 4 2
						else
						{
							matrix[pointer - 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
				}
				//2 2 x x
				else if (matrix[pointer - 1][i] == matrix[pointer][i])
				{
					//2 2 0 x
					if (matrix[pointer - 2][i] == 0)
					{
						//2 2 0 0 -> 0 0 0 4
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 1][i] * 2;
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 0 2 -> 0 0 2 4
						else if (matrix[pointer - 3][i] == matrix[pointer - 1][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 0 4 -> 0 0 4 4
						else
						{
							matrix[pointer - 2][i] = matrix[pointer - 1][i] * 2;
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
					}
					//2 2 2 x
					else if (matrix[pointer - 2][i] == matrix[pointer - 1][i])
					{
						//2 2 2 0 -> 0 0 2 4
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 2 2 -> 0 0 4 4
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer - 1][i] * 2;
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 2 4 -> 0 2 4 4
						else
						{
							matrix[pointer - 2][i] = matrix[pointer - 2][i] * 2;
							matrix[pointer - 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
					//2 2 4 x
					else
					{
						//2 2 4 0 -> 0 0 4 4
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i];
							matrix[pointer - 2][i] = matrix[pointer - 1][i] * 2;
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 4 4 -> 0 0 4 8
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer - 1][i] * 2;
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 4 2 -> 0 4 4 2
						else
						{
							matrix[pointer - 1][i] = matrix[pointer - 1][i] * 2;
							matrix[pointer][i] = 0;
						}
					}
					//2 4 x x
				}
				else
				{
					//2 4 0 x
					if (matrix[pointer - 2][i] == 0)
					{
						//2 4 0 0 -> 0 0 2 4
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 1][i];
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 4 0 4 -> 0 0 2 8
						else if (matrix[pointer - 3][i] == matrix[pointer - 1][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 4 0 2 -> 0 2 4 2
						else
						{
							matrix[pointer - 2][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
					//2 4 4 x
					else if (matrix[pointer - 2][i] == matrix[pointer - 1][i])
					{
						//2 4 4 0 -> 0 0 2 8
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer][i];
							matrix[pointer - 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 4 4 4 -> 0 2 4 8
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 4 4 2 -> 0 2 8 2
						else
						{
							matrix[pointer - 2][i] = matrix[pointer - 2][i] * 2;
							matrix[pointer - 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
					//2 4 2 x
					else
					{
						//2 4 2 0 -> 0 2 4 2
						if (matrix[pointer - 3][i] == 0)
						{
							matrix[pointer - 3][i] = matrix[pointer - 2][i];
							matrix[pointer - 2][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 4 2 2 -> 0 2 4 4
						else if (matrix[pointer - 3][i] == matrix[pointer - 2][i])
						{
							matrix[pointer - 3][i] = matrix[pointer - 3][i] * 2;
							matrix[pointer - 2][i] = matrix[pointer - 1][i];
							matrix[pointer - 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 4 2 4 -> 2 4 2 4
						else
						{
							if (counter == 3)
							{
								return 90;
// for movement control
							}
							if (count == 3)
							{
								return 89;
							}
							count++;
							counter++;
							//0 -> 1
							//1 -> 2
							//2 -> 3
							//3- > 4
						}
					}

				}
			}
		}
		
	}
	else if (direct == 2)// down
	{
		for (int i = 0; i < 4; i++)
		{
			pointer = 0;
			//0 x x x
			if (matrix[pointer][i] == 0)
			{
				//0 0 x x 
				if (matrix[pointer + 1][i] == 0)
				{
					//0 0 0 x
					if (matrix[pointer + 2][i] == 0)
					{
						//0 0 0 0 -> 0 0 0 0
						
							if (count == 3)
							{
								return 89;
							}
							count++;
						
						//0 0 0 2 -> 0 0 0 2
					}
					//0 0 2 x
					else
					{
						//0 0 2 0 -> 0 0 0 2
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i];
							matrix[pointer + 2][i] = 0;
						}
						//0 0 2 2 -> 0 0 0 4
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = 0;
						}
						else
						{
							if (count == 3)
							{
								return 89;
							}
							count++;
						}
						//0 0 2 4 -> 0 0 2 4

					}
				}
				//0 2 x x
				else
				{
					//0 2 0 x
					if (matrix[pointer + 2][i] == 0)
					{
						//0 2 0 0 -> 0 0 0 2
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = 0;
						}
						//0 2 0 2 -> 0 0 0 4
						else if (matrix[pointer + 3][i] == matrix[pointer + 1][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 1][i] = 0;
						}
						//0 2 0 4 -> 0 0 2 4
						else
						{
							matrix[pointer + 2][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = 0;
						}
					}
					//0 2 2 x
					else if (matrix[pointer + 1][i] == matrix[pointer + 2][i])
					{
						//0 2 2 0 -> 0 0 0 4
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i] * 2;
							matrix[pointer + 1][i] = 0;
							matrix[pointer + 2][i] = 0;
						}
						//0 2 2 2 -> 0 0 2 4
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = 0;
						}
						//0 2 2 4 -> 0 0 4 4
						else
						{
							matrix[pointer + 2][i] = matrix[pointer + 2][i] * 2;
							matrix[pointer + 1][i] = 0;
						}
					}
					//0 2 4 x
					else
					{
						//0 2 4 0 -> 0 0 2 4
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i];
							matrix[pointer + 2][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = 0;
						}
						//0 2 4 4 -> 0 0 2 8
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = 0;
						}
						else
						{
							if (count == 3)
							{
								return 89;
							}
							count++;
						}
						//0 2 4 8 -> 0 2 4 8
					}
				}
			}
			//2 x x x
			else
			{
				//2 0 x x
				if (matrix[pointer + 1][i] == 0)
				{
					//2 0 0 x
					if (matrix[pointer + 2][i] == 0)
					{
						//2 0 0 0 -> 0 0 0 2
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 0 0 2 -> 0 0 0 4
						else if (matrix[pointer + 3][i] == matrix[pointer][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer][i] = 0;
						}
						//2 0 0 4 -> 0 0 2 4
						else
						{
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
					//2 0 2 x
					else if (matrix[pointer + 2][i] == matrix[pointer][i])
					{
						//2 0 2 0 -> 0 0 0 4
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i] * 2;
							matrix[pointer + 2][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 0 2 2 -> 0 0 2 4
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 0 2 4 -> 0 0 4 4
						else
						{
							matrix[pointer + 2][i] = matrix[pointer + 2][i] * 2;
							matrix[pointer][i] = 0;
						}
					}
					//2 0 4 x
					else
					{
						//2 0 4 0 -> 0 0 2 4
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i];
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 0 4 4 -> 0 0 2 8
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 0 4 2 -> 0 2 4 2
						else
						{
							matrix[pointer + 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
				}
				//2 2 x x
				else if (matrix[pointer + 1][i] == matrix[pointer][i])
				{
					//2 2 0 x
					if (matrix[pointer + 2][i] == 0)
					{
						//2 2 0 0 -> 0 0 0 4
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 1][i] * 2;
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 0 2 -> 0 0 2 4
						else if (matrix[pointer + 3][i] == matrix[pointer + 1][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 0 4 -> 0 0 4 4
						else
						{
							matrix[pointer + 2][i] = matrix[pointer + 1][i] * 2;
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
					}
					//2 2 2 x
					else if (matrix[pointer + 2][i] == matrix[pointer + 1][i])
					{
						//2 2 2 0 -> 0 0 2 4
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 2 2 -> 0 0 4 4
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer + 1][i] * 2;
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 2 4 -> 0 2 4 4
						else
						{
							matrix[pointer + 2][i] = matrix[pointer + 2][i] * 2;
							matrix[pointer + 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
					//2 2 4 x
					else
					{
						//2 2 4 0 -> 0 0 4 4
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i];
							matrix[pointer + 2][i] = matrix[pointer + 1][i] * 2;
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 4 4 -> 0 0 4 8
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer + 1][i] * 2;
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 2 4 2 -> 0 4 4 2
						else
						{
							matrix[pointer + 1][i] = matrix[pointer + 1][i] * 2;
							matrix[pointer][i] = 0;
						}
					}
					//2 4 x x
				}
				else
				{
					//2 4 0 x
					if (matrix[pointer + 2][i] == 0)
					{
						//2 4 0 0 -> 0 0 2 4
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 1][i];
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 4 0 4 -> 0 0 2 8
						else if (matrix[pointer + 3][i] == matrix[pointer + 1][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 4 0 2 -> 0 2 4 2
						else
						{
							matrix[pointer + 2][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
					//2 4 4 x
					else if (matrix[pointer + 2][i] == matrix[pointer + 1][i])
					{
						//2 4 4 0 -> 0 0 2 8
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer][i];
							matrix[pointer + 1][i] = 0;
							matrix[pointer][i] = 0;
						}
						//2 4 4 4 -> 0 2 4 8
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 4 4 2 -> 0 2 8 2
						else
						{
							matrix[pointer + 2][i] = matrix[pointer + 2][i] * 2;
							matrix[pointer + 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
					}
					//2 4 2 x
					else
					{
						//2 4 2 0 -> 0 2 4 2
						if (matrix[pointer + 3][i] == 0)
						{
							matrix[pointer + 3][i] = matrix[pointer + 2][i];
							matrix[pointer + 2][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 4 2 2 -> 0 2 4 4
						else if (matrix[pointer + 3][i] == matrix[pointer + 2][i])
						{
							matrix[pointer + 3][i] = matrix[pointer + 3][i] * 2;
							matrix[pointer + 2][i] = matrix[pointer + 1][i];
							matrix[pointer + 1][i] = matrix[pointer][i];
							matrix[pointer][i] = 0;
						}
						//2 4 2 4 -> 2 4 2 4
						else
						{

							if (counter == 3)
							{
								return 90;// for movement control
							}
							if (count == 3)
							{
								return 89;
							}
							count++;
							counter++;
						}
					}

				}
			}
		}
		
	}
	else if (direct == 3)//left
	{
	for (int i = 0; i < 4; i++)
	{
		pointer = 3;
		//0 x x x
		if (matrix[i][pointer] == 0)
		{
			//0 0 x x 
			if (matrix[i][pointer - 1] == 0)
			{
				//0 0 0 x
				if (matrix[i][pointer - 2] == 0)
				{
					//0 0 0 0 -> 0 0 0 0
					
						if (count == 3)
						{
							return 89;
						}
						count++;
					
					//0 0 0 2 -> 0 0 0 2
				}
				//0 0 2 x
				else
				{
					//0 0 2 0 -> 0 0 0 2
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2];
						matrix[i][pointer - 2] = 0;
					}
					//0 0 2 2 -> 0 0 0 4
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = 0;
					}
					else
					{
						if (count == 3)
						{
							return 89;
						}
						count++;
					}
					//0 0 2 4 -> 0 0 2 4

				}
			}
			//0 2 x x
			else
			{
				//0 2 0 x
				if (matrix[i][pointer - 2] == 0)
				{
					//0 2 0 0 -> 0 0 0 2
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = 0;
					}
					//0 2 0 2 -> 0 0 0 4
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 1])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 1] = 0;
					}
					//0 2 0 4 -> 0 0 2 4
					else
					{
						matrix[i][pointer - 2] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = 0;
					}
				}
				//0 2 2 x
				else if (matrix[i][pointer - 1] == matrix[i][pointer - 2])
				{
					//0 2 2 0 -> 0 0 0 4
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2] * 2;
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer - 2] = 0;
					}
					//0 2 2 2 -> 0 0 2 4
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = 0;
					}
					//0 2 2 4 -> 0 0 4 4
					else
					{
						matrix[i][pointer - 2] = matrix[i][pointer - 2] * 2;
						matrix[i][pointer - 1] = 0;
					}
				}
				//0 2 4 x
				else
				{
					//0 2 4 0 -> 0 0 2 4
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2];
						matrix[i][pointer - 2] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = 0;
					}
					//0 2 4 4 -> 0 0 2 8
					else if (matrix[pointer - 3] == matrix[pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = 0;
					}
					else
					{
						if (count == 3)
						{
							return 89;
						}
						count++;
					}
					//0 2 4 8 -> 0 2 4 8
				}
			}
		}
		//2 x x x
		else
		{
			//2 0 x x
			if (matrix[i][pointer - 1] == 0)
			{
				//2 0 0 x
				if (matrix[i][pointer - 2] == 0)
				{
					//2 0 0 0 -> 0 0 0 2
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 0 0 2 -> 0 0 0 4
					else if (matrix[i][pointer - 3] == matrix[i][pointer])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer] = 0;
					}
					//2 0 0 4 -> 0 0 2 4
					else
					{
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
				//2 0 2 x
				else if (matrix[i][pointer - 2] == matrix[i][pointer])
				{
					//2 0 2 0 -> 0 0 0 4
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2] * 2;
						matrix[i][pointer - 2] = 0;
						matrix[i][pointer] = 0;
					}
					//2 0 2 2 -> 0 0 2 4
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 0 2 4 -> 0 0 4 4
					else
					{
						matrix[i][pointer - 2] = matrix[i][pointer - 2] * 2;
						matrix[i][pointer] = 0;
					}
				}
				//2 0 4 x
				else
				{
					//2 0 4 0 -> 0 0 2 4
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2];
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 0 4 4 -> 0 0 2 8
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 0 4 2 -> 0 2 4 2
					else
					{
						matrix[i][pointer - 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
			}
			//2 2 x x
			else if (matrix[i][pointer - 1] == matrix[i][pointer])
			{
				//2 2 0 x
				if (matrix[i][pointer - 2] == 0)
				{
					//2 2 0 0 -> 0 0 0 4
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 1] * 2;
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 0 2 -> 0 0 2 4
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 1])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 0 4 -> 0 0 4 4
					else
					{
						matrix[i][pointer - 2] = matrix[i][pointer - 1] * 2;
						matrix[i][pointer - 1] = 0;
						matrix[pointer][i] = 0;
					}
				}
				//2 2 2 x
				else if (matrix[i][pointer - 2] == matrix[i][pointer - 1])
				{
					//2 2 2 0 -> 0 0 2 4
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 2 2 -> 0 0 4 4
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer - 1] * 2;
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 2 4 -> 0 2 4 4
					else
					{
						matrix[i][pointer - 2] = matrix[i][pointer - 2] * 2;
						matrix[i][pointer - 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
				//2 2 4 x
				else
				{
					//2 2 4 0 -> 0 0 4 4
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2];
						matrix[i][pointer - 2] = matrix[i][pointer - 1] * 2;
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 4 4 -> 0 0 4 8
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer - 1] * 2;
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 4 2 -> 0 4 4 2
					else
					{
						matrix[i][pointer - 1] = matrix[i][pointer - 1] * 2;
						matrix[i][pointer] = 0;
					}
				}
				//2 4 x x
			}
			else
			{
				//2 4 0 x
				if (matrix[i][pointer - 2] == 0)
				{
					//2 4 0 0 -> 0 0 2 4
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 1];
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 4 0 4 -> 0 0 2 8
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 1])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 4 0 2 -> 0 2 4 2
					else
					{
						matrix[i][pointer - 2] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
				//2 4 4 x
				else if (matrix[i][pointer - 2] == matrix[i][pointer - 1])
				{
					//2 4 4 0 -> 0 0 2 8
					if (matrix[pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer];
						matrix[i][pointer - 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 4 4 4 -> 0 2 4 8
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 4 4 2 -> 0 2 8 2
					else
					{
						matrix[i][pointer - 2] = matrix[i][pointer - 2] * 2;
						matrix[i][pointer - 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
				//2 4 2 x
				else
				{
					//2 4 2 0 -> 0 2 4 2
					if (matrix[i][pointer - 3] == 0)
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 2];
						matrix[i][pointer - 2] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 4 2 2 -> 0 2 4 4
					else if (matrix[i][pointer - 3] == matrix[i][pointer - 2])
					{
						matrix[i][pointer - 3] = matrix[i][pointer - 3] * 2;
						matrix[i][pointer - 2] = matrix[i][pointer - 1];
						matrix[i][pointer - 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 4 2 4 -> 2 4 2 4
					else
					{

						if (counter == 3)
						{
							return 90;// for movement control
						}
						if (count == 3)
						{
							return 89;
						}
						count++;
						counter++;
					}
				}
			}
		}

	}
	}
	else if (direct == 4)//right 
	{
	for (int i = 0; i < 4; i++)
	{
		pointer = 0;
		//0 x x x
		if (matrix[i][pointer] == 0)
		{
			//0 0 x x 
			if (matrix[i][pointer + 1] == 0)
			{
				//0 0 0 x
				if (matrix[i][pointer + 2] == 0)
				{
					//0 0 0 0 -> 0 0 0 0
					
						if (count == 3)
						{
							return 89;
						}
						count++;
					
					//0 0 0 2 -> 0 0 0 2
				}
				//0 0 2 x
				else
				{
					//0 0 2 0 -> 0 0 0 2
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2];
						matrix[i][pointer + 2] = 0;
					}
					//0 0 2 2 -> 0 0 0 4
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = 0;
					}
					else
					{
						if (count == 3)
						{
							return 89;
						}
						count++;
					}
					//0 0 2 4 -> 0 0 2 4

				}
			}
			//0 2 x x
			else
			{
				//0 2 0 x
				if (matrix[i][pointer + 2] == 0)
				{
					//0 2 0 0 -> 0 0 0 2
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = 0;
					}
					//0 2 0 2 -> 0 0 0 4
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 1])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 1] = 0;
					}
					//0 2 0 4 -> 0 0 2 4
					else
					{
						matrix[i][pointer + 2] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = 0;
					}
				}
				//0 2 2 x
				else if (matrix[i][pointer + 1] == matrix[i][pointer + 2])
				{
					//0 2 2 0 -> 0 0 0 4
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2] * 2;
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer + 2] = 0;
					}
					//0 2 2 2 -> 0 0 2 4
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = 0;
					}
					//0 2 2 4 -> 0 0 4 4
					else
					{
						matrix[i][pointer + 2] = matrix[i][pointer + 2] * 2;
						matrix[i][pointer + 1] = 0;
					}
				}
				//0 2 4 x
				else
				{
					//0 2 4 0 -> 0 0 2 4
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2];
						matrix[i][pointer + 2] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = 0;
					}
					//0 2 4 4 -> 0 0 2 8
					else if (matrix[pointer + 3] == matrix[pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = 0;
					}
					else
					{
						if (count == 3)
						{
							return 89;
						}
						count++;
					}
					//0 2 4 8 -> 0 2 4 8
				}
			}
		}
		//2 x x x
		else
		{
			//2 0 x x
			if (matrix[i][pointer + 1] == 0)
			{
				//2 0 0 x
				if (matrix[i][pointer + 2] == 0)
				{
					//2 0 0 0 -> 0 0 0 2
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 0 0 2 -> 0 0 0 4
					else if (matrix[i][pointer + 3] == matrix[i][pointer])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer] = 0;
					}
					//2 0 0 4 -> 0 0 2 4
					else
					{
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
				//2 0 2 x
				else if (matrix[i][pointer + 2] == matrix[i][pointer])
				{
					//2 0 2 0 -> 0 0 0 4
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2] * 2;
						matrix[i][pointer + 2] = 0;
						matrix[i][pointer] = 0;
					}
					//2 0 2 2 -> 0 0 2 4
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 0 2 4 -> 0 0 4 4
					else
					{
						matrix[i][pointer + 2] = matrix[i][pointer + 2] * 2;
						matrix[i][pointer] = 0;
					}
				}
				//2 0 4 x
				else
				{
					//2 0 4 0 -> 0 0 2 4
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2];
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 0 4 4 -> 0 0 2 8
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 0 4 2 -> 0 2 4 2
					else
					{
						matrix[i][pointer + 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
			}
			//2 2 x x
			else if (matrix[i][pointer + 1] == matrix[i][pointer])
			{
				//2 2 0 x
				if (matrix[i][pointer + 2] == 0)
				{
					//2 2 0 0 -> 0 0 0 4
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 1] * 2;
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 0 2 -> 0 0 2 4
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 1])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 0 4 -> 0 0 4 4
					else
					{
						matrix[i][pointer + 2] = matrix[i][pointer + 1] * 2;
						matrix[i][pointer + 1] = 0;
						matrix[pointer][i] = 0;
					}
				}
				//2 2 2 x
				else if (matrix[i][pointer + 2] == matrix[i][pointer + 1])
				{
					//2 2 2 0 -> 0 0 2 4
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 2 2 -> 0 0 4 4
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer + 1] * 2;
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 2 4 -> 0 2 4 4
					else
					{
						matrix[i][pointer + 2] = matrix[i][pointer + 2] * 2;
						matrix[i][pointer + 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
				//2 2 4 x
				else
				{
					//2 2 4 0 -> 0 0 4 4
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2];
						matrix[i][pointer + 2] = matrix[i][pointer + 1] * 2;
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 4 4 -> 0 0 4 8
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer + 1] * 2;
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 2 4 2 -> 0 4 4 2
					else
					{
						matrix[i][pointer + 1] = matrix[i][pointer + 1] * 2;
						matrix[i][pointer] = 0;
					}
				}
				//2 4 x x
			}
			else
			{
				//2 4 0 x
				if (matrix[i][pointer + 2] == 0)
				{
					//2 4 0 0 -> 0 0 2 4
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 1];
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 4 0 4 -> 0 0 2 8
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 1])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 4 0 2 -> 0 2 4 2
					else
					{
						matrix[i][pointer + 2] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
				//2 4 4 x
				else if (matrix[i][pointer + 2] == matrix[i][pointer + 1])
				{
					//2 4 4 0 -> 0 0 2 8
					if (matrix[pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer];
						matrix[i][pointer + 1] = 0;
						matrix[i][pointer] = 0;
					}
					//2 4 4 4 -> 0 2 4 8
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 4 4 2 -> 0 2 8 2
					else
					{
						matrix[i][pointer + 2] = matrix[i][pointer + 2] * 2;
						matrix[i][pointer + 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
				}
				//2 4 2 x
				else
				{
					//2 4 2 0 -> 0 2 4 2
					if (matrix[i][pointer + 3] == 0)
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 2];
						matrix[i][pointer + 2] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 4 2 2 -> 0 2 4 4
					else if (matrix[i][pointer + 3] == matrix[i][pointer + 2])
					{
						matrix[i][pointer + 3] = matrix[i][pointer + 3] * 2;
						matrix[i][pointer + 2] = matrix[i][pointer + 1];
						matrix[i][pointer + 1] = matrix[i][pointer];
						matrix[i][pointer] = 0;
					}
					//2 4 2 4 -> 2 4 2 4
					else
					{
						
						if (counter == 3)
						{
							return 90;// for movement control
						}
						if (count == 3)
						{
							return 89;
						}
						count++;
						counter++;
					}
				}

			}
		}
	}
	}
	else
	{
		return 96;
	}
	return 1;
}
int check_for_end(int **matrix)
{
	int count = 1, error=0, c;

	while (count < 3)
	{
		c = control_matrix(matrix, count);
		if (c==90)
		{
			error++;
			count++;
		}
		else if (c == -2)
		{
			exit(97);
		}
		else
		{
			return 1;
			break;
		}

	}
	if (error == 2)
	{
		return 91;
	}
	else
	{
		return 1;
	}

	

}
int control_matrix(int **matrix, int count)
{
	int error = 0;
	if (count == 1)//up
	{
		for (int i = 3; i >= 0; i--)
		{
			for (int j = 3; j > 0; j--)
			{
				if (matrix[i][j] != matrix[i][j - 1])
				{
					error++;
					if (error == 12)
					{
						return 90;
					}
				}
				else
				{
					return 1;
				}
			}
		}
	
	}
	else if (count == 2)//left
	{
		for (int i = 3; i > 0; i--)
		{
			for (int j = 3; j >= 0; j--)
			{
				if (matrix[i][j] != matrix[i - 1][j])
				{
					error++;
					if (error == 12)
					{
						return 90;
					}
				}
				else
				{
					return 1;
				}
			}
		}

	}
	else
	{
		return -2;
	}
}
int matrix_add_2(int **matrix)
{
	int x, y, ret=1;
	bool controll = false;
	while (controll != true)
	{
		x = random_number(MAT);
		y = random_number(MAT);
		if (x < 5 && y < 5 && x>=0 && y>=0)
		{


			if (check_for_zero(matrix, x, y) == true)
			{
				matrix[x][y] = 2;
				controll = true;

			}

		}
		else
		{
			ret = 98;
		}
	}
	return ret;
}
bool check_for_zero(int **matrix, int x , int y)
{
	if (matrix[x][y] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int load_matrix(int **matrix, int save_slot)
{
	if (save_slot == 1 || save_slot == 2 || save_slot == 3)
	{
		FILE * open;
		if (save_slot == 1)
		{
			int i = 0, j = 0;
			int flag;
			char separators[] = "|";
			char *token1;
			char *token;
			char buffer[BUFFER_SIZE];
			errno_t errorCode = fopen_s(&open, "save1.txt", "r");
			if (open == NULL)
			{
				fclose(open);
				return -1;
			}
			while (fgets(buffer, BUFFER_SIZE, open))
			{
				if (j != 0)
				{
					if (i == 4)
					{
						fclose(open);
						break;
						return 1;
					}
					token = strtok_s(buffer, separators, &token1);
					flag = 0;
					while (token != NULL)
					{
						if (0 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (1 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (2 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (3 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else
						{
							fclose(open);
							return 95;
						}
						flag++;
						token = strtok_s(NULL, separators, &token1);
					}
					i++;
				}
				else
				{
					j++;
				}
			}
			fclose(open);
			return 1;
		}
		else if (save_slot == 2)
		{


			int i = 0, j = 0;
			int flag;
			char separators[] = "|";
			char *token1;
			char *token;
			char buffer[BUFFER_SIZE];
			errno_t errorCode = fopen_s(&open, "save2.txt", "r");
			if (open == NULL)
			{
				fclose(open);
				return -1;
			}
			while (fgets(buffer, BUFFER_SIZE, open))
			{
				if (j != 0)
				{
					if (i == 4)
					{
						fclose(open);
						break;
						return 1;
					}
					token = strtok_s(buffer, separators, &token1);
					flag = 0;
					while (token != NULL)
					{
						if (0 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (1 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (2 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (3 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else
						{
							fclose(open);
							return 95;
						}
						flag++;
						token = strtok_s(NULL, separators, &token1);
					}
					i++;
				}
				else
				{
					j++;
				}
			}
			fclose(open);
			return 1;
		}
		else if (save_slot == 3)
		{


			int i = 0, j = 0;
			int flag;
			char separators[] = "|";
			char *token1;
			char *token;
			char buffer[BUFFER_SIZE];
			errno_t errorCode = fopen_s(&open, "save3.txt", "r");
			if (open == NULL)
			{
				fclose(open);
				return -1;
			}
			while (fgets(buffer, BUFFER_SIZE, open))
			{
				if (j != 0)
				{
					if (i == 4)
					{
						fclose(open);
						break;
						return 1;
					}
					token = strtok_s(buffer, separators, &token1);
					flag = 0;
					while (token != NULL)
					{
						if (0 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (1 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (2 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else if (3 == flag)
						{
							matrix[i][flag] = (atoi(token));
						}
						else
						{
							fclose(open);
							return 95;
						}
						flag++;
						token = strtok_s(NULL, separators, &token1);
					}
					i++;
				}
				else
				{
					j++;
				}
			}
			fclose(open);
			return 1;
		}
		else
		{
			return 94;
		}

	}
	return 1;

}
actual_stats load_name(int save_slot)
{
	actual_stats name;
	FILE* open;
	char str[SIZE];
	if (save_slot == 1)
	{
		errno_t errorCode = fopen_s(&open, "save1.txt", "r");
		if (open == NULL)
		{
			name.score = -1;
			fclose(open);
			return name;
		}
		if (fscanf_s(open, "%s", str, SIZE) > 0)
		{
			strcpy_s(name.id, SIZE, str);
			fclose(open);
			return name;
		}
		else
		{
			name.score = -2;
			fclose(open);
			return name;
		}
	}
	if (save_slot == 2)
	{
		errno_t errorCode = fopen_s(&open, "save1.txt", "r");
		if (open == NULL)
		{
			name.score = -1;
			fclose(open);
			return name;
		}
		if (fscanf_s(open, "%s", str, SIZE) > 0)
		{
			strcpy_s(name.id, SIZE, str);
			fclose(open);
			return name;
		}
		else
		{
			name.score = -2;
			fclose(open);
			return name;
		}
	}
	if (save_slot == 3)
	{
		errno_t errorCode = fopen_s(&open, "save1.txt", "r");
		if (open == NULL)
		{
			name.score = -1;
			fclose(open);
			return name;
		}
		if (fscanf_s(open, "%s", str, SIZE) > 0)
		{
			strcpy_s(name.id, SIZE, str);
			fclose(open);
			return name;
		}
		else
		{
			name.score = -2;
			fclose(open);
			return name;
		}
	}
	else
	{
		name.score = -2;
		return name;
	}
}
int load_matrix_auto(int **matrix)
{
	
	FILE * open; 
	int i = 0, j = 0;
	int flag;
	char separators[] = "|";
	char *token1;
	char *token;
	char buffer[BUFFER_SIZE];
	errno_t errorCode = fopen_s(&open, "auto_save.txt", "r");
	if (open == NULL)
	{
		fclose(open);
		return -1;
	}
	while (fgets(buffer, BUFFER_SIZE, open))
	{
		if (j != 0)
		{
			if (i == 4)
			{
				fclose(open);
				break;
				return 1;
			}
			token = strtok_s(buffer, separators, &token1);
			flag = 0;
			while (token != NULL)
			{
				if (0 == flag)
				{
					matrix[i][flag] = (atoi(token));
				}
				else if (1 == flag)
				{
					matrix[i][flag] = (atoi(token));
				}
				else if (2 == flag)
				{
					matrix[i][flag] = (atoi(token));
				}
				else if (3 == flag)
				{
					matrix[i][flag] = (atoi(token));
				}
				else
				{
					fclose(open);
					return 95;
				}
				flag++;
				token = strtok_s(NULL, separators, &token1);
			}
			i++;
		}
		else
		{
			j++;
		}
	}
	fclose(open);
	return 1;
}
actual_stats load_name_auto()
{
	actual_stats name;
	FILE* open;
	char str[SIZE];
	errno_t errorCode = fopen_s(&open, "auto_save.txt", "r");
	if (open == NULL)
	{
		name.score = -1;
		fclose(open);
		return name;
	}
	if (fscanf_s(open, "%s", str, SIZE) > 0)
	{
		strcpy_s(name.id, SIZE, str);
		fclose(open);
		return name;
	}
	else
	{
		name.score = -2;
		fclose(open);
		return name;
	}
}
int load_intit_matrix(int **matrix)
{
	FILE * open;
	int i = 0, j = 0;
	int flag;
	char separators[] = "|";
	char *token1;
	char *token;
	char buffer[BUFFER_SIZE];
	errno_t errorCode = fopen_s(&open, "matrix.txt", "r");
	if (open == NULL)
	{
		fclose(open);
		return -1;
	}
	while (fgets(buffer, BUFFER_SIZE, open))
	{
		
			if (i == 4)
			{
				fclose(open);
				break;
				return 1;
			}
			token = strtok_s(buffer, separators, &token1);
			flag = 0;
			while (token != NULL)
			{
				if (0 == flag)
				{
					matrix[i][flag] = (atoi(token));
				}
				else if (1 == flag)
				{
					matrix[i][flag] = (atoi(token));
				}
				else if (2 == flag)
				{
					matrix[i][flag] = (atoi(token));
				}
				else if (3 == flag)
				{
					matrix[i][flag] = (atoi(token));
				}
				else
				{
					fclose(open);
					return 95;
				}
				flag++;
				token = strtok_s(NULL, separators, &token1);
			}
			i++;
		
	}
	fclose(open);
	return 1;
}

//-1 error in opening file
//-2 error in load name
// 99 gamemode error
// 89 user input == charater
//98 random error x || y 
//97 some error in control_matrix
//96 error in adjust matrx
//95 error in matrix
//94 error something wrong with load_matrix
//91 return for eng game
//90 return for not able to move up or down or left or right

