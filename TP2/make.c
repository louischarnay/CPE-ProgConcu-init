#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


#define GCC "gcc"
#define C_FLAG "-c"
#define WALL_FLAG "-Wall"
#define WEXTRA_FLAG "-Wextra"
#define O_FLAG "-o"

// strcat et strtok modifient le tableau de caractères passé en paramètre
// la commande file ... permet de connaitre le type d'un fichier => executable

int generate_object_file(char** filenames, const int size);
void rename_files(char** filenames, const int size, char** compiled);

int main(int argc, char *argv[]) {

    for(int i = 1; i < argc; i++){
        // check if the file are .c files
        if(strstr(argv[i], ".c") == NULL){
            perror("not a .c file");
            exit(-1);
        }
    }

    int status_compilation = generate_object_file(argv, argc);
    
    if(status_compilation < 0){
        perror("error in compilation");
        exit(-1);
    }
    
    int status;
    pid_t terminated_pid;

    // Wait for all children to terminate
    while ((terminated_pid = wait(&status)) != -1) {}

    //Generate executable
    char *compiled[argc - 1];

    rename_files(argv, argc, compiled);


    char* executables = malloc(strlen(argv[argc - 1]) + 3);

    // on retire les 2 derniers caractères de argv[argc - 1] (".c")
    strncpy(executables, argv[argc - 1], strlen(argv[argc - 1]) - 2);
    strcat(executables, ".out");

    char *params[argc + 4];

    // GCC
    params[0] = GCC;

    // GCC file1.o file2.o ... 
    for (int i = 1; i < argc; i++) {
        params[i] = compiled[i - 1];
    }

    // GCC file1.o file2.o ... -o executable
    params[argc] = O_FLAG;
    params[argc + 1] = executables;
    params[argc + 2] = NULL;

    int child_pid = fork();

    if(child_pid == 0) {
        int error = execvp(GCC, params);

        if (error == -1){
            // not exit because we want to free the memory
            perror("exec fail");
        }
    }
    else {
        // wait for the last child to terminate
        wait(NULL);       
    }


    // executed by the parent and the child to avoid memory leaks
    free(executables);
    for(int i = 0; i < argc - 1; i++){
        free(compiled[i]);
    }

    return 0;
}

int generate_object_file(char** filenames, const int size){
    for (int i = 1; i < size; i++) {

        int pid = fork();
        if(pid == 0) {
            char *param[] = { GCC,C_FLAG,WALL_FLAG,WEXTRA_FLAG,filenames[i],NULL};
            int error = execvp("gcc", param);

            if (error == -1) {
                perror("exec fail for object files");
                return error;
            }
        }
        else if(pid == -1) {
            perror("fork fail");
            return -2;
        }
    }
    return 0;
}


void rename_files(char** filenames, const int size, char** compiled){
    for (int i = 1; i < size; i++) {
        //strtok(argv[i], "."); // strtok("test.c", ".") -> "test"
        //strtok fonctionne mais modifier argv[i] n'est pas une bonne idée

        compiled[i - 1] = malloc(strlen(filenames[i]) + 3);

        // on retire les 2 derniers caractères de argv[i] (".c")
        strncpy(compiled[i - 1], filenames[i], strlen(filenames[i]) -2);
        // on ajoute ".o" à la fin de argv[i]
        strcat(compiled[i - 1], ".o");
    }
}