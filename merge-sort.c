#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int * sort(int len, int *left, int *array, int *sorted);

int main(int argc, char *argv[]){
    if (argc < 4) {
        printf("%s: expected 3 or more arguments, got %i.\n", argv[0], argc-1);
        return 1;
    }
    
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
    }

    args = sort(len, args, args, sorted);
    
    for (int i = 0; i < len; i++) {
        printf("%i ", args[i]);
    }
    printf("\n");

    free(args);
    free(sorted);
    return 0;
}


int * sort(int len, int *left, int *array, int *sorted) {
    if (len <= 1) {
        return left;
    }

    int llen = round(len/2.0);
    int rlen = len - llen;
    int *right = left + llen; // the pointer to the right array is at the first location
    int offset = left - array;
    
    // sort left & right
    left = sort(llen, left, array, sorted);
    right = sort(rlen, right, array, sorted);

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

    // write back into `array`
    for (int i = 0; i < len; i++) {
        array[i + offset] = sorted[i + offset];
    }

    return left;
}
