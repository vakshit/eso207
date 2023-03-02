#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 0
#define MAX 99

int pow(int a, int b)
{
    int ans = 1;
    int i;
    for (i = 0; i < b; i++)
    {
        ans *= a;
    }
    return ans;
}

int main(int argc, char **argv)
{
    FILE *filePtr;
    int i, j, num, count, n;

    if (argc < 2)
    {
        printf("Input the random number to be generated!\n");
        return 1;
    }

    count = atoi(argv[1]);
    n = pow(2, count);

    filePtr = fopen("randomStrassenNumbers.txt", "w");
    if (filePtr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(0));

    fprintf(filePtr, "%d\n\n", n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            num = MIN + rand() % (MAX - MIN + 1);
            fprintf(filePtr, "%d ", num);
        }
        fprintf(filePtr, "\n");
    }

    fprintf(filePtr, "\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            num = MIN + rand() % (MAX - MIN + 1);
            fprintf(filePtr, "%d ", num);
        }
        fprintf(filePtr, "\n");
    }

    return 0;
}