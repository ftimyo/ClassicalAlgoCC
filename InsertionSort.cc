/*
 * Worst-case running time 𝚯(n²), Average-case running time 𝚯(n²)
 * Insertion sort is a fast in-place sorting algorithm for small
 * input size due to its tight inner loops.
 */
/*
 * INSERTION-SORT(A)
 * 	for j = 2 to A.length
 * 		key = A[j]
 *  	// Insert A[j] into the sorted sequence A[1..j-1].
 *		i = j - 1
 *		while i > 0 and A[i] > key
 *			A[i+1] = A[i]
 *			i = i - 1
 *		A[i+1] = key
 */
