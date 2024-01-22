#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 9
#define NUM_THREADS 11

typedef struct {
    int row;
    int column;
} parameters;

int sudoku[GRID_SIZE][GRID_SIZE] = {
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
};
int results[NUM_THREADS] = {0};

void* checkRows(void* param);
void* checkColumns(void* param);
void* checkSubgrid(void* param);
int isValidSudoku();
int isUnique(int arr[GRID_SIZE]);

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIndex = 0;

    pthread_create(&threads[threadIndex++], NULL, checkRows, NULL);
    pthread_create(&threads[threadIndex++], NULL, checkColumns, NULL);

    for (int row = 0; row < GRID_SIZE; row += 3) {
        for (int col = 0; col < GRID_SIZE; col += 3) {
            parameters *data = (parameters *) malloc(sizeof(parameters));
            data->row = row;
            data->column = col;
            pthread_create(&threads[threadIndex], NULL, checkSubgrid, data);
            threadIndex++;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    if (isValidSudoku()) {
        printf("Sudoku solution is valid.\n");
    } else {
        printf("Sudoku solution is invalid.\n");
    }

    return 0;
}

void* checkRows(void* param) {
    for (int row = 0; row < GRID_SIZE; row++) {
        int rowArray[GRID_SIZE];
        for (int col = 0; col < GRID_SIZE; col++) {
            rowArray[col] = sudoku[row][col];
        }
        if (isUnique(rowArray)) {
            results[0] = 1;
        } else {
            results[0] = 0;
            return NULL;
        }
    }
    return NULL;
}

void* checkColumns(void* param) {
    for (int col = 0; col < GRID_SIZE; col++) {
        int colArray[GRID_SIZE];
        for (int row = 0; row < GRID_SIZE; row++) {
            colArray[row] = sudoku[row][col];
        }
        if (isUnique(colArray)) {
            results[1] = 1;
        } else {
            results[1] = 0;
            return NULL;
        }
    }
    return NULL;
}

void* checkSubgrid(void* param) {
    parameters *p = (parameters *) param;
    int rowStart = p->row;
    int colStart = p->column;
    free(param);

    int subgridArray[GRID_SIZE];
    int index = 0;

    for (int row = rowStart; row < rowStart + 3; row++) {
        for (int col = colStart; col < colStart + 3; col++) {
            subgridArray[index++] = sudoku[row][col];
        }
    }

    if (isUnique(subgridArray)) {
        results[rowStart + colStart / 3 + 2] = 1;
    } else {
        results[rowStart + colStart / 3 + 2] = 0;
        return NULL;
    }
    return NULL;
}

int isUnique(int arr[GRID_SIZE]) {
    int checker[GRID_SIZE + 1] = {0};
    for (int i = 0; i < GRID_SIZE; i++) {
        if (checker[arr[i]] == 1) return 0;
        checker[arr[i]] = 1;
    }
    return 1;
}

int isValidSudoku() {
    for (int i = 0; i < NUM_THREADS; i++) {
        if (results[i] == 0) {
            return 0;
        }
    }
    return 1;
}

