#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    //Implement a process that creates a child process, and communicates with it using pipe.
    //Parent process sends to child process 2 numbers and the child process returns through pipe their sum.
   //creating the pipe

    int p[2];
    int p1[2];
    if(pipe(p) < 0){
        perror("ERROR ON CREATING THE PIPE!!");
        exit(1);
    }
    if(pipe(p1) < 0){
        perror("ERROR ON CREATING THE  SECOND PIPE!!");
        exit(1);
    }
    int f = fork();
    if(f == -1){
        //error on fork
        perror("Error on creating the child");
        exit(1);
    }else if(f == 0){
    //ne aflam in procesul copil
        close(p[1]); //din p doar citim
        close(p1[0]); // din p1 doar scriem
        int a, b, res;
        if(read(p[0], &a, sizeof(int)) < 0){
            perror("Error on reading the number a");
            exit(1);
        }
        if(read(p[0], &b, sizeof(int)) < 0){
            perror("Error on reading the number b");
            exit(1);
        }
        res = a + b;
        if(write(p1[1], &res, sizeof(int)) < 0){
            perror("Error on sending the result");
            exit(1);
        }
        close(p[0]);
        close(p1[1]);
        exit(1);
    }else{
        //ne aflam in parinte
        int a, b, res;
        a = 4;
        b = 87;
        close(p[0]); //doar scriem in p
        if(write(p[1], &a, sizeof(int)) < 0){
            perror("Error on sending the number");
            exit(1);
        }
        if(write(p[1], &b, sizeof(int)) < 0){
            perror("Error on sending the number b");
            exit(1);
        }

        close(p1[1]); //din pipe 1 doar citim
        if(read(p1[0], &res, sizeof(int)) < 0){
            perror("Error on reading the result");
            exit(1);
        }
        printf("THE RESULT YOU ARE WAITING IS: %d", res);
        close(p[1]);
        close(p1[0]);
        wait(0);
    }

    return 0;
}
