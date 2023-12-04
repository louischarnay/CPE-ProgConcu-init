import time
import random
import multiprocessing as mp

from multiprocessing import Process 

class Controller:
    def __init__(self, max_billes):
        self.nbr_billes_disponible = mp.Value('i', max_billes)
        self.max_billes = max_billes
        self.semaphore = mp.Semaphore()

    def demander(self, nbr_billes):
        self.semaphore.acquire()
        nbr_billes_disponible = self.nbr_billes_disponible.value
        self.semaphore.release()

        while nbr_billes_disponible < nbr_billes:
            time.sleep(1)
            self.semaphore.acquire()
            print("Le processus {} ne peut pas prendre {} billes.".format(mp.current_process().ident, nbr_billes))
            nbr_billes_disponible = self.nbr_billes_disponible.value
            self.semaphore.release()

        self.semaphore.acquire()
        self.nbr_billes_disponible.value -= nbr_billes
        print("Le processus {} a pris {} billes.".format(mp.current_process().ident, nbr_billes))
        self.semaphore.release()

    def rendre(self, nbr_billes):
        self.semaphore.acquire()
        self.nbr_billes_disponible.value += nbr_billes
        print("Le processus {} a rendu {} billes.".format(mp.current_process().ident, nbr_billes))
        self.semaphore.release()

    def verifier_disponibilite(self):
        while True:
            time.sleep(1)
            self.semaphore.acquire()
            print("Il y a {} billes disponibles.".format(self.nbr_billes_disponible.value))
            self.semaphore.release()

class ProcessusTravailleur:
    def __init__(self, identifiant, controller):
        super(ProcessusTravailleur, self).__init__()
        self.identifiant = identifiant
        self.controller = controller
        self.m = 3  # Remplacez cela par le nombre d'itérations souhaité

    def run(self):
        for _ in range(self.m):
            nbBilles = random.randint(1, 5)
            self.controller.demander(nbBilles)
            time.sleep(random.randint(1, 5))
            self.controller.rendre(nbBilles)

if __name__ == "__main__":
    max_billes = 9  # Remplacez cela par le nombre maximum de billes disponibles

    controller = Controller(max_billes)
    processusController = Process(target=controller.verifier_disponibilite)
    processusController.start()

    n_processus = 5  # Remplacez cela par le nombre de processus souhaité
    tabProcessus = []

    for i in range(n_processus):
        processus_travailleurs = ProcessusTravailleur(i, controller)
        processus = Process(target=processus_travailleurs.run)
        tabProcessus.append(processus)
        processus.start()

    for processus in tabProcessus:
        processus.join()

    print("Tous les processus sont terminés.")
    
    print("Il y a {} billes disponibles.".format(controller.nbr_billes_disponible.value))

    processusController.terminate()

    print("Fin du programme.")