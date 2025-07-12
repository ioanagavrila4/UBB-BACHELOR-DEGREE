#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>
int main(int argc, char *argv[]){

    if(argc!=2){
        perror("Please put a valid no of arguments!");
        exit(1);
    }




    return 0;
}
