#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "sudoku.h"
#include <stdbool.h>
#include <time.h>

// Устанавливаем зелёный цвет для консоли
void setGreenText() {
    printf("\033[1;32m");
}

// Сбрасываем цвет на стандартный
void resetTextColor() {
    printf("\033[0m");
}

// Функция для чтения строки
char* getString() {
    int len = 0;
    int capacity = 1;
    char *str = (char *) calloc(capacity, sizeof(char));

    char c = getchar();

    // Читаем строку до символа новой строки
    while (c != '\n' && c != EOF) {
        str[len++] = c;

        // Увеличиваем размер массива, если нужно
        if (len >= capacity) {
            capacity *= 2;
            str = (char *) realloc(str, capacity * sizeof(char));
            if (str == NULL) {
                // Если realloc вернул NULL, то произошла ошибка
                printf("Ошибка выделения памяти.\n");
                exit(1);
            }
        }

        c = getchar();
    }

    str[len] = '\0';  // Завершаем строку
    return str;
}

// Функция для чтения массива
void readArray(char *array, int size) {
    char *buffer = getString();  // Получаем строку с числами
    int i = 0;

    // Разделяем строку на числа и заполняем массив
    char *token = strtok(buffer, " ");
    while (token != NULL && i < size) {
        array[i++] = *token;
        token = strtok(NULL, " ");
    }
    free(buffer);  // Освобождаем память, выделенную под строку
}

// Функция для печати матрицы
void printMatrix(const int N, char (*pmatrix)[N], int (*pcolor)[N], int currentRow, int currentCol) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == currentRow && j == currentCol) {
                printf("[%c]", pmatrix[i][j]); // Выделение текущего элемента
            } else if (pmatrix[i][j] != '.' && pcolor[i][j] == 0) {
                setGreenText(); // Зелёный цвет для чисел, которые уже сохранены
                printf(" %c ", pmatrix[i][j]);
                resetTextColor();
            } else {
                printf(" %c ", pmatrix[i][j]);
            }
        }
        printf("\n");
    }
}

// Функция для считывания клавиатуры
char GetChar() {
    struct termios oldt, newt;
    char ch;

    // Получение текущих настроек терминала
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Отключение канонического режима и вывода символов в консоль
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Считывание одного символа
    ch = getchar();

    // Восстановление старых настроек терминала
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

// Функция для замены элемента
void Replace(const int N, char (*pmatrix)[N], int currentRow, int currentCol, char value) {
    pmatrix[currentRow][currentCol] = value;
}

// Функция для проверки уникальности в блоке
int isElementUniqueInBlock(const int N, char (*pmatrix)[N], int currentRow, int currentCol, char value) {
    int blockSize = (int)sqrt(N); // Размер блока
    int blockRowStart = (currentRow / blockSize) * blockSize; // Начало строки блока
    int blockColStart = (currentCol / blockSize) * blockSize; // Начало столбца блока

    for (int i = 0; i < blockSize; i++) {
        for (int j = 0; j < blockSize; j++) {
            int row = blockRowStart + i; // Текущая строка в блоке
            int col = blockColStart + j; // Текущий столбец в блоке

            // Пропускаем сравнение элемента с самим собой
            if (row == currentRow && col == currentCol) {
                continue;
            }

            if (pmatrix[row][col] == value) {
                return 0; // Найден повторяющийся элемент
            }
        }
    }
    return 1;
}

// Общая функция проверки
int check(const int N, char (*pmatrix)[N], int currentRow, int currentCol, char value) {
    if (pmatrix[currentRow][currentCol] == value) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (pmatrix[i][currentCol] == value) {
            return 0;
        }
    }

    for (int j = 0; j < N; j++) {
        if (pmatrix[currentRow][j] == value) {
            return 0;
        }
    }

    return isElementUniqueInBlock(N, pmatrix, currentRow, currentCol, value);
}

// Функция для печати матрицы с текущим процессом перебора
void printMatrixWithGreen(const int N, char (*pmatrix)[N], int (*pcolor)[N], int currentRow, int currentCol, char value) {
    system("clear"); // Очистка консоли для обновления состояния

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == currentRow && j == currentCol) {
                setGreenText(); // Зелёный цвет для текущего элемента
                printf(" %c ", value);
                resetTextColor();
            } else if (pmatrix[i][j] != '.' && pcolor[i][j] == 0) {
                setGreenText(); // Зелёный цвет для чисел, которые уже сохранены
                printf(" %c ", pmatrix[i][j]);
                resetTextColor();
            } else {
                printf(" %c ", pmatrix[i][j]);
            }
        }
        printf("\n");
    }
    usleep(90000); // Задержка для визуализации (90 мс)
}

// Рекурсивная функция для перебора всех возможных чисел на местах с '.'
bool tryAllValues(const int N, char (*pmatrix)[N], int (*pcolor)[N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (pmatrix[row][col] == '.') { // Найти пустую ячейку
                for (char value = '1'; value <= '9'; value++) {
                    if (check(N, pmatrix, row, col, value)) {
                        pmatrix[row][col] = value; // Поставить значение
                        printMatrixWithGreen(N, pmatrix, pcolor, row, col, value); // Печать текущего состояния

                        if (tryAllValues(N, pmatrix, pcolor)) {
                            return true; // Если решение найдено, вернуть true
                        }

                        pmatrix[row][col] = '.'; // Вернуться назад
                        printMatrixWithGreen(N, pmatrix, pcolor, row, col, value); // Печать текущего состояния
                    }
                }
                return false; // Если не найдено подходящее значение, вернуть false
            }
        }
    }
    return true; // Если все ячейки заполнены, вернуть true
}

int main() {
    srand(time(NULL));
    int N, mode;
    printf("Введите размерность (Число стороны квадрата): \n");
    scanf("%d", &N);

    char matrix[N][N];
    int color[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = '.'; // Заполняем массив символами '.'
            color[i][j] = 1;
        }
    }

    int currentRow = 0, currentCol = 0;
    char (*pmatrix)[N] = matrix;

    printf("Пользовательский ввод(1) или сгенерированный(2): \n");
    scanf("%d", &mode);

    if (mode == 1) {
        printf("Введите числа (через пробел): \n");

        for (int i = 0; i < N; i++) {
            readArray(matrix[i], N);
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (matrix[i][j] == '.') {
                    color[i][j] = 0;
                }
            }
        }
    } else {
        int numToRemove;
        printf("Какое количество символов убрать: \n");
        scanf("%d", &numToRemove);
        generateSudoku(N, pmatrix, 0, 0);
        removeElements(N, pmatrix, numToRemove);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == '.') {
                color[i][j] = 0;
            }
        }
    }
    int (*pcolor)[N] = color;

    printMatrix(N, pmatrix, pcolor, currentRow, currentCol);
    char key;

    while (1) {
        system("clear");

        printf("Используйте WASD для перемещения по матрице. Нажмите 'q' для выхода, а 'b' для автоматического решения \n");
        printf("\n");

        printMatrix(N, pmatrix, pcolor, currentRow, currentCol);

        key = GetChar();

        if (key == 'q') {
            break; // Выход из программы
        }

        switch (key) {
            case 'w': // Вверх
            case 'W':
                if (currentRow > 0) currentRow--;
                break;
            case 's': // Вниз
            case 'S':
                if (currentRow < N - 1) currentRow++;
                break;
            case 'a': // Влево
            case 'A':
                if (currentCol > 0) currentCol--;
                break;
            case 'd': // Вправо
            case 'D':
                if (currentCol < N - 1) currentCol++;
                break;
            case '.':
                Replace(N, pmatrix, currentRow, currentCol, '.');
                break;
            case 'b':
            case 'B':
                tryAllValues(N, pmatrix, pcolor);
                break;
        }

        if (key >= '1' && key <= '9') {
            if (check(N, pmatrix, currentRow, currentCol, key)) {
                Replace(N, pmatrix, currentRow, currentCol, key);
            } else {
                Replace(N, pmatrix, currentRow, currentCol, 'X');
            }
        }
    }

    printf("\n");
    printf("Программа завершена.\n");

    return 0;
}
