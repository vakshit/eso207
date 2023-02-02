#include <stdio.h>
#include <time.h>

#define MAX_SIZE 1000000

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

int main()
{
  int arr[MAX_SIZE];
  int i, n;
  clock_t start, end;

  // Open the file for reading
  FILE *fptr = fopen("rand_numbers.txt", "r");
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

  // Print the sorted numbers
  printf("Sorted numbers:\n");
  for (i = 0; i < n; i += 10000)
  {
    printf("%d\n", arr[i]);
  }

  // Print the runtime
  printf("Runtime: %.6lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
