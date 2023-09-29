#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nombre de processus>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);

    for (int i = 0; i < N; i++) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("Erreur lors de la création du processus fils");
            exit(1);
        }

        if (child_pid == 0) {  // Code exécuté par le fils
            printf("Fils [%d] : Mon PID est %d, PID de mon père est %d\n", i, getpid(), getppid());
            sleep(2 * (i + 1));
            printf("Fils [%d] : Je reprends mon exécution avec i=%d\n", i, i);
            exit(i);
        }
    }

    // Code exécuté par le père
    int status;
    pid_t terminated_pid;

    while ((terminated_pid = wait(&status)) != -1) {
        if (WIFEXITED(status)) {
            printf("Le fils [%d] s'est terminé avec la valeur de retour %d\n", terminated_pid, WEXITSTATUS(status));
        } else {
            fprintf(stderr, "Le fils [%d] s'est terminé de manière anormale\n", terminated_pid);
        }
    }

    return 0;
}
