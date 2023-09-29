#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    for (int i = 0; i < 3; i++)
    {     
        int status;
        pid_t fils = fork();
        if (fils == 0)
        {
            if (i == 0)
            {
                char *argv[4] = { "du","-sh","/usr/share", NULL };
                int error = execvp("du", argv);
                if (error == -1)
                {
                    perror("exec fail");
                    exit(-1);
                }
                break;
            }
            else if (i == 1)
            {
                char *argv[3] = { "ls","-l",NULL };
                int error = execvp("ls", argv);
                if (error == -1)
                {
                    perror("exec fail");
                    exit(-1);
                }
                break;
            }
            else if (i == 2)
            {
                char *argv[2] = { "ps", NULL };
                int error = execvp("ps", argv);
                if (error == -1)
                {
                    perror("exec fail");
                    exit(-1);
                }
                break;
            }
        }
        wait(&status);
    }
    return 0;
}