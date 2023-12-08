import random
import multiprocessing as mp

def monte_carlo_pi(hits, num_points, lock):

    nbHits = 0
    point = 0

    while point < num_points :
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)

        # Vérifier si le point est à l'intérieur du cercle unitaire
        if x**2 + y**2 <= 1:
            nbHits += 1

        point += 1

    lock.acquire()
    hits.value += nbHits
    lock.release()
            
    # Calculer l'estimation de π
    # pi_approximation = 4 * hits.value / num_points.value

if __name__ == "__main__":
    # Nombre de points à générer
    num_processes = 100
    num_points = 1000000/num_processes
    hits = mp.Value('i',0)

    lock = mp.Lock()

    process = []

    for i in range(num_processes):
        process_calculateur = mp.Process(target=monte_carlo_pi, args=(hits, num_points, lock))
        process.append(process_calculateur)
        process_calculateur.start()

    for i in range(num_processes):
        process[i].join()

    print(f"Estimation de π avec {num_points} points : {4 * hits.value / (num_points * num_processes)}")