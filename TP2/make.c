#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// strcat et strtok modifient le tableau de caractères passé en paramètre
// la commande file ... permet de connaitre le type d'un fichier => executable

int main(int argc, char *argv[]) {
    //Generate .o files
    for (int i = 1; i < argc; i++) {

        if (fork() == 0) {
            char *param[] = { "gcc","-c","-Wall","-Wextra",argv[i],NULL};
            int error = execvp("gcc", param);
            if (error == -1)
            {
                perror("exec fail");
                exit(-1);
            }
        }
    }
    int status;
    pid_t terminated_pid;

    while ((terminated_pid = wait(&status)) != -1) {}

    //Generate executable

    char *executables[1];
    char *compiled[argc - 1];

    for (int i = 1; i < argc; i++) {
        strtok(argv[i], "."); // strtok("test.c", ".") -> "test"

        compiled[i - 1] = malloc(strlen(argv[i]) + 3);

        strcpy(compiled[i - 1], argv[i]);
        strcat(compiled[i - 1], ".o");
    }

    executables[0] = malloc(strlen(argv[argc - 1]) + 3);
    strcpy(executables[0], argv[argc - 1]);

    for (int i = 0; i < argc - 1; i++) {
    }

    char *param2[argc + 4];

    param2[0] = "gcc";

    for (int i = 1; i < argc; i++) {
        param2[i] = compiled[i - 1];
    }

    param2[argc] = "-o";
    param2[argc + 1] = executables[0];
    param2[argc + 2] = NULL;

    for (int i = 0; i < argc + 2; i++) {
        printf("param2[%d] = %s\n", i, param2[i]);
    }

    int error = execvp("gcc", param2);
    if (error == -1)
    {
        perror("exec fail");
        exit(-1);
    }

    return 0;
}