/*
 * Worst-case running time O(n lg n)
 *
 * min-heap property:	A[PARENT(i)] ≤ A[i]
 * max-heap property: A[PARENT(i)] ≥ A[i]
 * PARENT(i)
 * 	return ⎣ i/2 ⎦
 *
 * LEFT(i)
 * 	return 2i
 *
 * RIGHT(i)
 * 	return 2i + 1
 *
 * MAX-HEAPIFY(A,i)
 *	//lets the value at A[i] float down, subtree rooted at i
 *	//obeys the max-heap property
 * 	l = LEFT(i)
 * 	r = RIGHT(i)
 * 	if l ≤ A.heap-size and A[l] > A[i]
 * 		largest = l
 * 	else largest = i
 * 	if r ≤ A.heap-size and A[r] > A[largest]
 * 		largest = r
 * 	if largest ≠ i
 * 		exchange A[i] with A[largest]
 * 		MAX-HEAPIFY(A,largest)
 *
 * BUILD-MAX-HEAP(A)
 * 	A.heap-size = A.length
 * 	for i = ⎣ A.length/2 ⎦ down to 1
 * 		MAX-HEAPIFY(A,i)
 *
 * HEAPSORT(A)
 * 	BUILD-MAX-HEAP(A)
 * 	for i = A.length downto 2
 * 		exchange A[1] with A[i]
 * 		A.heap-size = A.heap-size - 1
 * 		MAX-HEAPIFY(A,1)
 */
