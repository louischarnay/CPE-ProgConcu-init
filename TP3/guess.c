#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int tubeNombre[2];
    int tubeCompare[2];

    int resNombre = pipe(tubeNombre);
    if (resNombre == -1) {
        perror("Création Pipe");
        exit(-1);
    }

    int resCompare = pipe(tubeCompare);
    if (resCompare == -1) {
        perror("Création Pipe");
        exit(-1);
    }

    if (fork() == 0) {
        srand(getpid());
        int random = rand() % 50;
        int guess = 0;

        close(tubeNombre[1]);
        close(tubeCompare[0]);

        while (guess != random)
        {   
            read(tubeNombre[0], &guess, sizeof(int)); // Lecture depuis le tube

            if (guess == random) {
                write(tubeCompare[1], "=", sizeof(char)); // Écriture dans le tube
            } else if (guess > random) {
                write(tubeCompare[1], "-", sizeof(char)); // Écriture dans le tube
            } else {
                write(tubeCompare[1], "+", sizeof(char)); // Écriture dans le tube
            }
        }
        close(tubeNombre[0]);
        close(tubeCompare[1]);
    }
    
    else {
        int guess = 0;
        char compare = ' ';

        close(tubeNombre[0]);
        close(tubeCompare[1]);

        while (compare != '=')
        {
            printf("Enter your guess:\n");
            scanf("%d", &guess);
            
            write(tubeNombre[1], &guess, sizeof(int)); // Écriture dans le tube
            
            read(tubeCompare[0], &compare, sizeof(char)); // Lecture depuis le tube

            printf("Compare: %c\n", compare);
        }
        close(tubeNombre[1]);
        close(tubeCompare[0]);
    }
    return 0;
}