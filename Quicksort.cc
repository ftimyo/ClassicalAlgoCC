/*
 * Worst-case running time 𝚯(n²), average-case 𝚯(n lg n)
 * Divide:
 * Partition (rearrange) the array A[p..r] into two (possibly
 * empty) subarrays A[p..q-1] and A[q+1..r] such that each
 * element of A[p..q-1] is less than or equal to A[q], which is,
 * in turn, less than or equal to each element of A[q+1..r].
 * Compute the index q as part of this partitioning procedure.
 * Conquer:
 * Sort the two subarrays A[p..q-1] and A[q+1..r] by recursive
 * calls to quicksort.
 * Combine:
 * Because the subarrays are already sorted, no work is needed to
 * combine them: the entire array A[p..r] is now sorted.
 *
 * QUICKSORT(A,p,r)
 * 	if p < r
 * 		q = PARTITION(A,p,r)
 * 		QUICKSORT(A,p,q-1)
 * 		QUICKSORT(A,q+1,r)
 *
 * PARTITION(A,p,r)
 * 	x = A[r]
 * 	i = p - 1
 * 	for j = p to r - 1
 * 		if A[j] ≤ x
 * 			i = i + 1
 * 			exchange A[i] with A[j]
 * 	exchange A[i+1] with A[r]
 * 	return i + 1
 */
