#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
int main(int argc, char *argv[]){
    char el[100];
    char *fifo1 = "./fifo1";
    if(mkfifo(fifo1, 0600) < 0){
        perror("Error on creating your first fifo");
        exit(1);
    }
    char *fifo2 = "./fifo2";
    if(mkfifo(fifo2, 0600) < 0){
        perror("Error on creating the second fifo!");
        exit(1);
    }
    int f_write = open(fifo1, O_WRONLY);
    int f_read = open(fifo2, O_RDONLY);

    while(1)
    {
        printf("Please enter a chracter: ");
        fgets(el,20,stdin );
        printf("Your string: %s\n", el);
        if(strcmp(el, "x\n") == 0){

            break;
        }
        int len = strlen(el);
        if(write(f_write, &len, sizeof(int)) < 0){
            perror("error");
            exit(1);
        }
        if(el[len-1] == '\n'){
            el[len-1] = '\0';
        }
        if(write(f_write, el, sizeof(char)*(len-1)) < 0){
            perror("Error on writing the strings!");
            exit(1);
        }
        int s;
        if(read(f_read, &s, sizeof(int)) < 0){
            perror("Error on reading the result!");
            exit(1);
        }

        printf("The result is: %d\n", s);

    }
    close(f_read);
    close(f_write);
    return 0;
}
