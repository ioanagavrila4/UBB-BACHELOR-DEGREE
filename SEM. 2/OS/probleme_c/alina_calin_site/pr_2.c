//Implement a process that creates two child processes A and B, that communicate using fifo. Process A sends to process B 2 numbers and process B returns to A a random number between the two.
//(Fifo created in the main c program)
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
int main(int argc, char *argv[]){
    //creare de fifo
    if(mkfifo("fifo1", 0666) < 0){
        perror("Error on creating the fifo");
        exit(1);
    }
    if(mkfifo("fifo2", 0666) < 0){
        perror("Error on creating the fifo");
        exit(1);
    }


    int f1 = fork();
    if(f1 < 0){
        perror("Error on creating the first child");
        exit(1);
    }else if(f1 == 0){
        sleep(1);
         printf("Process A: Opening FIFOs\n");
        int f_write = open("fifo1", O_WRONLY);
        if(f_write < 0){
            perror("error on opening");
            exit(1);
        }

        int f_read = open("fifo2", O_RDONLY);
        if(f_read < 0){
            perror("Error on opening");
            exit(1);
        }
        int a, b, res;
        a = 5;
        b = 100;
        printf("The numbers: %d and %d \n", a, b);
        if(write(f_write, &a, sizeof(int)) < 0){
            perror("Error on sending the number a on fifo");
            exit(1);
        }
        if(write(f_write, &b, sizeof(int)) < 0){
            perror("Error on sending the number b on fifo");
            exit(1);
        }
        if(read(f_read, &res, sizeof(int)) < 0){
            perror("Error on reading the number b on fifo");
            exit(1);
        }
        printf("THE RANDOM NUMBER GENERATED IS: %d", res);
        close(f_write);
        close(f_read);
        exit(0);
    }else{
        int f2 = fork();
        if(f2 < 0){
            perror("Error on creating the first child");
            exit(1);
        }
        else if(f2 == 0){
            int f_read = open("fifo1", O_RDONLY);
            int f_write = open("fifo2", O_WRONLY);
            int a, b, res;
            if(read(f_read, &a, sizeof(int)) < 0){
                perror("Error on reading the number a");
                exit(1);
            }
            if(read(f_read, &b, sizeof(int)) < 0){
                perror("Error on reading the number b");
                exit(1);
            }
            printf("The 2 numbers received are: %d and %d \n", a, b);
            srand(time(NULL));
            res = a + rand() % (b-a+1);
            printf("THE RANDOM NUMBER IS: %d\n", res);
            if(write(f_write, &res, sizeof(int)) < 0){
                perror("Error on writing the result generated");
                exit(1);
            }
            close(f_read);
            close(f_write);
            exit(0);
        }
        else{
            //ne aflam din nou in parinte
            printf("Parent: Waiting for child processes to complete\n");
            wait(NULL);
            wait(NULL);
            unlink("fifo1");
            unlink("fifo2");


        }
    }


    return 0;
}
