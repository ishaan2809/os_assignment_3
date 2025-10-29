/**
 * This file implements parallel mergesort.
 * Author: Ishaan Das And Seth Alenchery
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend)
{
	int i = leftstart;		// index of temp array B
	int left = leftstart;	// index of left subarray
	int right = rightstart; // index of right subarray

	while (left <= leftend && right <= rightend)
	{
		if (A[left] <= A[right])
		{
			B[i] = A[left];
			left++;
			i++;
		}
		else
		{
			B[i] = A[right];
			right++;
			i++;
		}
	}
  // copy any remaining elements from left half
	while (left <= leftend)
	{
		B[i] = A[left];
		left++;
		i++;
	}
  // copy any remaining elements from right half
	while (right <= rightend)
	{
		B[i] = A[right];
		right++;
		i++;

	}
	
    // copy merged elements back from the temporary array (the array that's basically empty) B into A
	//void *memcpy(void *dest, const void *src, size_t n); destination, source, number of bytes to copy
	memcpy(A + leftstart, B + leftstart, (rightend - leftstart + 1) * sizeof(int));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right)
{
	   if (left >= right)
        return;

	   int mid = (left + right) / 2;
	   my_mergesort(left, mid); //split left half 
	   my_mergesort(mid + 1, right); //split right half
	   merge(left, mid, mid + 1, right); // merge the two halves
}

/* this function will be called by the testing program. */
//In parallel merge sort, instead of sorting the left half then the right half,
we sort both halves at the same time using separate threads.
void *parallel_mergesort(void *arg)
{
	struct argument *args = (struct argument *) arg;
    int left = args->left;
    int right = args->right;
    int level = args->level;

    // Base case: If only one element, or we’ve hit cutoff depth
	//→ stop creating new threads,
	//→ just sort normally (serially) using my_mergesort().
    if (left >= right) {
        free(arg);
        return NULL;
    }
	   if (level >= cutoff) {
        my_mergesort(left, right);
        free(arg);
        return NULL;
    }

	 int mid = (left + right) / 2;

    // Prepare arguments for left and right halves
    struct argument *leftArg = buildArgs(left, mid, level + 1);
    struct argument *rightArg = buildArgs(mid + 1, right, level + 1);

    pthread_t tid1, tid2;

    // Create two threads to handle both halves
    pthread_create(&tid1, NULL, parallel_mergesort, leftArg);
    pthread_create(&tid2, NULL, parallel_mergesort, rightArg);

    // Wait for both halves to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Merge the two sorted halves
    merge(left, mid, mid + 1, right);

    // Free current arg memory
    free(arg);
    return NULL;
}

/* we build the argument for the parallel_mergesort function. */
// Imagine each thread is a worker, and you can only give them one envelope when they start.
// So you put everything they need (left, right, level) inside that envelope (struct argument),
// and hand it to them.

//so basically rather than passsing 3 arguemnets indivuallay we are performing thread approach each left right and level will get handled in it's own thread, So each (left, right, level) combo runs in its own thread concurrently.
struct argument *buildArgs(int left, int right, int level)
{
	struct argument *arg; 
	arg = malloc(sizeof(struct argument));
    arg->left = left;
    arg->right = right;
    arg->level = level;
    return arg;
}
