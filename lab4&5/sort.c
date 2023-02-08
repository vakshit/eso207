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

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int partition(int arr[], int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1);
    swap(&arr[randomIndex], &arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
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
    int i, j, n, temp;
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

    printf("Choose the type of sort you want to perform:\n");
    printf("\t(1) Quick Sort (random pivot)\n");
    printf("\t(2) Non-recursive Merge Sort\n");
    printf("\t(3) Recursive Merge Sort\n");
    printf("\nEnter your choice: ");
    scanf("%d", &temp);
    printf("\n");

    start = clock();
    switch (temp)
    {
    case 1:
        quickSort(arr, 0, n - 1);
        break;

    case 2:
        iterativeMergeSort(arr, n);
        break;

    case 3:
        recursiveMergeSort(arr, 0, n - 1);
        break;

    default:
        printf("Invalid choice encountered!\n");
        exit(1);
        break;
    }
    end = clock();

    for (i = 0; i < n; i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("\n");

    printf("Runtime: %.6lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
