/*
 * Define subsequence
 * Given a sequence X = ＜x₁,x₂,...,xₘ＞, another sequence
 * Z = ＜z₁,z₂,...,zₖ＞ is a subsequence of X if there exists a
 * strictly increasing sequence ＜i₁,i₂,...,iₖ＞ of indices of X
 * such that for all j = 1,2,...,k, we have X[iⱼ]= zⱼ.
 *
 * Define common subsequence
 * Given two sequences X and Y, we say that a sequence Z is a
 * common subsequence of X and Y if Z is a subsequence of both X
 * and Y.
 *
 * Problem:
 * Given two sequences X = ＜x₁,x₂,...,xₘ＞ and Y = ＜y₁,y₂,...,yₙ＞
 * and wish to find the maximum-length common subsequence of X and Y
 *
 * Optimal substructure of an LCS
 * 1. If xₘ=yₙ,then zₖ=xₘ=yₙ and Zₖ₋₁ is an LCS of Xₘ₋₁ and Yₙ₋₁.
 * 2. If xₘ≠yₙ,then zₖ≠xₘ implies Z is an LCS of Xₘ₋₁ and Y.
 * 3. If xₘ=yₙ,then zₖ≠yₙ implies Z is an LCS of X and Yₙ₋₁.
 *
 * Let us define c[i,j] to be the length of an LCS of the
 * sequences Xᵢ and Xⱼ. If either i = 0 or j = 0, LCS is 0.
 * c[i,j] = 0												if i = 0 or j = 0,
 * c[i,j] = c[i-1,j-1] + 1					if i,j > 0 and xᵢ=yⱼ,
 * c[i,j] = max(c[i,j-1],c[i-1,j])	if i,j > 0 and xᵢ≠yⱼ.
 *
 * To Construct the optimal solution, let b[i,j] point to the
 * table entry corresponding to the optimal subproblem solution
 * chosen when computing c[i,j].
 *
 * LCS-LENGTH(X,Y)
 * 	m = X.length
 * 	n = Y.length
 * 	let b[1..m,1..n] and c[0..m,0..n] be new tables
 * 	for i = 1 to m
 * 		c[i,0] = 0
 * 	for j = 0 to n
 * 		c[0,j] = 0
 * 	for i = 1 to m
 * 		for j = 1 to n
 * 			if xᵢ == yⱼ
 * 				c[i,j] = c[i-1,j-1] + 1
 * 				b[i,j] = "↖︎"
 * 			elseif c[i-1,j] ≥ c[i,j-1]
 * 				c[i,j] = c[i-1,j]
 * 				b[i,j] = "↑"
 * 			else
 * 				c[i,j] = c[i,j-1]
 * 				b[i,j] = "←"
 * 	return c and b
 *
 * PRINT-LCS(b,X,i,j)
 * 	if i == 0 or j == 0
 * 		return
 * 	if b[i,j] == "↖︎"
 * 		PRINT-LCS(b,X,i-1,j-1)
 * 		print xᵢ
 * 	elseif b[i,j] == "↑"
 * 		PRINT-LCS(b,X,i-1,j)
 * 	else PRINT-LCS(b,X,i,j-1)
 *
 */
