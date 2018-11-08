#pragma once
#include "pch.h"
#include "school_lib.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <iostream>

#define SIZE 21 
#define MAT 4
typedef struct actual_stats {
	char id[SIZE];
	int score;
}actual_stats;
typedef struct all_stats {
	struct obj_t *obj;
}all_stats;
char show_menu();
int random_number(int max_number);
int initialization_file();
void statistics_write(char *name, int score);
int statistics_show();
void add_stat(char *name, int score);
