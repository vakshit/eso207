#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 0
#define MAX 100

int main(int argc, char **argv)
{
  FILE *filePtr;
  int i, num, count;

  if (argc < 2)
  {
    printf("Input the random number to be generated!!");
    return 1;
  }

  count = atoi(argv[1]);

  filePtr = fopen("randomNumbers.txt", "w");
  if (filePtr == NULL)
  {
    printf("Error opening file!");
    return 1;
  }

  srand(time(0));

  for (i = 0; i < count; i++)
  {
    num = MIN + rand() % (MAX - MIN + 1);
    fprintf(filePtr, "%d\n", num);
  }

  fclose(filePtr);

  return 0;
}
