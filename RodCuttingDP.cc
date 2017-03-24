/*
 * Problem: Given a rod of length n inches and a table of prices
 * pi for i = 1,2,...,n, determine the maximum revenue rn
 * obtainable by cutting up the rod and selling the pieces. Note
 * that if the price pn for a rod of length n is large enough, an
 * optimal solution may require no cutting at all.
 *
 * rₙ = max(pᵢ + rₙ₋ᵢ), where 1≤i≤n.
 * ie.
 * rₙ = max(pₙ,r₁ + rₙ₋₁,r₂ + rₙ₋₂,...,rₙ₋₁ + r₁)
 *
 * //Top-down with memoization
 * MEMOIZED-CUT-ROD(p,n)
 * 	let r[0..n] be a new array
 * 	for i = 0 to n
 * 		r[i] = -∞
 * 	return MEMOIZED-CUT-ROD-AUX(p,n,r)
 *
 * MEMOIZED-CUT-AUX(p,n,r)
 * 	if r[n] ≥ 0
 * 		return r[n]
 * 	if n == 0
 * 		q = 0
 * 	else q = -∞
 * 		for i = 1 to n
 * 			q = max(q,p[i]+MEMOIZED-CUT-ROD-AUX(p,n-i,r))
 *	r[n] = q
 *	return q
 *
 * //bottom-up
 * BOTTOM-UP-CUT-ROD(p,n)
 * 	let r[0..n] be a new array
 * 	r[0] = 0
 * 	for j = 1 to n
 * 		q = -∞
 * 		for i = 1 to j
 * 			q = max(q,p[i]+r[j-i])
 * 		r[j] = q
 * 	return r[n]
 *
 * //extend bottom-up
 * EXTENDED-BOTTOM-UP-CUT-ROD(p,n)
 * 	let r[0..n] and s[0..n] be a new array
 * 	r[0] = 0
 * 	for j = 1 to n
 * 		q = -∞
 * 		for i = 1 to j
 * 			if q < p[i] + r[j-i]
 * 				q = p[i]+r[j-i]
 * 				s[j] = i
 * 		r[j] = q
 * 	return r and s
 *
 * PRINT-CUT-ROD-SOLUTION(p,n)
 * 	(r,s) = EXTENDED-BOTTOM-UP-CUT-ROD(p,n)
 * 	while n > 0
 * 		print s[n]
 * 		n = n - s[n]
 */
