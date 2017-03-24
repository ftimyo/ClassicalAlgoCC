/*
 * Problem and analysis is well defined in my CLRS reading note
 * Here it only gives the Pseudocode and my pseudocode solution
 * to optimal solution construction
 *
 * OPTIMAL-BST(p,q,n)
 * 	let e[1..n+1,0..n],w[1..n+1,0..n],root[1..n,1..n] be new
 * 			tables
 * 	for i = 1 to n + 1
 * 		e[i,i-1] = qᵢ₋₁
 * 		w[i,i-1] = qᵢ₋₁
 * 	for l = 1 to n
 * 		for i = 1 to n - l + 1
 * 			j = i + l - 1
 * 			e[i,j] = ∞
 * 			w[i,j] = w[i,j-1] + pⱼ+ qⱼ
 * 			for r = i to j
 * 				t = e[i,r-1] + e[r+1,j] + w[i,j]
 * 				if t < e[i,j]
 * 					e[i,j] = t
 * 					root[i,j] = r
 * 	return e and root
 *
 * def BuildBST(root,i,j):
 * 	if i < j:
 * 		return None
 * 	r = root[i][j]
 * 	k = Key(r)
 * 	k.left = BuildBST(root,i,r-1)
 * 	k.right = BuildBST(root,r+1,j)
 * 	if not k.left:
 * 		k.left = DummyKey(r-1)
 * 	if not k.right:
 * 		k.right = DummyKey(r)
 *
 */
