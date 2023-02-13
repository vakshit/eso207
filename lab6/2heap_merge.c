#include <stdio.h>
#include <time.h>

#define MAX_SIZE 1000000

int min(int a, int b)
{
  return a < b ? a : b;
}

void heapify(int arr[], int n, int i)
{
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  while (left < n || right < n)
  {
    if (left < n && arr[left] > arr[largest])
    {
      largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
      largest = right;
    }

    if (largest != i)
    {
      int temp = arr[i];
      arr[i] = arr[largest];
      arr[largest] = temp;
      i = largest;
      left = 2 * i + 1;
      right = 2 * i + 2;
    }
    else
    {
      break;
    }
  }
}

void heapSort(int arr[], int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
  {
    heapify(arr, n, i);
  }

  for (int i = n - 1; i >= 0; i--)
  {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    heapify(arr, i, 0);
  }
}

void merge(int arr[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  int L[n1], R[n2];
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }
  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void iterativeMergeSort(int arr[], int n)
{
  int currSize;
  int leftStart;

  for (currSize = 1; currSize < n; currSize *= 2)
  {
    for (leftStart = 0; leftStart < n; leftStart += 2 * currSize)
    {
      int mid = min(leftStart + currSize - 1, n - 1);
      int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);
      merge(arr, leftStart, mid, rightEnd);
    }
  }
}

void recursiveMergeSort(int arr[], int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;

    recursiveMergeSort(arr, l, m);
    recursiveMergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

int main()
{
  int arr[MAX_SIZE];
  int i, n;
  clock_t start, end;

  // Open the file for reading
  FILE *fptr = fopen("numbers.txt", "r");
  if (fptr == NULL)
  {
    printf("Error opening file\n");
    return 1;
  }

  // Read the numbers from the file into an array
  n = 0;
  while (fscanf(fptr, "%d", &arr[n]) == 1)
  {
    n++;
  }

  // Close the file
  fclose(fptr);

  // Sort the numbers using an iterative heap sort
  start = clock();
  heapSort(arr, n);
  end = clock();
  printf("Runtime: of heap sort is %.6lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  n = 0;
  while (fscanf(fptr, "%d", &arr[n]) == 1)
  {
    n++;
  }
  start = clock();
  iterativeMergeSort(arr, n);
  end = clock();
  printf("Runtime: of heap sort is %.6lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  // // Print the sorted numbers
  // printf("Sorted numbers:\n");
  // for (i = 0; i < n; i += 1)
  // {
  //   printf("%d\n", arr[i]);
  // }

  // Print the runtime

  return 0;
}
