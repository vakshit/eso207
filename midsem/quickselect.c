// C code for the above approach

#include <limits.h>
#include <stdio.h>

int partition(int arr[], int l, int r);

// This function returns K'th smallest element in arr[l..r]
// using QuickSort based method. ASSUMPTION: ALL ELEMENTS IN
// ARR[] ARE DISTINCT
int kthSmallest(int arr[], int l, int r, int K)
{
  // If k is smaller than number of elements in array
  if (K > 0 && K <= r - l + 1)
  {

    // Partition the array around last element and get
    // position of pivot element in sorted array
    int pos = partition(arr, l, r);

    // If position is same as k
    if (pos == K - 1)
      return arr[pos];
    if (pos > K - 1) // If position is more, recur
                     // for left subarray
      return kthSmallest(arr, l, pos - 1, K);

    // Else recur for right subarray
    return kthSmallest(arr, pos + 1, r,
                       K);
  }

  // If k is more than number of elements in array
  return INT_MAX;
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Standard partition process of QuickSort(). It considers
// the last element as pivot and moves all smaller element
// to left of it and greater elements to right

int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = low;
  for (int j = low; j <= high - 1; j++)
  {
    if (arr[j] <= pivot)
    {
      swap(&arr[i], &arr[j]);
      i++;
    }
  }
  swap(&arr[i], &arr[high]);
  printf("%d \n", i);
  for (int i = 0; i < 7; i++)
    printf("%d ", arr[i]);
  printf("\n");
  return (i);
}

// int partition(int arr[], int l, int r)
// {
//   int x = arr[r], i = l;
//   for (int j = l; j <= r - 1; j++)
//   {
//     if (arr[j] <= x)
//     {
//       swap(&arr[i], &arr[j]);
//       i++;
//     }
//   }

//   swap(&arr[i], &arr[r]);
//   printf("%d \n", i);
//   for (int i=0;i<7;i++)
//     printf("%d ", arr[i]);
//   printf("\n");
//   return i;
// }

// Driver's code
int main()
{
  int arr[] = {12, 3, 5, 7, 4, 19, 26};
  int N = sizeof(arr) / sizeof(arr[0]), K = 3;

  // Function call
  printf("K'th smallest element is %d",
         kthSmallest(arr, 0, N - 1, K));
  return 0;
}
