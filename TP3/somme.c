#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int tube[2], tube2[2], tube3[2], tube4[2], tube5[2];
    int res = pipe(tube), res2 = pipe(tube2), res3 = pipe(tube3), res4 = pipe(tube4), res5 = pipe(tube5);
    if (res == -1 || res2 == -1 || res3 == -1 || res4 == -1 || res5 == -1)
    {
        perror("Création Pipe");
        exit(-1);
    }

    if (fork() == 0)
    {
        if (fork() == 0)
        {
            // Processus petit-fils - Filtre-Pair
            close(tube[0]);
            close(tube[1]);
            close(tube2[1]);
            close(tube3[0]);
            close(tube3[1]);
            close(tube4[0]);
            close(tube5[0]);
            close(tube5[1]);

            int x = 0;
            int sum = 0;
            read(tube2[0], &x, sizeof(int));

            while (x != -1)
            {
                printf("Filtre-Pair : %d\n", x);
                sum += x;
                read(tube2[0], &x, sizeof(int));
            }
            close(tube2[0]);
            write(tube4[1], &sum, sizeof(int));
            close(tube4[1]);
        }
        else if (fork() == 0)
        {
            // Processus petit-fils - Filtre-Impair
            close(tube[0]);
            close(tube[1]);
            close(tube2[0]);
            close(tube2[1]);
            close(tube3[1]);
            close(tube4[0]);
            close(tube4[1]);
            close(tube5[0]);

            int x = 0;
            int sum = 0;
            read(tube3[0], &x, sizeof(int));

            while (x != -1)
            {
                printf("Filtre-Impair : %d\n", x);
                sum += x;
                read(tube3[0], &x, sizeof(int));
            }
            close(tube3[0]);
            write(tube5[1], &sum, sizeof(int));
            close(tube5[1]);
        }
        else
        {
            // Processus fils - Filtre
            close(tube[1]);
            close(tube2[0]);
            close(tube3[0]);
            close(tube4[0]);
            close(tube4[1]);
            close(tube5[0]);
            close(tube5[1]);

            int x = 0;

            read(tube[0], &x, sizeof(int));

            while (x != -1)
            {
                if (x % 2 == 0)
                {
                    write(tube2[1], &x, sizeof(int));
                }
                else
                {
                    write(tube3[1], &x, sizeof(int));
                }

                read(tube[0], &x, sizeof(int));
            }
            x = -1;
            write(tube2[1], &x, sizeof(int));
            write(tube3[1], &x, sizeof(int));
            close(tube[0]);
            close(tube2[1]);
            close(tube3[1]);
        }
    }
    else
    {
        // Processus parent - Générateur
        close(tube[0]);
        close(tube2[0]);
        close(tube2[1]);
        close(tube3[0]);
        close(tube3[1]);
        close(tube4[1]);
        close(tube5[1]);
        int x;

        srand(getpid());
        int n = (rand() % 10) + 1;

        for (int i = 0; i < n; i++)
        {
            x = rand() % 10;
            write(tube[1], &x, sizeof(int));
            printf("Generateur : %d\n", x);
        }
        x = -1;
        write(tube[1], &x, sizeof(int));
        close(tube[1]);

        int sumPair;
        int sumImpair;
        read(tube4[0], &sumPair, sizeof(int));
        read(tube5[0], &sumImpair, sizeof(int));

        printf("Somme des nombres pairs : %d\n", sumPair);
        printf("Somme des nombres impairs : %d\n", sumImpair);

        close(tube4[0]);
        close(tube5[0]);
    }
}