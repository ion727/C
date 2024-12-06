# Merge Sort Algorithm in C

This repository contains an implementation of the **Merge Sort** algorithm in C. It reads a list of integers provided via command-line arguments, sorts the list using the merge sort algorithm, and prints both the sorted and unsorted list at each recursive step. The program also measures and outputs the runtime of the sorting process.

## Features:
- Implements the classic **merge sort** algorithm.
- Displays the sorting process step-by-step.
- Measures the runtime of the sorting process.
- Provides a command-line interface for passing integers to be sorted.

## Requirements:
- Standard C libraries (`stdio.h`, `stdlib.h`, `math.h`, `time.h`, `unistd.h`, `limits.h`, `string.h`, `ctype.h`)

## Usage:
To use the program, run the compiled executable with a list of integers as command-line arguments. For example:

`./merge_sort 5 3 -8 1 97 2 -v --delay 200`

This will sort the integers `5, 3, -8, 1, 97, 2` using the merge sort algorithm, display the process with 200 ms between each frame, and print the sorted list.

## Files:
- `merge-sort.c`: The main C file containing the merge sort algorithm implementation.
- `merge-sort.exe`: The compiled binary of `merge-sort.c` for Windows.
- `merge-sort.bin`: The compiled binary of `merge-sort.c` for MacOS.

## Options:
- `-h` and `--help` print a usage manual to stdout.
- `-v` visually represents the sorting process. Implies `--delay 50` unless overriden. Implies `-r`.
- `-r` upon completion, print the runtime
- `--delay time` sets a delay of <ins>time</ins> milliseconds between each frame of the sorting process. Overrides the delay from `-v`.

## Note(s):
- Make sure to place the numbers to sort **before** the options. Placing options before or in the list will replace final numbers with zeros.

## Current Identified Issue(s) in merge-sort.c:
- using the `-v` option slightly increases the runtime delay.

## Coming Soon:
- Reading/writing to/from file.

## Author:
ion727

