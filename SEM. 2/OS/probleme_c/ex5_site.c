//Scrieti un program C care implementeaza un joc de boltz. Se creeaza exact N procese (numerotate de la 1 la N, unde N este dat) incrementeaza pe rand un numar, pornind de la 1, si il trimit unui proces "vecin". Procesul 1 porneste jocul incrementand numarul si trimitandu-l procesului 2, care il incrementeaza si il trimite procesului 3, si asa mai departe. Procesul N va trimite numarul procesului 1, si ciclul se repeta. Fiecare proces va afisa numarul inainte sa il trilita, cu exceptia cazului in care numarul contine cifra 7 sau este multiplu de 7, caz in care procesul va afisa cuvantul "boltz". Ca procesele sa isi incheie executia, implementati ca un proces sa nu afiseze "boltz" intr-o situatie in care ar trebui sa afiseze "boltz", cu o probabilitate de 1/3. In acest caz, toate procesele se vor opri.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
//prima oara facem ce stim
//functie de verificat daca un numar contine cifra 7 sau este multiplu de 7
bool contains_7(int n){
    if(n%7 == 0){
        return true;
    }
    while(n){
        if(n%10 == 7){
            return true;
        }
        n = n/10;
    }
    return false;
}



void fork_and_com(int n){
    int i;
    int pipes[n][2]//practic facem un lant de pipe uri care trebuies numerotate de la 1 la n ca sa facem comunicarea

    pid_t pids[n]; //facem un array de pid uri, pid_t e practic un tip de data din unistd

    //acum cream n pipe uri pentru comunicare
    for(i=0; i < n; i++){
        if(pipe(pipes[i]) == -1){
            perror("ERROR ON CREATING PIPES");
            exit(1);
        }
    }

    //acum cream copiii
    for(int i = 0; i< n; i++){
        pids[i] = fork();

        if(pids[i] < 0){
            perror("Fork failed");
            exit(1);
        }

        if(pids[i] == 0){
            //ne aflam in al i-lea proces copil
            int id = i+1 //numarul care o sa trebuiasca trimis
            int nr;
            int prev_pipe = (i == 0) ? (n-1) : (i - 1);
            int my_pipe = i;


        }
    }

}

int main(int argc, char *argv[]){

    if(argc < 2){
        perror("Not enough arguments!!");
        exit(1);
    }

    int n = atoi(argv[1]);
    int i = 1;

    return 0;
}
