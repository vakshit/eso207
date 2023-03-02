#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int a[], int l, int r)
{
  int pivot = a[l];
  int i = l, j = r;
  while (i < j)
  {
    do
    {
      i++;
    } while (i < j && a[i] >= pivot);
    printf("%d", i);
    do
    {
      j--;
    } while (j >= 0 && a[j] < pivot);
     printf("%d", j);
    if (i < j)
      swap(&a[i], &a[j]);
  }
  swap(&pivot, &a[j]);
  return j;
}

void quicksort(int a[], int l, int r)
{
  if(l < r)
  {
    int j = partition(a, l, r);
    quicksort(a, l, j);
    quicksort(a, j + 1, r);
  }
}

int main()
{
  int n;
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &a[i]);
  }
  quicksort(a, 0, n - 1);
}