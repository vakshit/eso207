#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
const int SIZE = 2;

int mx(int arr[], int n)
{
  int max = arr[0];
  for (int i = 1; i < n; i++)
  {
    if (arr[i] > max)
    {
      max = arr[i];
    }
  }
  return max;
}

int nextpowerof2(int k)
{
  return pow(2, ceil(log2(k)));
}

void display(int matrix[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (j != 0)
      {
        printf("\t");
      }
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void add(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE], int size)
{
  int i, j;
  for (i = 0; i < size; i++)
  {
    for (j = 0; j < size; j++)
    {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

void sub(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE], int size)
{
  int i, j;
  for (i = 0; i < size; i++)
  {
    for (j = 0; j < size; j++)
    {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
}

void Strassen_algorithmA(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE], int size)

{
  // base case
  if (size == 1)
  {
    C[0][0] = A[0][0] * B[0][0];
    return;
  }
  else
  {
    int new_size = size / 2;
    int z[new_size];
    int a11[new_size][new_size], a12[new_size][new_size], a21[new_size][new_size], a22[new_size][new_size],
        b11[new_size][new_size], b12[new_size][new_size], b21[new_size][new_size], b22[new_size][new_size],
        c11[new_size][new_size], c12[new_size][new_size], c21[new_size][new_size], c22[new_size][new_size],
        p1[new_size][new_size], p2[new_size][new_size], p3[new_size][new_size], p4[new_size][new_size],
        p5[new_size][new_size], p6[new_size][new_size], p7[new_size][new_size],
        aResult[new_size][new_size], bResult[new_size][new_size];

    int i, j;

    // dividing the matrices into sub-matrices:
    for (i = 0; i < new_size; i++)
    {
      for (j = 0; j < new_size; j++)
      {
        a11[i][j] = A[i][j];
        a12[i][j] = A[i][j + new_size];
        a21[i][j] = A[i + new_size][j];
        a22[i][j] = A[i + new_size][j + new_size];

        b11[i][j] = B[i][j];
        b12[i][j] = B[i][j + new_size];
        b21[i][j] = B[i + new_size][j];
        b22[i][j] = B[i + new_size][j + new_size];
      }
    }

    // Calculating p1 to p7:

    add(a11, a22, aResult, new_size); // a11 + a22
    add(b11, b22, bResult, new_size); // b11 + b22
    Strassen_algorithmA(aResult, bResult, p1, new_size);
    // p1 = (a11+a22) * (b11+b22)

    add(a21, a22, aResult, new_size); // a21 + a22
    Strassen_algorithmA(aResult, b11, p2, new_size);
    // p2 = (a21+a22) * (b11)

    sub(b12, b22, bResult, new_size); // b12 - b22
    Strassen_algorithmA(a11, bResult, p3, new_size);
    // p3 = (a11) * (b12 - b22)

    sub(b21, b11, bResult, new_size); // b21 - b11
    Strassen_algorithmA(a22, bResult, p4, new_size);
    // p4 = (a22) * (b21 - b11)

    add(a11, a12, aResult, new_size); // a11 + a12
    Strassen_algorithmA(aResult, b22, p5, new_size);
    // p5 = (a11+a12) * (b22)

    sub(a21, a11, aResult, new_size); // a21 - a11
    add(b11, b12, bResult, new_size);
    // b11 + b12
    Strassen_algorithmA(aResult, bResult, p6, new_size);
    // p6 = (a21-a11) * (b11+b12)

    sub(a12, a22, aResult, new_size); // a12 - a22
    add(b21, b22, bResult, new_size);
    // b21 + b22
    Strassen_algorithmA(aResult, bResult, p7, new_size);
    // p7 = (a12-a22) * (b21+b22)

    // calculating c21, c21, c11 e c22:

    add(p3, p5, c12, new_size); // c12 = p3 + p5
    add(p2, p4, c21, new_size); // c21 = p2 + p4

    add(p1, p4, aResult, new_size);      // p1 + p4
    add(aResult, p7, bResult, new_size); // p1 + p4 + p7
    sub(bResult, p5, c11, new_size);     // c11 = p1 + p4 - p5 + p7

    add(p1, p3, aResult, new_size);      // p1 + p3
    add(aResult, p6, bResult, new_size); // p1 + p3 + p6
    sub(bResult, p2, c22, new_size);     // c22 = p1 + p3 - p2 + p6

    // Grouping the results obtained in a single matrix:
    for (i = 0; i < new_size; i++)
    {
      for (j = 0; j < new_size; j++)
      {
        C[i][j] = c11[i][j];
        C[i][j + new_size] = c12[i][j];
        C[i + new_size][j] = c21[i][j];
        C[i + new_size][j + new_size] = c22[i][j];
      }
    }
  }
}


void Strassen_algorithm(int A[SIZE][SIZE], int B[SIZE][SIZE], int m, int n, int a, int b)
{
  /* Check to see if these matrices are already square and have dimensions of a power of 2. If not,
   * the matrices must be resized and padded with zeroes to meet this criteria. */
  int temp_arr[] = {m, n, a, b};
  int k = mx(temp_arr, 4);

  int s = nextpowerof2(k);

  int Aa[s][s], Bb[s][s], Cc[s][s];

  for (unsigned int i = 0; i < m; i++)
  {
    for (unsigned int j = 0; j < n; j++)
    {
      Aa[i][j] = A[i][j];
    }
  }
  for (unsigned int i = 0; i < a; i++)
  {
    for (unsigned int j = 0; j < b; j++)
    {
      Bb[i][j] = B[i][j];
    }
  }
  Strassen_algorithmA(Aa, Bb, Cc, s);
  // int temp1[b];
  int C[m][b];
  for (unsigned int i = 0; i < m; i++)
  {
    for (unsigned int j = 0; j < b; j++)
    {
      C[i][j] = Cc[i][j];
    }
  }
  display(C);
}

int main()
{
  // Your code goes here;
  int a[2][2] = {{1, 0}, {0, 1}};
  int b[2][2] = {{-1, 0}, {0, -1}};
  Strassen_algorithm(a, b, 3, 3, 3, 3);
  return 0;
}