#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define MIN -1000000
#define MIN 0
#define MAX 100

int main(int argc, char *argv[]) {
    FILE *fptr;
    int i, num, count;
    
    // Check if the number of random numbers was provided as a command-line argument
    if (argc < 2) {
        printf("Usage: %s [number of random numbers]\n", argv[0]);
        return 1;
    }
    
    // Convert the command-line argument to an integer
    count = atoi(argv[1]);
    
    // Open file for writing
    fptr = fopen("rand_numbers.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    // Seed the random number generator
    srand(time(0));
    
    // Generate and write the random numbers to the file
    for (i = 0; i < count; i++) {
        num = MIN + rand() % (MAX - MIN + 1);
        fprintf(fptr, "%d\n", num);
    }
    
    // Close the file
    fclose(fptr);
    
    return 0;
}
