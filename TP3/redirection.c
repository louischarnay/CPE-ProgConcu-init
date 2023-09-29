#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    // Exercice 1 //

    // int input = open("/etc/passwd", O_RDONLY);

    // if (input == -1) {
    //     perror("Open");
    //     exit(-1);
    // }

    // dup2(input, 0);

    // execlp("wc", "wc", NULL);

    // Exercice 2 //

    // int tube[2];

    // int res = pipe(tube);

    // if (res == -1) {
    //     perror("Création Pipe");
    //     exit(-1);
    // }

    // if (fork() == 0) {
    //     close(tube[1]);
    //     dup2(tube[0], 0);
    //     close(tube[0]);

    //     execlp("tr", "tr", "a-z", "A-Z", NULL);
    // }

    // else {
    //     int input = open("/etc/passwd", O_RDONLY);

    //     if (input == -1) {
    //         perror("Open");
    //         exit(-1);
    //     }

    //     close(tube[0]);
    //     dup2(input, 0);
    //     dup2(tube[1], 1);
    //     close(input);
    //     close(tube[1]);

    //     execlp("cut", "cut", "-f", "1", "-d", ":", NULL);
    // }

    // Exercice 3 //

    
    return 0;
}