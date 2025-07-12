//Un thread poate sa apeleze metode ale parintelui(poate sa se uite pe heap si sa extraga chestii puse de parinte) - in materie de memorie, thread ul are mult mai mult acces la memorie.
//p - vine de la posix - defineste niste metode de creare, asteptare si mai multe moduri de sincronizare
//toate incep cu pthread - _create - 4 argumente => primul e numele, al doilea - daca il pui NULL, ia valori implicite, al treilea
//un thread isi incepe executia de la f-practic ; cand porneste threadul are nevoie de un entry point void*(param void*)
//void * - adresa care te duce in memorie la sizeof(void) - numar necunoscut de octeti  - poate fi incadrat oricat acolo
//* - pointer
//parametrii de out mereu is trimisi prin referinta
//al doilea param - atribute gen prioritate(maxima poate - nu poate fi intrerupt de alte thread uri) - structura de caracteristici ale thread uluii
//o operatie poate fi compusa din unul sau mai multi pasi - in opeartiile atomice ori se executa tot dintr un foc, ori nimic
//mutex - totemul vorbirii - vine de la mutual exclusion - cine are mutexul ae voie sa execute ceva si restul asteapta
//pthread_mutex m - pthread_mutex_init(mutex, atributele mutex pentru creare = NULL pt default) - cum se foloseste? pthread_mutex_lock/unlock
//resursa critica este o resursa care este accesata de cel mult un thread si cel putin un thread vrea sa acceseze resursa - toate liniile de cod care vor sa acceseze aceea linie de cod se numesc zone critice - numa liniile critice trebuie protejate de mutex
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
typedef struct{
    char idx;
    int k;
}data;
int*a;
char **b;
void *f(void *arg){
    banana b = *((banana*) arg);
    printf("This thread has received a %s of size  %d\n", b.arr, b.k);
    int *ret=malloc(sizeof(int));
    *ret=0;
    //main(a, b); // bucla infinita
    return ret;
}
int main(int argc, char *argv[]){
    pthread_t ph;
    banana b;
    strcpy(b.arr, "banana");
    b.k = 3;
    int *i;
    pthread_create(&ph, NULL, f, &b); //b e arg ul din f
    //void ** - reprezinta
    //chestiile facute cu malloc rezida in heap
    pthread_join(ph,(void **) &i); //wit parctic
    printf("From the thread he comes: %d", *i);
    free(i);
    return 0;
}
