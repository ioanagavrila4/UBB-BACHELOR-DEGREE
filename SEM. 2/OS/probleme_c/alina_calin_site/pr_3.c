//Implement a program that creates 2 child processes A and B, which communicate using FIFO.
//Process A sends to process B a number 70>n>10; process B receives this number, subtracts 4 and sends it to process A;
//process A reads the number from B, decreases the number by 1 and sends it to B... and so on, until the number n has 1 digit.
//(Fifo created in the command line using mkfifo)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char *argv[]){
    int f1 = fork();
    if(f1 < 0){
        perror("Error on creating the first child");
        exit(1);
    }
    else if(f1 == 0){
        //ne aflam in procesul copil 1
        sleep(1);
        int a;
        printf("Please type a number: \n");
        scanf("%d", &a);
        printf("THE NUMBER: %d\n", a);
        //deschidem fifo ul deja creat
        int f_write = open("fifo2", O_WRONLY);
        int res;
        if(f_write < 0){
            perror("Error on opening the second fifo");
            exit(1);
        }
        int f_read = open("fifo1", O_RDONLY);
        if(f_read < 0){
            perror("Error on opening the fifo");
            exit(1);
        }
        if(write(f_write, &a, sizeof(int)) < 0){
            perror("Error on writing the number on fifo");
            exit(1);
        }

        if(read(f_read, &res, sizeof(int)) < 0){
            perror("Error on reading from fifo the result");
            exit(1);
        }
        res = res - 1;
        while(res > 9){
            if(write(f_write, &a, sizeof(int)) < 0){
              perror("Error on writing the number on fifo");
              exit(1);
          }
            if(read(f_read, &res, sizeof(int)) < 0){
              perror("Error on reading from fifo the result");
              exit(1);
          }
          res = res - 1;
        }
        printf("THE FINAL RESULT IS: %d\n", res);
        close(f_write);
        close(f_read);
        exit(0);
    }
    else{
        int f2 = fork();
        if(f2 < 0){
            perror("Error on creating the second child");
            exit(1);
        }
        else if(f2 == 0){
            //ne aflam in procesul copil 2
            int f_read = open("fifo2", O_RDONLY);
            if(f_read < 0){
                perror("Error on reading");
                exit(1);
            }
            int f_write = open("fifo1", O_WRONLY);
            if(f_write < 0){
                perror("Error on opening the fifo");
                exit(1);
            }
            printf("PROCES B IN LOADING...\n");
            int a, res;
            if(read(f_read, &a, sizeof(int)) < 0){
                perror("ERROR ON READING NUMBER A");
                exit(1);
            }
            printf("NUMBER A: %d\n", a);
            res = a - 4;
            if(write(f_write, &res, sizeof(int)) < 0){
                perror("Error on writing the first result");
                exit(1);
            }
            while(res > 9){
                if(read(f_read, &a, sizeof(int)) < 0){
                  perror("ERROR ON READING NUMBER A");
                  exit(1);
              }
                res = a - 4;
                if(write(f_write, &res, sizeof(int)) < 0){
                  perror("Error on writing the first result");
                  exit(1);
              }
            }
            close(f_read);
            close(f_write);
            exit(0);

        }
        else{
            wait(0);
            wait(0);
            unlink("fifo1");
            unlink("fifo2");
        }

    }

    return 0;
}
