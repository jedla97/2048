//xjedli24
#include "our_lib.h"


char show_menu()
{
	printf("welcome in our 2048\n\n\n");
	printf("1. new game \n");
	printf("2. continue\n");
	printf("3. load game\n");
	printf("4. statistics\n");
	printf("5. close 2048\n\n");
	printf("press number which corresponds your next step e.g 1 for new game : ");
	return 1;
	
}
int random_number(int max_number)
{
	int x = 0; 
	x = rand() % max_number;
	return x;
}
int initialization_file()
{
	int x = 0, y = 0;
	srand(time(NULL));
	x = random_number(5);
	y = random_number(5);
	FILE *opening;
	errno_t errorCode = fopen_s(&opening, "start.txt", "w");
	fprintf(opening, "%d \n", x);
	fprintf(opening, "%d", y);
	fclose(opening);
	return 1;
}
void statistics_write(char *name, int score)
{
	FILE *open;
	errno_t errorCode = fopen_s(&open, "statistics_name.txt", "a+");
	fprintf(open, "%s	|	%d \n", name, score);
	fclose(open);

}

int statistics_show()
{
	struct actual_stats *arr;
	FILE *open;
	char name[50];
	int i;
	errno_t errorCode = fopen_s(&open, "statistics.txt", "r");
	arr = (struct actual_stats *) malloc(sizeof(actual_stats) * 10);
	for (i = 0; i < 10; i++)
	{
		if (fgets(name, 100, open) != NULL)
		{
			if (sscanf(name, "%s %d", &arr->id , &arr->score ) < 2);
		}

	}
}

void add_stat(char *name, int score)
{
	struct actual_stats *st;
	int newsize = sizeof(struct actual_stats*);
	st = (struct actual_stats *) malloc(sizeof(actual_stats));
	strcpy_s(st->id, SIZE, name);
	st->score = score;
	statistics_write(st->id, st->score);
	free(st);
}

