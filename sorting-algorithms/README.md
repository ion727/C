# Merge Sort Algorithm in C

This repository contains an implementation of the **Merge Sort** algorithm in C. It reads a list of integers provided via command-line arguments, sorts the list using the merge sort algorithm, and prints both the sorted and unsorted list at each recursive step. The program also measures and outputs the runtime of the sorting process.

## Features:
- Implements the classic **merge sort** algorithm.
- Displays the sorting process step-by-step.
- Measures the runtime of the sorting process.
- Provides a command-line interface for passing integers to be sorted.

## Requirements:
- A C compiler (e.g., GCC)
- Standard C libraries (`stdio.h`, `stdlib.h`, `math.h`, `time.h`, `unistd.h`, `limits.h`)

## Compilation:
To compile the program, run the following command in your terminal:

`gcc merge_sort.c -o merge_sort -lm`

## Usage:
To use the program, run the compiled executable with a list of integers as command-line arguments. For example:

`./merge_sort 5 3 8 1 9 2`

This will sort the integers `5, 3, 8, 1, 9, 2` using the merge sort algorithm, display the process, and print the sorted list.

### Example:

```
$ ./merge_sort 5 3 8 1 9 2
output:
[ 5 3 8 1 9 2 ]
[ 1 3 5 8 9 2 ]
[ 1 2 3 5 8 9 ]
[ 1 2 3 5 8 9 ]
Runtime: 0.003274 seconds
```


## Explanation:
1. The program takes a series of integers from the command line and stores them in an array.
2. It then calls the `sort` function to recursively split the array and merge the sorted subarrays.
3. At each merge step, the program prints both the unsorted and partially sorted arrays to visually track the progress.
4. The program measures and prints the runtime of the sorting operation.

## Files:
- `merge_sort.c`: The main C file containing the merge sort algorithm implementation.
  
## Code Breakdown:

### `main` function:
- Handles the input parsing and memory allocation for the array and sorted output.
- Calls the `sort` function to begin the sorting process.
- Prints the sorted array and the runtime after sorting.

### `sort` function:
- Recursively splits the array into two halves until the base case (array of length 1) is reached.
- Merges the sorted subarrays back together in sorted order.
- Prints the current state of the array before and after the merge operation.

### Memory Allocation:
- The program dynamically allocates memory for the input array (`args`) and the sorted array (`sorted`).
- It checks for memory allocation failure and terminates with an error message if necessary.

### Output:
The program displays the current state of the array at each recursive step of the merge sort, so you can visualize the sorting process.

### Runtime:
The program calculates the runtime of the sorting process and prints it at the end. The runtime is measured in seconds and is printed with a precision of six decimal places.

## Notes:
- The program uses the `usleep()` function to create a delay between printing updates, so that the process can be visually tracked.
- The program works with any integer input and can handle a wide range of values.

## Coming Soon:
- `-h` and `--help` flags for information.
- `-d` and `--delay` flags to set a delay (currently 500 ms by default).

## Author:
ion727

