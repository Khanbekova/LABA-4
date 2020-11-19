#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
using namespace std;
typedef int tData;
typedef struct sNode {
	tData value;
	struct sNode *next;
} tNode;
tNode* create_list(int N, int k, int **A, int i)
{
	tNode *p_begin = NULL;
	tNode *p = NULL;
	//заполним односвязный список
	p_begin = (tNode *)malloc(sizeof(tNode));
	p = p_begin;
	p->next = NULL;
	p->value = i+1;
	for (int x = 1; x < N; x++) {
		if (A[i][x]) {
			p->next = (tNode *)malloc(sizeof(tNode));
			p = p->next;
			//заполнить _новую_ структуру данных
			p->next = NULL;
			p->value = x+1;
		}
	}
	return p_begin;
}

void print_list(tNode *p_begin)
{
	tNode *p = p_begin;
	while (p != NULL) {
		printf("-> %d ", p->value);
		p = p->next;
	}
}
tNode **p_begin;
void SG(int i, int *M) {
	{	if (M[i] != 1) {
		printf("%d ", i + 1);
		M[i] = 1;
	}
		tNode *p_b = p_begin[i];		
		while (p_b->next != NULL) {			
			i = p_b->next->value - 1;
			if (M[i] != 1) { 				
				SG(i, M);
			}
			p_b = p_b->next;
		}

	}
}



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
	printf("\n\n Список :\n");

	p_begin = (tNode**)malloc(N * sizeof(tNode*));

	for (i = 0; i < N; i++) {
		int k = 0;
		for (j = 0; j < N; j++) {
			if (A[i][j]==1)
				k++;

		}
		p_begin[i] = create_list(N, k, A, i);
		print_list(p_begin[i]);
		printf("\n");
	}
	for (i = 0; i < N; i++) {
		M[i] = 0;
	}
	printf("\nОбход в глубину списками:\n");
	for (i = 0; i < N; i++) {
			SG(i, M);
	}


	free(A);
	free(M);
	free(p_begin);
	_getch();
}