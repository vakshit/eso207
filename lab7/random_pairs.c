#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 0
#define MAX 10000000000

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Provide an argument for the length of random pairs to be generated!\n");
        return 1;
    }

    FILE *filePtr;
    int i, count;
    double num;

    count = atoi(argv[1]);
    filePtr = fopen("pairs.txt", "w");
    if (filePtr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(0));

    fprintf(filePtr, "%d\n\n", count);

    for (i = 0; i < count; i++)
    {
        num = MIN + rand() % (MAX - MIN + 1);
        fprintf(filePtr, "%lf ", num / 10000);
        num = MIN + rand() % (MAX - MIN + 1);
        fprintf(filePtr, "%lf\n", num / 10000);
    }

    fclose(filePtr);

    return 0;
}
