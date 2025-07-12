#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
    int f_write = open("fifo1", O_WRONLY);
    if(f_write < 0){
        perror("ERROR ON OPENING THE FIFO");
        exit(1);
    }
    int f_read = open("fifo2", O_RDONLY);
    if(f_read < 0){
        perror("ERROR ON OPENING THE FIFO");
        exit(1);
    }
    char string[100] = "";
    while(strcmp(string, "000")){
        fgets(string, sizeof(string), stdin);
        size_t len = strlen(string);
        if(len > 0 && string[len-1] == '\n'){
            string[len-1]='\0';
            len--;
        }
        printf("%s\n", string);

    }

    return 0;
}
