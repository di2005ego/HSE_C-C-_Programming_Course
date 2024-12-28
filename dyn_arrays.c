#define _CRT_SECURE_NO_WARNINGS
#define TASK_9

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>

#ifdef TASK_1
int* func(int **matrix, int m, int n)
{
	int* result = (int*)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) {
		result[i] = 0;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			result[i] += matrix[i][j];
		}
	}
	return result;
	free(result);
}
int main() {
	int m, n, i, j = 0;
	int **input_matrix;
	int *output_result;
	printf("The number of rows and columns of the matrix separated by a space: ");
	scanf("%d %d", &m, &n);
	input_matrix = (int**)malloc(m * sizeof(int*));
	for (i = 0; i < m; i++) {
		input_matrix[i] = (int*)malloc(n * sizeof(int));
	}
	output_result = malloc(m * sizeof(int));
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &input_matrix[i][j]);
		}
	}
	output_result = func(input_matrix, m, n);
	for (i = 0; i < m; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_2
int* func(int** matrix, int m, int n)
{
	int* result = (int*)malloc(n * sizeof(int));
	for (int j = 0; j < n; j++) {
		result[j] = 0;
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			if (matrix[i][j] > result[j]) {
				result[j] = matrix[i][j];
			}
		}
	}
	return result;
	free(result);
}
int main() {
	int m, n, i, j = 0;
	int** input_matrix;
	int* output_result;
	printf("The number of rows and columns of the matrix separated by a space: ");
	scanf("%d %d", &m, &n);
	input_matrix = (int**)malloc(m * sizeof(int*));
	for (i = 0; i < m; i++) {
		input_matrix[i] = (int*)malloc(n * sizeof(int));
	}
	output_result = malloc(n * sizeof(int));
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &input_matrix[i][j]);
		}
	}
	output_result = func(input_matrix, m, n);
	for (i = 0; i < n; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_3
int* func(int** matrix, int m, int n)
{
	int* result = (int*)malloc(n * sizeof(int));
	for (int j = 0; j < n; j++) {
		result[j] = 0;
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			result[j] += matrix[i][j];
		}
	}
	return result;
	free(result);
}
int main() {
	int m, n, i, j = 0;
	int** input_matrix;
	int* output_result;
	printf("The number of rows and columns of the matrix separated by a space: ");
	scanf("%d %d", &m, &n);
	input_matrix = (int**)malloc(m * sizeof(int*));
	for (i = 0; i < m; i++) {
		input_matrix[i] = (int*)malloc(n * sizeof(int));
	}
	output_result = malloc(n * sizeof(int));
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &input_matrix[i][j]);
		}
	}
	output_result = func(input_matrix, m, n);
	for (i = 0; i < n; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_4
int* func(int** matrix, int n)
{
	int* result = (int*)malloc(((n-1)/2)*n * sizeof(int));
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i < j) {
				result[k] = matrix[i][j];
				k += 1;
			}
		}
	}
	return result;
	free(result);
}
int main() {
	int n, i, j = 0;
	int** input_matrix;
	int* output_result;
	printf("The number of rows and columns of the square matrix: ");
	scanf("%d", &n);
	input_matrix = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		input_matrix[i] = (int*)malloc(n * sizeof(int));
	}
	output_result = malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &input_matrix[i][j]);
		}
	}
	output_result = func(input_matrix, n);
	for (i = 0; i < ((n - 1) / 2) * n; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_5
int* func(int** matrix, int m, int n)
{
	int* result = (int*)malloc(n * sizeof(int));
	for (int j = 0; j < n; j++) {
		result[j] = 1;
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			result[j] *= matrix[i][j];
		}
}
	return result;
	free(result);
}
int main() {
	int m, n, i, j = 0;
	int** input_matrix;
	int* output_result;
	printf("The number of rows and columns of the matrix separated by a space: ");
	scanf("%d %d", &m, &n);
	input_matrix = (int**)malloc(m * sizeof(int*));
	for (i = 0; i < m; i++) {
		input_matrix[i] = (int*)malloc(n * sizeof(int));
	}
	output_result = malloc(n * sizeof(int));
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &input_matrix[i][j]);
		}
	}
	output_result = func(input_matrix, m, n);
	for (i = 0; i < n; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_6
int* func(int** matrix, int n)
{
	int* result = (int*)malloc(n * sizeof(int));
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				result[k] = matrix[i][j];
				k += 1;
}
		}
	}
	return result;
	free(result);
}
int main() {
	int n, i, j = 0;
	int** input_matrix;
	int* output_result;
	printf("The number of rows and columns of the square matrix: ");
	scanf("%d", &n);
	input_matrix = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		input_matrix[i] = (int*)malloc(n * sizeof(int));
	}
	output_result = malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &input_matrix[i][j]);
		}
	}
	output_result = func(input_matrix, n);
	for (i = 0; i < n; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_7
int* func(int** matrix, int m, int n)
{
	int* result = (int*)malloc(n * sizeof(int));
	for (int j = 0; j < n; j++) {
		result[j] = 0;
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			if (matrix[i][j] > result[j]) {
				result[j] = matrix[i][j];
	}
		}
	}
	return result;
	free(result);
}
int main() {
	int m, n, i, j = 0;
	int** input_matrix;
	int* output_result;
	printf("The number of rows and columns of the matrix separated by a space: ");
	scanf("%d %d", &m, &n);
	input_matrix = (int**)malloc(m * sizeof(int*));
	for (i = 0; i < m; i++) {
		input_matrix[i] = (int*)malloc(n * sizeof(int));
	}
	output_result = malloc(n * sizeof(int));
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &input_matrix[i][j]);
		}
	}
	output_result = func(input_matrix, m, n);
	for (i = 0; i < n; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_8
int* func(int** matrix, int m, int n)
{
	int* result = (int*)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) {
		result[i] = 2147483647;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] < result[i]) {
				result[i] = matrix[i][j];
			}
		}
}
	return result;
	free(result);
}
int main() {
	int m, n, i, j = 0;
	int** input_matrix;
	int* output_result;
	printf("The number of rows and columns of the matrix separated by a space: ");
	scanf("%d %d", &m, &n);
	input_matrix = (int**)malloc(m * sizeof(int*));
	for (i = 0; i < m; i++) {
		input_matrix[i] = (int*)malloc(n * sizeof(int));
	}
	output_result = malloc(m * sizeof(int));
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &input_matrix[i][j]);
		}
	}
	output_result = func(input_matrix, m, n);
	for (i = 0; i < m; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_9
int* func(int* input_massive1, int* input_massive2, int n)
{
	int* result = (int*)malloc(2*n * sizeof(int));
	for (int i = 0; i < 2*n; i++) {
		result[i] = 0;
	}
	for (int i = 0; i < 2*n; i++) {
		if (i % 2 == 0) {
			result[i] = input_massive1[i/2];
		}
		else {
			result[i] = input_massive2[i/2];
		}
	}
	return result;
	free(result);
}
int main() {
	int n, i, j = 0;
	int* input_massive1;
	int* input_massive2;
	int* output_result;
	printf("Enter the size of the two arrays: ");
	scanf("%d", &n);
	input_massive1 = (int*)malloc(n * sizeof(int*));
	input_massive2 = (int*)malloc(n * sizeof(int*));
	output_result = malloc(2*n * sizeof(int));
	for (i = 0; i < n; i++) {
		scanf("%d", &input_massive1[i]);
	}
	for (j = 0; j < n; j++) {
		scanf("%d", &input_massive2[j]);
	}
	output_result = func(input_massive1, input_massive2, n);
	for (i = 0; i < 2*n; i++) {
		printf("%d ", output_result[i]);
	}
	free(output_result);
	return 0;
}
#endif

#ifdef TASK_10
void output_matrix(int A[2][2], int B[2][2], int C[2][2], int D[2][2]) {
    int result[4][4];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = A[i][j];
            result[i][j + 2] = B[i][j];
            result[i + 2][j] = C[i][j];
            result[i + 2][j + 2] = D[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int A[2][2], B[2][2], C[2][2], D[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &C[i][j]);
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &D[i][j]);
        }
    }
    output_matrix(A, B, C, D);
    return 0;
}
#endif