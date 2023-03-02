#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int partition(int arr[], int left, int right, int pivotIndex)
{
    int pivotValue = arr[pivotIndex];
    int storeIndex = left;
    int i;

    swap(arr + pivotIndex, arr + right);
    for (i = left; i < right; i++)
    {
        if (arr[i] < pivotValue)
        {
            swap(arr + i, arr + storeIndex);
            storeIndex++;
        }
    }
    swap(arr + storeIndex, arr + right);

    return storeIndex;
}

int linearTimeSelection(int arr[], int left, int right, int k)
{
    if (left == right)
    {
        return arr[left];
    }

    int pivotIndex = left + (rand() % (right - left + 1));
    pivotIndex = partition(arr, left, right, pivotIndex);

    if (k == pivotIndex)
    {
        return arr[k];
    }
    else if (k < pivotIndex)
    {
        return linearTimeSelection(arr, left, pivotIndex - 1, k);
    }
    else
    {
        return linearTimeSelection(arr, pivotIndex + 1, right, k);
    }
}

int findMedian(int arr[], int n)
{
    return linearTimeSelection(arr, 0, n - 1, n / 2);
}

int main()
{
    int i, n, temp;
    srand(time(0));

    clock_t start, end;

    FILE *filePtr = fopen("randomNumbers.txt", "r");
    if (filePtr == NULL)
    {
        printf("Error opening file randomNumbers.txt!");
        return 1;
    }
    n = 0;
    while (fscanf(filePtr, "%d", &temp) == 1)
    {
        n++;
    }
    int arr[n];
    i = 0;
    fseek(filePtr, 0, SEEK_SET);
    while (fscanf(filePtr, "%d", &temp) == 1)
    {
        arr[i] = temp;
        i++;
    }
    fclose(filePtr);

    start = clock();
    int median = findMedian(arr, n);
    end = clock();

    printf("Median: %d\n", median);
    printf("Runtime: %.6lf seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}