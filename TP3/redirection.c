#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void exercice_1()
{
    // Exercice 1 //
    int input = open("/etc/passwd", O_RDONLY);
    if (input == -1)
    {
        perror("Open");
        exit(-1);
    }
    dup2(input, 0);
    execlp("wc", "wc", NULL);
}

void exercice_2()
{
    // Exercice 2 //
    int tube[2];
    int res = pipe(tube);
    if (res == -1)
    {
        perror("Création Pipe");
        exit(-1);
    }
    if (fork() == 0)
    {
        close(tube[1]);
        dup2(tube[0], 0);
        close(tube[0]);
        execlp("tr", "tr", "a-z", "A-Z", NULL);
    }
    else
    {
        close(tube[0]);
        dup2(tube[1], 1);
        close(tube[1]);
        execlp("cut", "cut", "-f", "1", "-d", ":", NULL);
    }
}

void exercice_3()
{
    // Exercice 3 //
    int tube1[2];
    int res1 = pipe(tube1);

    int tube2[2];
    int res2 = pipe(tube2);

    if (res1 == -1 || res2 == -1)
    {
        perror("Création Pipe");
        exit(-1);
    }

    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (child_pid == 0)
    { // Code exécuté par le fils
        pid_t child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (child_pid == 0)
        {
            int output = open("users", O_CREAT | O_WRONLY, 0644);
            dup2(output, 1);
            close(output);

            close(tube2[1]);
            dup2(tube2[0], 0);
            close(tube2[0]);
            close(tube1[1]);
            close(tube1[0]);
            execlp("sort", "sort", "-n", NULL);
        }
        else
        {
            close(tube1[1]);
            dup2(tube1[0], 0);
            close(tube1[0]);

            close(tube2[0]);
            dup2(tube2[1], 1);
            close(tube2[1]);
            execlp("sed", "sed", "s+^\\(.*\\):\\(.*\\)+\\2:\\1+", NULL);
        }
    }
    else
    {
        int input = open("/etc/passwd", O_RDONLY);
        dup2(input, 0);
        close(input);

        close(tube1[0]);
        dup2(tube1[1], 1);
        close(tube1[1]);
        close(tube2[1]);
        close(tube2[0]);
        execlp("cut", "cut", "-f", "1,3", "-d", ":", NULL);
    }
}

int main()
{
    exercice_3();
    return 0;
}