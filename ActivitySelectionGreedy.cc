/*
 * Dynamic Programing Approach
 * Let us denote by Sᵢⱼ the set of activities that start after
 * activity aᵢ finishes and that finish before activity aⱼstarts.
 * Let us denote the size of an optimal solution for the set Sᵢⱼ
 * by c[i,j], then we would have the recurrence
 * c[i,j] = c[i,k] + c[k,j] + 1
 * If we did not know that an optimal solution for the set Sᵢⱼ
 * includes activity aₖ, we would have to examine all activities
 * in Sᵢⱼ to find which one to choose, so that
 * c[i,j] = 0, if Sᵢⱼ = ∅
 * c[i,j] = max{c[i,k] + c[k,j] + 1}, where aₖ∈Sᵢⱼ if Sᵢⱼ ≠ ∅
 *
 * Greedy Choice
 * we should choose an activity that leaves the resource
 * available for as many other activities as possible.Now, of the
 * activities we end up choosing, one of them must be the first
 * one to finish. Our intuition tells us, therefore, to choose
 * the activity in S with the earliest finish time, since that
 * would leave the resource available for as many of the
 * activities that follow it as possible. (If more than one
 * activity in S has the earliest finish time, then we can choose
 * any such activity.)
 *
 * We assume that the n input activities are already ordered by
 * monotonically increasing finish time, according to equation.
 *
 * let Sₖ = {aᵢ ∈ S : sᵢ ≥ fₖ} be the set of activities that
 * start after activity aₖ finishes.
 *
 * RECURSIVE-ACTIVITY-SELECTOR(s,f,k,n)
 * 	m = k + 1
 * //find he first activity in Sₖ to finish
 * 	while m ≤ n and s[m] < f[k]	
 * 		m = m + 1
 * 	if m ≤ n
 * 		return {aₘ} ∪ RECURSIVE-ACTIVITY-SELECTOR(s,f,m,n)
 * 	else return ∅
 *
 * GREEDY-ACTIVITY-SELECTOR(s,f)
 * 	n = s.length
 * 	A = {a₁}
 * 	k = 1
 * 	for m = 2 to n
 * 		if s[m] ≥ f[k]
 * 			A = A ∪ {aₘ}
 * 			k = m
 * 	return A
 */
