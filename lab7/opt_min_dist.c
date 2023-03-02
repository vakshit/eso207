#include <math.h>
#include <time.h>
#include "read_file.h"

int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return (p1->y - p2->y);
}

double calcDist(Point p1, Point p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

double bruteForce(Point points[], int n)
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
            }
        }
    }
    return minDist;
}

double min(double x, double y)
{
    return (x < y) ? x : y;
}

double stripClosest(Point strip[], int size, double d)
{
    int i, j;
    double minDist = d;
    qsort(strip, size, sizeof(Point), compareY);
    for (i = 0; i < size; i++)
    {
        for (j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; j++)
        {
            double d = calcDist(strip[i], strip[j]);
            if (d < minDist)
            {
                minDist = d;
            }
        }
    }
    return minDist;
}

double closestUtil(Point points[], int n)
{
    if (n <= 3)
    {
        return bruteForce(points, n);
    }

    int mid = n / 2;
    Point midPoint = points[mid];

    float dl = closestUtil(points, mid);
    float dr = closestUtil(points + mid, n - mid);
    float d = min(dl, dr);

    Point strip[n];
    int i, j = 0;
    for (i = 0; i < n; i++)
    {
        if (abs(points[i].x - midPoint.x) < d)
        {
            strip[j] = points[i];
            j++;
        }
    }

    return min(d, stripClosest(strip, j, d));
}

double findMinDist(Point points[], int n)
{
    qsort(points, n, sizeof(Point), compareX);
    return closestUtil(points, n);
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
    minDist = findMinDist(points, n);
    end = clock();

    printf("\nThe minimum distance encountered is of length: %lf units\n", minDist);
    printf("Total time taken: %.6lf seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}