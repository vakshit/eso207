#include <stdio.h>
#include <stdlib.h>

typedef struct Point
{
    double x;
    double y;
} Point;

int find_length(FILE *filePtr)
{
    int n = 0;
    fseek(filePtr, 0, SEEK_SET);
    fscanf(filePtr, "%d\n", &n);
    return n;
}

void read_pairs(FILE *filePtr, int n, Point points[])
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        fscanf(filePtr, "%lf", &points[i].x);
        fscanf(filePtr, "%lf", &points[i].y);
    }
    return;
}