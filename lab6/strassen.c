#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void strassen(int n, int A[][n], int B[][n], int C[][n])
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int i, j;
    int m = n / 2;
    int A11[m][m], A12[m][m], A21[m][m], A22[m][m];
    int B11[m][m], B12[m][m], B21[m][m], B22[m][m];
    int C11[m][m], C12[m][m], C21[m][m], C22[m][m];
    int P1[m][m], P2[m][m], P3[m][m], P4[m][m], P5[m][m], P6[m][m], P7[m][m];
    int temp1[m][m], temp2[m][m];

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    strassen(m, A11, B11, P1);
    strassen(m, A12, B21, P2);
    strassen(m, A11, B12, P3);
    strassen(m, A12, B22, P4);
    strassen(m, A21, B11, P5);
    strassen(m, A22, B21, P6);
    strassen(m, A21, B12, P7);

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            temp1[i][j] = P1[i][j] + P2[i][j];
            temp2[i][j] = P3[i][j] + P4[i][j];
            C11[i][j] = temp1[i][j] + temp2[i][j];
            C21[i][j] = P5[i][j] + P6[i][j];
            C12[i][j] = P1[i][j] + P3[i][j];
            C22[i][j] = P2[i][j] + P4[i][j] + P7[i][j];
        }
    }

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }

    return;
}

int main()
{
    int i, j, n, temp;
    srand(time(0));

    clock_t start, end;

    FILE *filePtr = fopen("randomStrassenNumbers.txt", "r");
    if (filePtr == NULL)
    {
        printf("Error opening file randomStrassenNumbers.txt!\n");
        return 1;
    }

    fscanf(filePtr, "%d\n", &n);
    int A[n][n], B[n][n], C[n][n];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            fscanf(filePtr, "%d ", &A[i][j]);
        }
    }
    fscanf(filePtr, "\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            fscanf(filePtr, "%d ", &B[i][j]);
        }
    }
    fclose(filePtr);

    filePtr = fopen("multipledMatrix.txt", "w");

    start = clock();
    strassen(n, A, B, C);
    end = clock();

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            fprintf(filePtr, "%d ", C[i][j]);
        }
        fprintf(filePtr, "\n");
    }

    printf("Multiplied matrix stored in multipledMatrix.txt!\n");
    printf("Runtime: %.6lf seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}