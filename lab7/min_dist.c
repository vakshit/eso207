#include <math.h>
#include <time.h>
#include "read_file.h"

double calcDist(Point p1, Point p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

double findMinDist(Point points[], int n, Point *p1, Point *p2)
{
    int i, j;
    double minDist = INFINITY;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            double d = calcDist(points[i], points[j]);
            if (d < minDist)
            {
                minDist = d;
                *p1 = points[i];
                *p2 = points[j];
            }
        }
    }
    return minDist;
}

int main(int argc, char **argv)
{
    FILE *filePtr = fopen("pairs.txt", "r");
    if (filePtr == NULL)
    {
        printf("Cannot open file pairs.txt!\n");
        return 1;
    }

    int n = find_length(filePtr);
    Point points[n];
    read_pairs(filePtr, n, points);

    double minDist;
    clock_t start, end;
    Point p1, p2;

    start = clock();
    minDist = findMinDist(points, n, &p1, &p2);
    end = clock();

    printf("\nThe minimum distance encountered is of length: %lf units\n", minDist);
    printf("\tPoint 1: (%lf, %lf)\n", p1.x, p1.y);
    printf("\tPoint 2: (%lf, %lf)\n", p2.x, p2.y);
    printf("Total time taken: %.6lf seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}