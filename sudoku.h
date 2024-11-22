#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

// Объявления функций
int isElementUnique(const int N, char (*pmatrix)[N], int currentRow, int currentCol, char value);
int check2(const int N, char (*pmatrix)[N], int currentRow, int currentCol, char value);
bool solveSudoku(int N, char (*pmatrix)[N], int row, int col);
bool generateSudoku(int N, char (*pmatrix)[N], int row, int col);
void removeElements(int N, char (*pmatrix)[N], char numToRemove);

#endif // SUDOKU_H
