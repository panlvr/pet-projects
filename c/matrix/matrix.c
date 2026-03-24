#include <stdio.h>
#include <stdlib.h>

int input (int *choice, int *rows, int *cols);
int stat(int data[][100], int rows, int cols);
int ptp(int **data, int rows, int cols);
int flat_array(int *data, int rows, int cols);
int block_array(int **data, int *block, int rows, int cols);


int main (void) {
    int choice, rows, cols;
    int flag = input(&choice, &rows, &cols);
    if (flag != 1) {
        if (choice == 1) {
            int data[100][100];
            if(stat(data, rows, cols) != 0) {
                return 0;
            }
        }
    } else if (choice == 2) {
        int **data = malloc(rows * sizeof(int *));
        if (data == NULL) {
            printf("n/a");
            free(data);
            return 0;
        }
        for (int i = 0; i < rows; i++) {
            data[i] = malloc(cols * (sizeof(int)));
            if (data[i] == NULL) {
                printf("n/a");
                for (int k = 0; k < i; k ++) {
                    free(data[k]);
                }
                free(data);
                return 0;
            }
        }
        if (ptp(data, rows, cols) != 0) {
            for (int i = 0; i < rows; i++) {
                free(data[i]);
            }
            free(data);
            return 0;
        }
        for (int i = 0; i < rows; i++) {
            free(data[i]);
        }
        free(data);
    } else if (choice == 3) {
        int *data = malloc(rows * cols * sizeof(int));
        if (data == NULL) {
            free(data);
            printf("n/a");
            return 0;
        }
        if (flat_array(data, rows, cols) != 0) {
            free(data);
            return 0;
        }
        free(data);
    } else if (choice == 4) {
        int **data = malloc(rows * sizeof(int *));
        int *block = malloc(rows * cols * sizeof(int));
        if (data == NULL || block == NULL) {
            printf("n/a");
            free(data);
            free(block);
            return 0;
        }
        if (block_array(data, block, rows, cols) != 0) {
            free(block);
            free(data);
            return 0;
        }
        free(block);
        free(data);
    }
    return 0;
}

int input (int *choice, int *rows, int *cols) {
    int flag = 0;
    if (scanf("%d", choice) != 1 || *choice < 1 || *choice > 4) {
        printf("n/a");
        flag = 1;
    }
    if (flag == 0) {
        if (scanf("%d %d", rows, cols) != 2 || *rows <= 0 || *cols <= 0) {
            printf("n/a");
            flag = 1;
        }
    }
    return flag;
}

int stat(int data[][100], int rows, int cols) {
    if (rows > 100 || cols > 100) {
        printf("n/a");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%i", &data[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j < cols - 1) {
                printf("%i ", data[i][j]);
            } else {
                printf("%i", data[i][j]);
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}

int ptp(int **data, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%i", &data[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j < cols - 1) {
                printf("%i ", data[i][j]);
            } else {
                printf("%i", data[i][j]);
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}

int flat_array(int *data, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%i", &data[i * cols + j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j < cols - 1) {
                printf("%i ", data[i * cols + j]);
            } else {
                printf("%i", data[i * cols + j]);
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}

int block_array (int **data, int *block, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        data[i] = block + i * cols;
        for (int j = 0; j < cols; j++) {
            if (scanf("%i", &data[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j < cols - 1) {
                printf("%i ", data[i][j]);
            } else {
                printf("%i", data[i][j]);
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}