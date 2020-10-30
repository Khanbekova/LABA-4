#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
using namespace std;
void OGVG(int **A, int N, int i, int*M) {
	int j;
	if (M[i] != 1) {
		M[i] = 1;
		printf("%d ", i + 1);
		for (j = 0; j < N; j++) {
			if (A[i][j] == 1) {
				OGVG(A, N, j, M);
			}
		}
	}

}
void OVGBR(int **A, int N, int*M) {
	int j, i;
	stack <int> S;
	for (i = 0; i < N; i++) {
		if (M[i] != 1) {
			M[i] = 1;
			printf("%d ", i + 1);
			S.push(i);
			do {
				i = S.top();
				j = 0;
				while (j < N) {
					if ((A[i][j] == 1) && (M[j] != 1)) {
						S.push(j);
						M[j] = 1;
						printf("%d ", j + 1);
						i = j;
						j = 0;
					}
					else
						j++;
				}
				S.pop();
			} while (S.empty() != true);
		}
	}
}
int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int N, i, j;
	printf("Ведите размер матрицы \n");
	scanf_s("%d", &N);
	srand(6);
	int *M = (int*)malloc(N * sizeof(int));
	int **A = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++) {
		A[i] = (int *)malloc(N * sizeof(int));
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = rand() % 2;
			A[j][i] = A[i][j];
			if (i == j) {
				A[i][j] = 0;
			}
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d  ", A[i][j]);
		}
		printf("\n");
	}
	printf("\nОбход в глубину рекурсией:\n");
	for (i = 0; i < N; i++) {
		OGVG(A, N, i, M);
	}
	printf("\n");
	for (i = 0; i < N; i++) {
		M[i] =0;
	}
	printf("\nОбход в глубину без рекурсии:\n");
	OVGBR(A, N, M);
	
	free(A);
	free(M);
	_getch();
}