import random

def monte_carlo_pi(n):
    hits = 0

    for _ in range(n):
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)

        # Vérifier si le point est à l'intérieur du cercle unitaire
        if x**2 + y**2 <= 1:
            hits += 1

    # Calculer l'estimation de π
    pi_estimate = 4 * hits / n

    return pi_estimate

# Nombre de points à générer
num_points = 1000000

# Estimer π en utilisant la méthode de Monte-Carlo
pi_approximation = monte_carlo_pi(num_points)

print(f"Estimation de π avec {num_points} points : {pi_approximation}")
