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

`gcc merge_sort.c -o merge_sort.exe -lm`

## Usage:
To use the program, run the compiled executable with a list of integers as command-line arguments. For example:

`./merge_sort 5 3 8 1 9 2 -v --delay 100`

This will sort the integers `5, 3, 8, 1, 9, 2` using the merge sort algorithm, display the process with 100 ms between each frame, and print the sorted list.


## Explanation:
1. The program takes a series of integers from the command line and stores them in an array.
2. It then calls the `sort` function to recursively split the array and merge the sorted subarrays.
3. At each merge step, the program prints both the unsorted and partially sorted arrays to visually track the progress.
4. The program measures and prints the runtime of the sorting operation.

## Files:
- `merge-sort.c`: The main C file containing the merge sort algorithm implementation.
- `merge-sort.exe`: The compiled binary of `merge-sort.c` for Windows.

## Options:
- `-h` and `--help` print a usage manual to stdout.
- `-v` visually represents the sorting process. Implies `--delay 50` unless overriden.
- `--delay time` sets a delay of <ins>time</ins> milliseconds between each frame of the sorting process. Overrides the delay from `-v`.

## Notes:
- The program _*can*_ sort multi-digit & negative numbers, but fails to represent them when the `-v` option is included.
- Make sure to place the numbers to sort **before** the options. Placing options before or in the list will replace final numbers with zeros.

## Current Identified Issue(s) in merge-sort.c:
- Visual tracking misalligns in the presence of multi-digit numbers (including negatives).

## Coming Soon:
- Reading/writing to/from file.

## Author:
ion727

