/*
 * Worst-case running time 𝚯(n lg n), Average-case 𝚯(n lg n)
 * Merge sort has a better asymptotic running time, but it does
 * not operate in place
 */
/*
 * MERGE(A,p,q,r)
 * 	n₁ = q - p + 1
 * 	n₂ = r - q
 * 	let L[1..n₁+1] and R[1..n₂+1] be new arrays
 * 	for i = 1 to n₁
 * 		L[i] = A[p+i-1]
 * 	for j = 1 to n₂
 * 		R[j] = A[q+j]
 * 	L[n₁+1] = ∞
 * 	R[n₂+1] = ∞
 * 	i = 1
 * 	j = 1
 * 	for k = p to r
 * 		if L[i] ≤ R[j]
 * 			A[k] = L[i]
 * 			i = i + 1
 * 		else A[k] = R[j]
 * 			j = j + 1
 *
 * MERGE-SORT(A,p,r)
 * 	if p < r
 * 		q = ⎣ (p+r)/2 ⎦
 * 		MERGE-SORT(A,p,q)
 * 		MERGE-SORT(A,q+1,r)
 * 		MERGE(A,p,q,r)
 */
