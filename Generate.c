#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "sudoku.h"

// Функция для проверки, можно ли поставить число в указанную ячейку
int isElementUnique(const int N, char (*pmatrix)[N], int currentRow, int currentCol, char value) {
    int blockSize = (int)sqrt(N); // Размер блока
    int blockRowStart = (currentRow / blockSize) * blockSize; // Начало строки блока
    int blockColStart = (currentCol / blockSize) * blockSize; // Начало столбца блока

    for (int i = 0; i < blockSize; i++) {
        for (int j = 0; j < blockSize; j++) {
            int row = blockRowStart + i;
            int col = blockColStart + j;

            // Пропускаем текущий элемент
            if (row == currentRow && col == currentCol) continue;

            if (pmatrix[row][col] == value) {
                return 0; // Найден повторяющийся элемент
            }
        }
    }
    return 1;
}

// Общая функция проверки
int check2(const int N, char (*pmatrix)[N], int currentRow, int currentCol, char value) {
    if (pmatrix[currentRow][currentCol] == value) {
        return 1;
    }

    // Проверка столбца
    for (int i = 0; i < N; i++) {
        if (pmatrix[i][currentCol] == value) {
            return 0;
        }
    }

    // Проверка строки
    for (int j = 0; j < N; j++) {
        if (pmatrix[currentRow][j] == value) {
            return 0;
        }
    }

    // Проверка блока
    return isElementUnique(N, pmatrix, currentRow, currentCol, value);
}

// Функция для решения судоку
bool solveSudoku(int N, char (*pmatrix)[N], int row, int col) {
    if (row == N - 1 && col == N) {
        return true;
    }

    if (col == N) {
        row++;
        col = 0;
    }

    if (pmatrix[row][col] != '.') {
        return solveSudoku(N, pmatrix, row, col + 1);
    }

    for (char num = '1'; num <= '0' + N; num++) {
        if (check2(N, pmatrix, row, col, num)) {
            pmatrix[row][col] = num;
            if (solveSudoku(N, pmatrix, row, col + 1)) {
                return true;
            }
            pmatrix[row][col] = '.'; // Возврат назад
        }
    }

    return false;
}

// Функция для генерации судоку
bool generateSudoku(int N, char (*pmatrix)[N], int row, int col) {
    if (row == N - 1 && col == N) {
        return true; // Все ячейки заполнены
    }

    if (col == N) {
        row++;
        col = 0;
    }

    // Пропускаем заполненные ячейки
    if (pmatrix[row][col] != '.') {
        return generateSudoku(N, pmatrix, row, col + 1);
    }

    char nums[N];
    for (int i = 0; i < N; i++) {
        nums[i] = '1' + i;
    }

    // Перемешиваем числа
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    // Пробуем вставить числа
    for (int i = 0; i < N; i++) {
        char num = nums[i];
        if (check2(N, pmatrix, row, col, num)) {
            pmatrix[row][col] = num;

            // Отладочный вывод текущей матрицы
            // printf("Заполняем ячейку (%d, %d) значением %c:\n", row, col, num);
            // for (int x = 0; x < N; x++) {
            //     for (int y = 0; y < N; y++) {
            //         printf("%c ", pmatrix[x][y]);
            //     }
            //     printf("\n");
            // }
            // printf("--------------------\n");

            if (generateSudoku(N, pmatrix, row, col + 1)) {
                return true;
            }

            // Возврат назад
            pmatrix[row][col] = '.';
        }
    }

    return false;
}

// Функция для удаления элементов с проверкой на уникальность
void removeElements(int N, char (*pmatrix)[N], char numToRemove) {
    while (numToRemove > 0) {
        int row = rand() % N;
        int col = rand() % N;

        if (pmatrix[row][col] != '.') {
            char backup = pmatrix[row][col];
            pmatrix[row][col] = '.';

            // Копируем матрицу
            char tempMatrix[N][N];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    tempMatrix[i][j] = pmatrix[i][j];
                }
            }

            if (!solveSudoku(N, tempMatrix, 0, 0)) {
                pmatrix[row][col] = backup; // Возврат назад
            } else {
                numToRemove--;
            }
        }
    }
}
