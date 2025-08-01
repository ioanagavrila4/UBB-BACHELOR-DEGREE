//Scrieti un program C care creeaza n procese fiu. Fiecare proces fiu va afisa propriul PID si PID-ul procesului parinte, iar procesul parinte va afisa propriul PID si PID-urile tuturor proceselor sale fiu.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		perror("Please provide exactly one argument");
		exit(1);
}
	int n = atoi(argv[1]);
	for(int i = 1; i <= n; i++){
		int f = fork();
		if(-1 == f){
			perror("Error on fork");

		}else if(0==f){
			printf("Child process %d - PID: %d - PPID: %d\n", i, getpid(), getppid());
			exit(0);
		} else{
			printf("Parent %d - Child: %d\n", getpid(), f);
		}
}
	for(int i = 1; i <= n;i++){
		wait(NULL);
}


	return 0;
}

