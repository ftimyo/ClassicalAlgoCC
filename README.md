# ClassicalAlgoCC
Classical Algorithm Implementation in CPP By Timothy Yo (Me)

Some Basics:

𝚯-notation	asymptotic tight bound

	𝚯(g(n)) = {f(n):there exist positive constant c1, c2,
		and n0 such that 0 ≤ c1g(n) ≤ f(n) ≤ c2g(n) for all
		n ≥ n0}

𝚶-notation	asymptotic upper bound

	𝚶(g(n)) = {f(n):there exist positive constant c and n0
		such that 0 ≤ f(n) ≤ cg(n) for all n ≥ n0}

𝛀-notation	asymptotic lower bound

	𝛀(g(n)) = {f(n):there exist positive constant c and n0
		such that 0 ≤ cg(n) ≤ f(n) for all n ≥ n0}

Theorem

	For any two functions f(n) and g(n),
	we have f(n) = 𝚯(g(n)) if and only if
	f(n) = 𝚶(g(n)) and
	f(n) = 𝛀(g(n))
