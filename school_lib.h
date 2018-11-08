#pragma once
//Vytvoreni dynamicke 2D matice
int **createMatrix(int m, int n);
//Naplneni matice nulami
void initMatrix(int **matrix, int m, int n);
//Nastaveni kurzoru v konzoli na pozici x = sloupce, y = radky
void setCursorPosition(int x, int y);
//Tisk matice + nastaveni barev v konzoli
void printMatrix(int **matrix, int m, int n);
//Vyprazdneni pameti od alokovane matice
void deleteMatrix(int **matrix, int m);
//Tisk bodu do koonzoloveho okna
void printPoint(int **matrix, int *mActual, int *nActual, int mOld, int nOld);
//Posun bodu dle stisknute klavesy, s ochranou proti vstupu mimo oblast hraciho pole
void moveNumber(int **matrix, int m, int n, char d, int *mActual, int *nActual);
//Jednoduchy casovac zajistujici pocatecni zpozdeni
int simpleTimer(int n_seconds);
//funkce pro skryti kursoru v konzoli
void showConsoleCursor(bool showFlag);