#pragma once
#define SIZE 21 
#define MAT 4
#define BUFFER_SIZE 100
typedef struct actual_stats {
	char id[SIZE];
	int score;
}actual_stats;
actual_stats save_to_structure(char* str, int counter);
actual_stats load_name(int save_slot);
actual_stats load_name_auto();
void credits();
int show_menu();
int random_number(int max_number);
void statistics_write(char *name, int score);
void statistics_rewrite(char *name, int score);
void add_stat(char *name, int score);
void print(actual_stats* arr, int size);
int show_stat();
int compare(const void* l, const void* r);
int score(int **matrix, int *arr);
int save(int **matrix, char *name);
bool reach_end(int **matrix, int *arr);
int adjust_matrix(int **matrix, int direct, int *arr);
int check_for_end(int **matrix);
int control_matrix(int **matrix, int count);
int matrix_add_2(int **matrix);
bool check_for_zero(int **matrix, int x, int y);
void change_stat_txt(actual_stats* arr);
int load_matrix(int **matrix, int save_slot);
int load_matrix_auto(int **matrix);
int auto_save(int **matrix, char *name);
int load_intit_matrix(int **matrix);