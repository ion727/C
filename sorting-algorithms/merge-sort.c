#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int *sort(int *left, int len, int *array, int arraylen, int *sorted, int delay, int visual, int digits_len, double *runtime);
int get_digits(int num);
void frametick(int *array, int arraylen, int *sorted, int delay, int visual, int digits_len, double *runtime);
void printn(int n, char *character);
void realign(char **location, int n, int *argc, char **argv);

int main(int argc, char **argv){
    int delay = 0, visual = 0, runT = 0;
    for (int i = 0; i < argc; i++){
        printf("%s\n",argv[i]);
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
                printf("Usage:\n"
"program_name [-h | --help] [-vr] [--delay <milliseconds>] <int> <int> ... <int>\n"
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
"Enables visualization of the sorting process. Visualization imposes a minimum delay of 100 ms (can be overriden with --delay 0 following -v).\n"
"Implies -r\n"
"\n"
"-r\n"
"Displays the total time allocated to the program by the CPU (therefore excluding the delay when -v is specified).\n"
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
            } else if (strcmp(argv[i], "-v") == 0) {
                delay = 100;
                visual = 1;
                runT = 1;
                realign(&argv[i], 1, &argc, argv);
                i--;
            } else if (strcmp(argv[i], "--delay") == 0) {
                if (delay < 0) {
                    printf("Error: [--delay] option takes positive integer as argument");
                    return 1;
                }
                delay = atoi(argv[i+1]);
                realign(&argv[i], 2, &argc, argv);
                i--;
            } else if (strcmp(argv[i], "-r") == 0) {
                runT = 1;
                realign(&argv[i], 1, &argc, argv);
                i--;
            } else if (strcmp(argv[i], "-o") == 0) {
                //print to file
                realign(&argv[i], 2, &argc, argv);
                i--;
            } else {
                for (int j = 1, l = strlen(argv[i]); j < l; j++) {
                    if (!isdigit(argv[i][j])) {
                        printf("Unrecognised option <%s>.\nUsage: <%s> <int> <int> ... <int> [-h|--help] [-vr] [--delay time].\n",argv[i], argv[0]);
                        return 1;
                    }
                }
            }
        }
    }
    if (argc < 3) {
        printf("Usage: <%s> <int> <int> ... <int> [-h|--help] [-v] [--delay time].", argv[0]);
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
    argv++; // to ignore the filename at argv[0]

    int largest_len = 1;
    for (int i = 0; i < len; i++) { // turn input into integers & find largest number
        sorted[i] = INT_MIN;
        args[i] = atoi(argv[i]);
        if (get_digits(args[i]) > largest_len) {
            largest_len = get_digits(args[i]);
        }   
    }

    double run = 0;
    double *runtime = &run;
    clock_t start = clock();
    sort(args, len, args, len, sorted, delay, visual, largest_len, runtime); //=========================================\\ BEACON
    clock_t end = clock();
    
    printf("[ ");
    for (int i = 0; i < len; i++) {
        printf("%i", args[i]);
        printn(largest_len - get_digits(args[i]) + 1, " ");
    }
    printf("]\n");
    printn((largest_len + 1)*len, " ");
    printf("   \r");
    
    free(args);
    free(sorted);
    *runtime += (double)(end - start) / CLOCKS_PER_SEC;
    if (runT) {printf("Runtime: %.3f ms\n", *runtime*1000);}
    return 0;
}


int * sort(int *left, int len, int *array, int arraylen, int *sorted, int delay, int visual, int digits_len, double *runtime) {
    if (len <= 1) {
        return left;
    }

    int llen = round(len/2.0);
    int rlen = len - llen;
    int *right = left + llen; // the pointer to the right array is at the first location
    const int offset = left - array;
    
    // sort left & right
    left = sort(left, llen, array, arraylen, sorted, delay, visual, digits_len, runtime);
    right = sort(right, rlen, array, arraylen, sorted, delay, visual, digits_len, runtime);

    for (int i = 0; i < arraylen; i++) {
        sorted[i] = INT_MIN;
    }
    for (int i = 0; i < len; i++) {
        sorted[i + offset] = INT_MAX;
    }
    int leftpoint = 0, rightpoint = 0;
    for (int i = 0; i < len; i++){ // iteratively merge
        if (leftpoint >= llen) {
            *(sorted + i + offset) = right[rightpoint];
            right[rightpoint] = INT_MAX;
            rightpoint++;
        } else if (rightpoint >= rlen) {
            *(sorted + i + offset) = left[leftpoint];
            leftpoint++;
        } else if (left[leftpoint] < right[rightpoint]) {
            *(sorted + i + offset) = left[leftpoint];
            left[leftpoint] = INT_MAX;
            leftpoint++;
        } else {
            *(sorted + i + offset) = right[rightpoint]; 
            right[rightpoint] = INT_MAX;
            rightpoint++;
        }
        frametick(array, arraylen, sorted, delay, visual, digits_len, runtime);
    }


    // write back into `array`
    for (int i = 0; i < len; i++) {
        array[i + offset] = sorted[i + offset];
        sorted[i + offset] = INT_MAX;
        frametick(array, arraylen, sorted, delay, visual, digits_len, runtime);

    }

    return left;
}

void printn(int n, char *character) {
    for (int i = 0; i < n; i++) {
        printf("%s", character);
    }
}

int get_digits(int num) {
    if (num == 0) {
        return 1;
    }
    int count = 1;
    if (num < 0) {
        count++;
        num = -num;
    }
    return ((int)log10(num)) + count;
}

void realign(char **location, int n, int *argc, char **argv) {
    *argc -= n;
    // loop starting at location that takes i+1 and copies it into i, including the NULL.
    for (int i = 0; location[i+n] != NULL; i++) {
        location[i] = location[i+n];
    }
    for (int i = *argc, len = *argc + n; i < len; i++) {
        argv[i] = NULL;
    }
}

void frametick(int *array, int arraylen, int *sorted, int delay, int visual, int digits_len, double *runtime) { //visually display sorting
    if (!visual) { 
        return;
    }
    clock_t start = clock();

    printf("[ ");
    for (int i = 0; i < arraylen; i++) {
        if (array[i] == INT_MAX) {
            printn(digits_len,"▓");
        } else {
            int missing_digits = digits_len - get_digits(array[i]);
            printf("%i", array[i]);
            printn(missing_digits," ");
        }
        printf(" ");
    }
    printf("]\n\n[ ");
    for (int i = 0; i < arraylen; i++) {
        if (!(sorted[i] == INT_MIN || sorted[i] == INT_MAX)) {
            printf("%i", sorted[i]);
            int missing_digits = digits_len - get_digits(sorted[i]);
            printn(missing_digits," ");
        } else if (sorted[i] == INT_MAX) {
            printn(digits_len,"▓");
        } else {
            printn(digits_len,"░");
        }
        printf(" ");
    }
    printf("]\x1b[2A\r");
    fflush(stdout);
    usleep(delay * 1000);
    clock_t end = clock();
    *runtime -= (double)(end - start) / CLOCKS_PER_SEC;
    return;
}