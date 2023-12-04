import multiprocessing as mp
import sys

nbCalcul = 3

def demandeur(pipe_demande, pipe_reponse):
    # Exemple de demande : (id_demandeur, opération, opérande1, opérande2)
    for i in range(nbCalcul):
        demande = (i+1, sys.argv[2 + 3*i], (int)(sys.argv[1 + 3*i]), (int)(sys.argv[3 + 3*i]))
        pipe_demande.send(demande)
    
    for i in range(nbCalcul):
        reponse = pipe_reponse.recv()
        print(f"Demandeur {i+1} a reçu la réponse : {reponse}")

def calculateur(pipe_demande, pipe_reponse):
    demande = pipe_demande.recv()
    
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
    
    pipe_reponse.send(reponse)

if __name__ == "__main__":
    pipe_demande_demandeur, pipe_demande_calculateur = mp.Pipe()
    pipe_reponse_demandeur, pipe_reponse_calculateur = mp.Pipe()

    process = []

    for i in range(nbCalcul):
        process_calculateur = mp.Process(target=calculateur, args=(pipe_demande_calculateur, pipe_reponse_calculateur))
        process.append(process_calculateur)
        process_calculateur.start()

    process_demandeur = mp.Process(target=demandeur, args=(pipe_demande_demandeur, pipe_reponse_demandeur))
    process_demandeur.start()

    for i in range(nbCalcul):
        process[i].join()

    process_demandeur.join()

