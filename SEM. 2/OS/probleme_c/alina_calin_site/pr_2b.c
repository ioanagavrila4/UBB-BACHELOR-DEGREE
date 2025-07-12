#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Create FIFOs
    if(mkfifo("fifo1", 0666) < 0) {
        perror("Error on creating fifo1");
        exit(1);
    }
    if(mkfifo("fifo2", 0666) < 0) {
        perror("Error on creating fifo2");
        exit(1);
    }

    int f1 = fork();
    if(f1 < 0) {
        perror("Error on creating the first child");
        exit(1);
    } else if(f1 == 0) {
        // Process A
        sleep(1); // Give Process B time to start

        printf("Process A: Opening FIFOs\n");
        int f_write = open("fifo1", O_WRONLY);
        if(f_write < 0) {
            perror("Process A: Error opening fifo1 for writing");
            exit(1);
        }

        int f_read = open("fifo2", O_RDONLY);
        if(f_read < 0) {
            perror("Process A: Error opening fifo2 for reading");
            exit(1);
        }

        int a = 5;
        int b = 100;
        printf("Process A: The numbers: %d and %d\n", a, b);

        if(write(f_write, &a, sizeof(int)) < 0) {
            perror("Process A: Error on sending the number a on fifo");
            exit(1);
        }
        printf("Process A: Sent number a\n");

        if(write(f_write, &b, sizeof(int)) < 0) {
            perror("Process A: Error on sending the number b on fifo");
            exit(1);
        }
        printf("Process A: Sent number b\n");

        int res;
        printf("Process A: Waiting for result...\n");
        if(read(f_read, &res, sizeof(int)) < 0) {
            perror("Process A: Error on reading the result from fifo");
            exit(1);
        }

        printf("Process A: THE RANDOM NUMBER GENERATED IS: %d\n", res);

        close(f_write);
        close(f_read);
        exit(0);
    } else {
        int f2 = fork();
        if(f2 < 0) {
            perror("Error on creating the second child");
            exit(1);
        } else if(f2 == 0) {
            // Process B
            printf("Process B: Opening FIFOs\n");
            int f_read = open("fifo1", O_RDONLY);
            if(f_read < 0) {
                perror("Process B: Error opening fifo1 for reading");
                exit(1);
            }

            int f_write = open("fifo2", O_WRONLY);
            if(f_write < 0) {
                perror("Process B: Error opening fifo2 for writing");
                exit(1);
            }

            int a, b;
            printf("Process B: Waiting for numbers...\n");

            if(read(f_read, &a, sizeof(int)) < 0) {
                perror("Process B: Error on reading the number a");
                exit(1);
            }
            printf("Process B: Received number a: %d\n", a);

            if(read(f_read, &b, sizeof(int)) < 0) {
                perror("Process B: Error on reading the number b");
                exit(1);
            }
            printf("Process B: Received number b: %d\n", b);

            printf("Process B: The 2 numbers received are: %d and %d\n", a, b);

            srand(time(NULL));
            int res = a + rand() % (b - a + 1);
            printf("Process B: THE RANDOM NUMBER IS: %d\n", res);

            if(write(f_write, &res, sizeof(int)) < 0) {
                perror("Process B: Error on writing the result generated");
                exit(1);
            }
            printf("Process B: Sent result back to Process A\n");

            close(f_read);
            close(f_write);
            exit(0);
        } else {
            // Parent process
            printf("Parent: Waiting for child processes to complete\n");
            wait(NULL);
            wait(NULL);
            printf("Parent: Child processes completed, cleaning up FIFOs\n");

            unlink("fifo1");
            unlink("fifo2");
        }
    }

    return 0;
}
