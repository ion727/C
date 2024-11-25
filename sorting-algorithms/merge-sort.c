#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int * sort(int *left, int len, int *array, int arraylen, int *sorted, int delay, int visual);

int main(int argc, char *argv[]){
    int delay = 0, visual = 0;
    for (int i = 0; i < argc; i++){
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
                printf("Usage:\n"
"program_name [-h | --help] [-v] [--delay <milliseconds>] <int> <int> ... <int>\n"
"\n"
"Description:\n"
"This program sorts a list of integers using a recursive merge sort algorithm. The process is optionally visualized step-by-step in the terminal, and the runtime of the sorting operation is displayed at the end.\n"
"\n"
"Arguments:\n"
"<int> <int> ... <int>\n"
"A list of integers to be sorted. These integers must be provided as space-separated values.\n"
"\n"
"Options:\n"
"-h, --help\n"
"Displays this help page.\n"
"\n"
"-v\n"
"Enables visualization of the sorting process. Visualization imposes a minimum delay of 50 ms (can be overriden with --delay 0 following -v).\n"
"\n"
"--delay <milliseconds>\n"
"Specifies the delay (in milliseconds) between steps of the sorting visualization. This allows you to observe the merge sort process at your chosen speed.\n"
"Default: 0 ms.\n"
"Note: The delay must be a positive integer.\n"
"\n"
"Exit Codes:\n"
"0: Program executed successfully.\n"
"1: Incorrect usage (e.g., missing required arguments).\n"
"2: Memory allocation error.\n"
"\n"
"Notes:\n"
"\n"
"The program assumes the input integers are valid. If the input is malformed (e.g., non-numeric values), unexpected behavior may occur.\n"
"Ensure sufficient terminal width to visualize the sorting process effectively.\n");
                return 0;
            }
            if (strcmp(argv[i], "-v") == 0) {
                delay = 50;
                visual = 1;
            }
            if (strcmp(argv[i], "--delay") == 0) {
                argc -= 2;
                delay = atoi(argv[i+1]);
                if (delay < 0) {
                    printf("Error: [--delay] flag takes positive integer.");
                }
            }
        }
    }
    if (argc < 3) {
        printf("Usage: <%s> <int> <int> ... <int> [-h|--help] [-v] [--delay time].\nOutputs to stdio a sorted list using the provided integers.\n", argv[0]);
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
    argv++; // to ignore the filename at argv[0]
    for (int i = 0; i < len; i++) {
        args[i] = atoi(argv[i]);
        sorted[i] = INT_MIN;
    }

    sort(args, len, args, len, sorted, delay, visual);
    
    printf("\r");
    for (int i = 0; i < len; i++) {printf("%i ", args[i]);}
    printf("\n");
    for (int i = 0; i < len; i++) {printf("  ");}
    printf("   \r");
    
    free(args);
    free(sorted);
    clock_t end = clock();
    double runtime = (double)(end - start) / CLOCKS_PER_SEC;
    if (visual) {printf("Runtime: %.3f ms\n", runtime*1000);}
    return 0;
}


int * sort(int *left, int len, int *array, int arraylen, int *sorted, int delay, int visual) {
    if (len <= 1) {
        return left;
    }

    int llen = round(len/2.0);
    int rlen = len - llen;
    int *right = left + llen; // the pointer to the right array is at the first location
    int offset = left - array;
    
    // sort left & right
    left = sort(left, llen, array, arraylen, sorted, delay, visual);
    right = sort(right, rlen, array, arraylen, sorted, delay, visual);

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
    if (visual) {
        printf("\r[ ");
        for (int i = 0; i < arraylen; i++) {printf("%i ", array[i]);}
        printf("]\n[ ");
        for (int i = 0; i < arraylen; i++) {
            if (sorted[i] != INT_MIN && sorted[i] != INT_MAX) {
                printf("\x1b[1A▓\x1b[1D\x1b[1B%i ", sorted[i]);
            } else if (sorted[i] == INT_MAX) {
                printf("▓ ");
            } else {
                printf("░ ");
            }
        }
        printf("]\x1b[1A");
        fflush(stdout);
    }

    // write back into `array`
    for (int i = 0; i < len; i++) {
        array[i + offset] = sorted[i + offset];
        sorted[i + offset] = INT_MAX;
    }

    usleep(delay * 1000);
    return left;
}
