
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//Scrieti un program care primeste la linia de comanda siruri de caractere. Pentru fiecare sir de caractere programul creeaza un thread care calculeaza numarul de cifre, litere si caractere speciale (orice nu e litera sau cifra). Programul principal asteapta ca thread-urile sa isi incheie executia si afiseaza rezultatele totale (numarul total de cifre, litere si caractere speciale din toate argumentele primite la linia de comanda) si apoi se incheie. Folositi sincronizare eficienta. Nu folositi variabile globale.

typedef struct{
    int idx;
    char input[100];
    int *c, *l, *s;
    pthread_mutex_t *mtx;


}data;

void* f(void* args){
    data *p = (data*)args;
    return NULL;
}
int main(int argc, char *argv[]){
    if(argc < 2){
        perror("invalid number of arguments");
        exit(1);
    }

    int n = argc;
    pthread_t *T = malloc(sizeof(pthread_t)*n);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    data *arg = malloc(sizeof(data)*n);
    int *l = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int *s = malloc(sizeof(int));
    *l = *c = *s = 0;
    for(int i = 0; i < n; i++){
        arg[i].idx = i;
        arg[i].mtx = mtx;
        arg[i].c = c;
        arg[i].l = l;
        arg[i].s = s;
        strcpy(arg[i].input, argv[i+1]);
        if(pthread_create(&T[i], NULL, f, &arg[i]) != 0)
    {
        perror("eroare on cre`tin the threads");
    }
    }
for(int i = 0; i < n; i++){
        if(pthread_join(T[i], NULL) != 0){
            perror("error joining thread");
            exit(1);
        }
    }
    free(l);
    free(c);
    free(s);
    free(T);
    free(mtx);
    return 0;
}
