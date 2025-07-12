#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[]){
    for(int i=0; i<3; i++) {
        if(fork() > 0) {
            printf("PROCESUL %d: %d", i, getpid());
            wait(0);
            wait(0);
            exit(0);
        }
    }
    return 0;
}
