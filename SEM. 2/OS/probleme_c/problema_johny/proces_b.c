#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char*argv[]){
    char *fifo1 = "./fifo1";
    char *fifo2 = "./fifo2";
    int f_read = open(fifo1, O_RDONLY);
    int f_write = open(fifo2, O_WRONLY);
    char received[100];
    int n;
    while(1){
        if(read(f_read, &n, sizeof(int)) < 0){
            perror("error");
            exit(1);
        }
        if(read(f_read, received, n*sizeof(char)) < 0){
            perror("error");
            exit(1);
        }
        int s = 0;
        for(int i = 0; i < n; i++){
            if(received[i] >= 'A' && received[i] <= 'Z'){
                s++;
            }
        }
        if(write(f_write, &s, sizeof(int)) < 0){
            perror("error");
            exit(1);
        }
    }
    close(f_write);
    close(f_read);

    return 0;
}
