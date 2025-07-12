#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
//Write a program that creates a child process. The two communicate through a pipe. The parent reads a string with >25 characters and sends it to the child, which removes 1 vowel and sends it to the parent, which removes the first and the last character and sends it to the child back which removes again a vowel and sends it back .... and so on untill the string contains 3 or less characters.

//Print the intermediary results and consider the initial string does not contain spaces or tabs, but only alphanumeric characters. You can use strstr() function.
//

int main(int argc, char *argv[]){

    int p[2];
    //creare pipe uri

    int p1[2];
    if(pipe(p) < 0 || pipe(p1) < 0){
        perror("ERROR ON CREATING THE PIPES");
        exit(1);
    }
    int f1 = fork();
    if(f1 < 0){
        perror("ERROR ON CREATING THE CHILD");
        exit(1);
    }
    else if(f1 == 0){
        //suntem in procesul copil
        close(p[1]);
        close(p1[0]);
        char received_string[100];
        int no_of_bytes = read(p[0], received_string, sizeof(received_string));
        if(no_of_bytes < 0){
            perror("Error on reading the initial string");
            exit(1);
        }
        received_string[bytes_read] = '\0';
        printf("Child received: %s\0", received_string);









    }
    else{
    //suntem in procesul parinte;
    char string[100];
    printf("Enter a string: \n");
    fgets(string, sizeof(string), stdin);
    close(p[0]);
    close(p1[1]);
    size_t len = strlen(string);
    if(len > 0 && string[len-1] == '\n'){
        string[len-1] = '\0';
        len--;
    }

    if(write(p[1], string, len) < 0){
        perror("Error on writing the string");
        exit(1);
    }

    char received_string;
    int no_of_bytes = read(p1[0], received_string, sizeof(received_string));
    if(no_of_bytes < 0){
        perror("Error on reading from pipe");
        exit(1);
    }

    received_String[bytes_read] = '\0';

    }
    return 0;
}
