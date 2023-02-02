#include <stdio.h>
#include <time.h>

#define MAX_SIZE 1000000

int main()
{
  int arr[MAX_SIZE];
  int i, j, n, temp;
  clock_t start, end;

  start = clock();
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

  // Sort the numbers using an iterative insertion sort
  for (i = 1; i < n; i++)
  {
    temp = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > temp)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = temp;
  }
  end = clock();

  // Print the sorted numbers
  printf("Sorted numbers:\n");
  for (i = 0; i < n; i++) {
      printf("%d\n", arr[i]);
  }

  // Print the runtime
  printf("Runtime: %.6lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
