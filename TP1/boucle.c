#include <stdio.h>
#include <unistd.h>

int main(void){
    for(int i = 0; i < 3; i++)
    {
        pid_t fils = fork();
        pid_t pere = getppid();
        pid_t moi = getpid();
        printf("%d - Je suis %d, mon père est %d, fork à retourner %d\n",i,moi,pere,fils);
    }
}