/*
 * Suprise: Fast MinMax implementation
 * def MinMax(A,n)
 * 	for i = 2 to n:
 * 		r = A[i]
 * 		l = A[i-1]
 * 		if l < r:
 * 			min = Min(l,min)
 * 			max = Max(r,max)
 * 		else:
 * 			min = Min(r,min)
 * 			max = Max(l,max)
 * 	return min,max
 *
 * As in quicksort, we partition the input array recursively. But
 * unlike quicksort, which recursively process both sides of the
 * partition. RANDOMIZED-SELECT works on only one side of the
 * partition. This difference shows up in the analysis: whereas
 * quicksort has an expected running time of 𝚯(n lg n), the
 * expected running time of RANDOMIZED-SELECT is 𝚯(n), assuming
 * that the elements are distinct.
 *
 * RANDOMIZED-SELECT(A,p,r,i)
 * 	if p == r
 * 		return A[p]
 * 	q = RANDOMIZED-PARTITION(A,p,r)
 * 	k = q - p + 1
 * 	if i == k			//the pivot value is the answer
 * 		return A[q]
 * 	elseif i < k
 * 		return RANDOMIZED-SELECT(A,p,q-1,i)
 * 	else return RANDOMIZED-SELECT(A,q+1,r,i-k)
 *
 * RANDOMIZED-PARTITION(A,p,r)
 * 	i = RANDOM(p,r)
 * 	exchange A[r] with A[i]
 * 	return PARTITION(A,p,r)
 */
