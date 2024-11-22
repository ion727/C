#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

int * sort(int len, int *left, int *array, int arraylen, int *sorted);

int main(int argc, char *argv[]){
    if (argc < 4) {
        printf("Usage: <%s> <int> <int> ... <int>.\nOutputs to stdio a sorted list using the provided integers.\n", argv[0]);
        return 1;
    }
    clock_t start = clock();
    // stores the length of the array of integers
    int len = argc - 1; 

    // convert each element of argv into an integer and add it to "args"
    int *args = malloc(len*sizeof(int));
    int *sorted = malloc(len*sizeof(int));

    if (args == NULL || sorted == NULL){
        printf("Error code 2: memory allocation failed.");
        return 2;
    }
    for (int i = 0; i < len; i++) {
        args[i] = atoi(argv[i + 1]);
        sorted[i] = INT_MIN;
    }

    sort(len, args, args, len, sorted);
    
    printf("\r[ ");
    for (int i = 0; i < len; i++) {printf("%i ", args[i]);}
    printf("]\n");
    for (int i = 0; i < len; i++) {printf("  ");}
    printf("   \r");
    
    free(args);
    free(sorted);
    clock_t end = clock();
    double runtime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Runtime: %.6f seconds\n", runtime);
    return 0;
}


int * sort(int len, int *left, int *array, int arraylen, int *sorted) {
    if (len <= 1) {
        return left;
    }

    int llen = round(len/2.0);
    int rlen = len - llen;
    int *right = left + llen; // the pointer to the right array is at the first location
    int offset = left - array;
    
    // sort left & right
    left = sort(llen, left, array, arraylen, sorted);
    right = sort(rlen, right, array, arraylen, sorted);

    // merge
    int leftpoint = 0, rightpoint = 0;
    for (int i = 0; i < len; i++){
        if (leftpoint >= llen) {
            *(sorted + i + offset) = right[rightpoint];
            rightpoint++;
        } else if (rightpoint >= rlen) {
            *(sorted + i + offset) = left[leftpoint];
            leftpoint++;
        } else if (left[leftpoint] < right[rightpoint]) {
            *(sorted + i + offset) = left[leftpoint];
            leftpoint++;
        } else {
            *(sorted + i + offset) = right[rightpoint]; 
            rightpoint++;
        }
    }

    printf("\r[ ");
    for (int i = 0; i < arraylen; i++) {printf("%i ", array[i]);}
    printf("]\n[ ");
    for (int i = 0; i < arraylen; i++) {
        if (sorted[i] != INT_MIN) {
            printf("\x1b[1A░\x1b[1D\x1b[1B%i ", sorted[i]);
        } else {
            printf("░ ");
        }
    }
    printf("]\x1b[1A");
    fflush(stdout);
    
    // write back into `array`
    for (int i = 0; i < len; i++) {
        array[i + offset] = sorted[i + offset];
        sorted[i + offset] = INT_MIN;
    }

    usleep(500000);
    return left;
}
