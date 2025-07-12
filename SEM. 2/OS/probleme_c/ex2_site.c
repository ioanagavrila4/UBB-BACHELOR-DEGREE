//Scrieti un program C care creeaza o ierarhie liniara de n procese (procesul parinte creeaza un proces fiu, care la randul lui creeaza un proces fiu, samd.)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>}
int main(int argc, char *argv[]){
    if(argc != 2){

        perror("Please provide exactly one argument");
        exit(1);
    }
    int n=atoi(argv[1]);
    for(int i = 1; i <=n; i++){
        int f=fork();
        if(-1==f){
            perror("An error was for fork!");
            exit(1);
        }else if(0 == f){
            printf("Child process: %d - PID %d - PPID: %d\n", i, getpid(),getppid());
        }else{
            printf("Parent %d - Child: %d\n", getpid(), f);
            wait(0);
            exit(0);
        }
    }
    return 0;
}
