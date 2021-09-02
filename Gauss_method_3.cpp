#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#define TRUE 1
#define FALSE 0

void Enter_mas(double **Matr, int row, int col)			//ббнд люяяхбю
{
	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			printf("a[%d,%d] = ", i + 1, j + 1);
			scanf("%lf", &Matr[i][j]);
		}
	printf("\n\n");
}

int min_col_row(int col, int row)					//лхмхлсл хг йнк-бю ярпнй х ярнкжнб
{
	if (col > row) return row;
	else return col;
}

void div_row(double *prow, int col, int index)				//декемхе ярпнйх
{
	int i;
	double temp;
	temp = prow[index];
	for (i = index; i < col; i++)
	{
		prow[i] = prow[i] / temp;
	}
}

void swap_row(double **p, int i, int j)						//оепелемю леярюлх ярпнвей
{
	double *temp;
	temp = p[i];
	p[i] = p[j];
	p[j] = temp;
}

void swap_col(double **p, int row, int i, int j)			//оепелемю леярюлх ярнкажнб
{
	double temp;
	int k;
	for (k = 0; k < row; k++)
	{
		temp = p[k][i];
		p[k][i] = p[k][j];
		p[k][j] = temp;
	}
}

void row_sum(double **Matr, int index1, int index2, int col) //яйкюдшбюмхе ярпнвей люрпхжш
{
	int i;
	double temp;
	temp = Matr[index2][index1];
	Matr[index2][index1] = 0.0;
	for (i = (index1 + 1); i < col; i++)
	{
		Matr[index2][i] -= (Matr[index1][i] * temp);
	}
}

int rank_normal(double **mat, int row, int col)						//пюмц люрпхжш
{
	int i, n;
	n = min_col_row(col - 1, row);
	i = n - 1;
	while (mat[i][i] == 0) i--;
	return i + 1;
}

int rank_extended(double **mat, int row, int col, int rank_N)		//пюмц пюяьхпеммни люрпхжш
{
	int i, j, rank_E, n;
	char flag = TRUE;
	n = min_col_row(col, row);
	i = rank_N;
	while (flag && i < row)
	{
		for (j = rank_N; j < col; j++)
		if (mat[i][j] != 0) flag = FALSE;
		i++;
	}
	if (flag) rank_E = rank_N;
	else rank_E = rank_N + 1;
	return rank_E;
}

void Gauss_main(double **mat, int row, int col, char *ind) //лернд цюсяяю
{
	int i, j, l, i1, i2, n, k;
	char flag = FALSE;
	n = min_col_row(col - 1, row);
	for (i = 0; i < n; i++)
	{
		for (i1 = 0; i1 < row; i1++)
		{
			for (i2 = 0; i2 < col; i2++)
				printf("%.1lf  ", mat[i1][i2]);
			printf("\n");
		}
		printf("\n");

		l = i;
		k = i;
		while (mat[l][k] == 0 && k != (col - 1))
		{
			l++;
			if (l == row)
			{
				l = i;
				k++;
			}
		}
		if (k == (col - 1))
		{
			flag = TRUE;
			break;
		}
		else
		{
			if (l != i || k != i)
			{
				swap_row(mat, l, i);
				swap_col(mat, row, k, i);
				ind[k] = ind[k] + ind[i];
				ind[i] = ind[k] - ind[i];
				ind[k] = ind[k] - ind[i];
			}
		}
		div_row(mat[i], col, i);
		for (j = (i + 1); j < row; j++)
			row_sum(mat, i, j, col);
	}
	if (flag == FALSE)
		div_row(mat[n - 1], col, n - 1);

	for (i1 = 0; i1 < row; i1++)
	{
		for (i2 = 0; i2 < col; i2++)
			printf("%.1lf  ", mat[i1][i2]);
		printf("\n");
	}
	printf("\n");
}

void Back_stroke(double **mat, int row, int col, double *mas, char *ind) //напюрмши унд
{
	int n, i, j;
	n = min_col_row(col, row);
	for (i = n - 1; i >= 0; i--)
	{
		mas[i] = mat[i][col - 1];
		printf("x%d = ", ind[i] + 1);
		if (mat[i][i] == 0)
			printf("t%d\n", i);
		for (j = (i + 1); j < (col - 1); j++)
		{
			if (j >= n || mat[j][j] == 0)
				printf("-t(%d)*%.1lf", j, mat[i][j]);
			else
				mas[i] += (-mas[j])*mat[i][j];
		}
		if (mat[i][i] != 0)
			printf("+(%lf)\n", mas[i]);
	}

	for (i = n; i < col - 1; i++)
	{
		printf("x%d = t%d\n", ind[i] + 1, i);
	}

	printf("\n\nprivate decision:\n");
	for (i = 0; i < (col - 1); i++)
	{
		printf("x%d = %e\n", ind[i] + 1, mas[i]);
	}
}

int index_x(char *ind, int j) 				//хмдейя мехгбеярмни оепелеммни(дкъ опнбепйх)
{
	int i = 0;
	while (ind[i] != j) i++;
	return i;
}

void Gauss_test(double **mat, int row, int col, double *mas, char *ind)  //опнбепйю пеьемхъ
{
	int i, j, index;
	double left_side;
	printf("\n\n **** GAUSS TEST ****\n\n");
	for (i = 0; i < row; i++)
	{
		left_side = 0.0;
		for (j = 0; j < col - 1; j++)
		{
			index = index_x(ind, j);
			left_side += mat[i][j] * mas[index];
		}
		printf("%e = %e\n", left_side, mat[i][col - 1]);
	}
}

void Gauss(double **mat, int row, int col, double *mas, char *ind) //тсмйжхъ бшгнбю
{
	int rank_n, rank_e, i, j;
	double **mat1;
	mat1 = (double **)malloc(row*sizeof(double*));
	for (i = 0; i < row; i++)
		mat1[i] = (double *)malloc(col*sizeof(double));
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			mat1[i][j] = mat[i][j];
	Gauss_main(mat, row, col, ind);
	rank_n = rank_normal(mat, row, col);
	rank_e = rank_extended(mat, row, col, rank_n);
	if (rank_n < rank_e)
		printf("System Incompatible :(\n");
	else
	{
		Back_stroke(mat, row, col, mas, ind);
		Gauss_test(mat1, row, col, mas, ind);
	}
	for (i = 0; i < row; i++)
		free(mat1[i]);
	free(mat1);
}


int main()											//MAIN
{
	int row, col, i;
	double **arr, *mas;
	char *ind;
	do
	{
		printf("Enter row: ");
		scanf("%d", &row);
	} while (row <= 0);
	do
	{
		printf("Enter col: ");
		scanf("%d", &col);
	} while (col <= 0);
	arr = (double **)malloc(row*sizeof(double*));
	for (i = 0; i < row; i++)
		arr[i] = (double *)malloc(col*sizeof(double));

	mas = (double *)malloc((col - 1)*sizeof(double));
	ind = (char*)malloc((col - 1)*sizeof(char));
	Enter_mas(arr, row, col);
	for (i = 0; i < (col - 1); i++)
	{
		ind[i] = i;
		mas[i] = 0;
	}

	Gauss(arr, row, col, mas, ind);

	for (i = 0; i < row; i++)
		free(arr[i]);
	free(arr);
	free(ind);
	free(mas);
	_getch();
	return 0;
}