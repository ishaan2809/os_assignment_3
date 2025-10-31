## Project Number/Title 

* Authors: Ishaan and Seth 
* Group name: A buffer group 3
## Overview

This program implements a parallel version of the merge sort algorithm using the pthread library. It divides an array into smaller subarrays and sorts them concurrently using multiple threads, improving performance compared to the standard single-threaded merge sort. The depth of parallelism is controlled by a user-specified cutoff level, which determines how many levels of threads are created.

## Manifest

mergesort.c – Implements the merge sort algorithm and its multithreaded (parallel) version using pthreads.

mergesort.h – Header file containing global variables, function prototypes, and struct definitions used across the program.

test-mergesort.c – Testing driver that generates a random array, calls the sorting functions, and measures execution time.

## Building the project

To build the program, run the following commands:
make clean
make

## Features and usage

Main Features

Implements both serial and parallel versions of the merge sort algorithm.

Utilizes the pthread library to enable multi-threaded (parallel) execution.

Allows the user to specify a cutoff level, controlling how many levels of threads are spawned.

Automatically merges sorted subarrays once all threads have completed execution.

Displays execution time to show the performance improvement from parallel sorting.

## Testing
The provided testing program test-mergesort.c takes three command-line parameters:

Array Size (n) – the number of elements to sort (where n ≥ 100).

Cutoff Level – determines how deep new threads are created in the parallel merge sort.

Random Seed – used to generate a reproducible random array for sorting.

The program generates a random array of size n and executes the following:

struct argument *arg = buildArgs(0, n - 1, 0);
parallel_mergesort(arg);


This sorts the array and measures the total execution time.

When the cutoff level = 0, the program performs a single-threaded (serial) merge sort.

When the cutoff level > 0, it performs a multi-threaded (parallel) merge sort using the pthread library.

On the Onyx server, using an array size of 100 million elements, the parallel implementation is expected to achieve at least a 2× speedup compared to the serial version.

## Known Bugs

N/A

## Reflection and Self Assessment

We found this assignment straightforward and enjoyable to complete. Most of the testing and framework code was already provided, so our main focus was implementing the merge sort and parallel merge sort logic. Once we understood how the pthread library and the buildArgs() function worked, the rest of the development process felt very smooth.

We did not encounter any major issues during development. The concepts of thread creation, joining, and recursion were easy to apply once the structure became clear. Testing program made it simple to verify correctness and performance without needing to write additional code.

Overall, this project helped reinforce our understanding of multithreading and how parallel execution can improve performance for divide-and-conquer algorithms like merge sort. I
We genuinely enjoyed working on it and appreciated how cleanly everything came together.

## Sources Used
https://www.youtube.com/watch?v=86HOPLCgc00&t=2859s
https://leetcode.com/problems/merge-sorted-array/
https://stackoverflow.com/questions/1163624/memcpy-with-startindex
