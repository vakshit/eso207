#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 1000000;
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int quickselect(int arr[], int low, int high, int k)
{
    if (low <= high) {
        int pivotIndex = partition(arr, low, high);
        if (pivotIndex == k) {
            return arr[pivotIndex];
        } else if (pivotIndex > k) {
            return quickselect(arr, low, pivotIndex - 1, k);
        } else {
            return quickselect(arr, pivotIndex + 1, high, k);
        }
    }
    return -1;
}

int main(void)
{
    int arr[MAX_SIZE];
    int n = 0;

    FILE *fp = fopen("numbers.txt", "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    while (fscanf(fp, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(fp);

    int k = n / 2;
    printf("The median is %d\n", quickselect(arr, 0, n - 1, k));

    return 0;
}
