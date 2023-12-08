import multiprocessing as mp
import sys

nbCalcul = 3

def demandeur(pipe_demande, pipe_reponse, semDemandeur, semCalculateur, id):
    # Exemple de demande : (id_demandeur, opération, opérande1, opérande2)
    semDemandeur.acquire()
    demande = (id+1, sys.argv[2 + 3*id], (int)(sys.argv[1 + 3*id]), (int)(sys.argv[3 + 3*id]))
    print(f"Demandeur {id+1} envoie la demande : {demande}")
    pipe_demande.send(demande)
    semCalculateur.release()
    semReponse.acquire()
    lock.acquire()
    reponse = pipe_reponse.recv()
    lock.release()
    print(f"Demandeur {id+1} a reçu la réponse : {reponse}")

def calculateur(pipe_demande, pipe_reponse, semCalculateur, lock):
    semCalculateur.acquire()
    
    lock.acquire()
    demande = pipe_demande.recv()
    lock.release()

    id_demandeur, operation, operande1, operande2 = demande
    
    if operation == '+':
        reponse = operande1 + operande2
    elif operation == '-':
        reponse = operande1 - operande2
    elif operation == 'x':
        reponse = operande1 * operande2
    elif operation == '/':
        reponse = operande1 / operande2
    else:
        reponse = "Opération non supportée"
    
    lock.acquire()
    pipe_reponse.send(reponse)
    lock.release()

    semReponse.release()

if __name__ == "__main__":
    pipe_demande_demandeur, pipe_demande_calculateur = mp.Pipe()
    pipe_reponse_demandeur, pipe_reponse_calculateur = mp.Pipe()

    lock = mp.Lock()
    semCalculateur = mp.Semaphore(0)
    semDemandeur = mp.Semaphore(nbCalcul)
    semReponse = mp.Semaphore(0)

    process = []

    for i in range(nbCalcul):
        process_calculateur = mp.Process(target=calculateur, args=(pipe_demande_calculateur, pipe_reponse_calculateur, semCalculateur, lock))
        process.append(process_calculateur)
        process_calculateur.start()

    for i in range(nbCalcul):
        process_demandeur = mp.Process(target=demandeur, args=(pipe_demande_demandeur, pipe_reponse_demandeur, semDemandeur, semCalculateur, i))
        process.append(process_demandeur)
        process_demandeur.start()

    for i in range(len(process)):
        process[i].join()