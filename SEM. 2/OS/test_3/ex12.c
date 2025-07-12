#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
//Scrieti un program C care citeste o matrice de intregi dintr-un fisier. Programul creeaza un numar de thread-uri egal cu numarul de randuri in matrice, iar fiecare thread calculeaza suma numerelor de pe un rand. Procesul principal asteapta ca thread-urile sa isi incheie executia si apoi afiseaza sumele.
//
int a[100][100], fr[10];
typedef struct{
    int idx;
    int suma;

}data;
void* f(void* args){
    data *d = (data*)args;
    for(int i = 0; i < 10; i++){
        d->suma += a[d->idx][i];
    }
    return NULL;
}
int main(int argc, char* argv[]){
    int sume[100];
    pthread_t *T = malloc(sizeof(pthread_t)*10);
    data *arg = malloc(sizeof(data)*10);
    FILE fd
    for(int i = 0; i < 10; i++){
        for(int j = 0; j <= 9; j++){
            a[i][j] = i+j*8+10;
        }
    }

    for(int i = 0; i < 10; i++){
        arg[i].idx = i;
        if(0!= pthread_create(&T[i], NULL, f, &arg[i])){
            perror("error on creating the thread");
        }



    }
    for(int i = 0; i < 10; i++){
        pthread_join(T[i], NULL);
        printf("The sum: %d\n", arg[i].suma);
    }
    free(T);
    free(arg);

    return 0;
}
