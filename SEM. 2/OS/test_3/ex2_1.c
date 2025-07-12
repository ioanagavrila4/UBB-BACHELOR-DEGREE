#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
FILE *ptr;
int a[1000], prime[100];
int prim(int n){
    if(n < 2) return 0;
    if(n > 2 && n% 2 == 0) return 0;
    for(int d = 3; d < n; d++){
        if(n%d == 0) return 0;
    }
    return 1;

}
typedef struct{
    int numar;
    int elem;
    int frecventa;
    pthread_mutex_t *mtx;
    int afisat;

}data;
int M;

int prelucrare_toate = 0, media =0;
int contor_p;

void* f(void* args){
    data *p = (data*)args;
    int  calculat = 0;
    p->frecventa = 0;
        if(!calculat){
            for(int i = 0; i < p->elem; i++){
                if(a[i] == p->numar){
                    p->frecventa = p->frecventa+1;
                }                }
    pthread_mutex_lock(p->mtx);
                contor_p++;
               pthread_mutex_unlock(p->mtx);


            calculat = 1;


        }
        pthread_mutex_lock(p->mtx);
        M = M + p->frecventa;
        if(contor_p == 25 && media == 0){
            M = M/p->elem;
            printf("The media is: %d\n", M);
            media=1;


        }
        pthread_mutex_unlock(p->mtx);
        if(p->afisat == 0 && media && p->frecventa <= M && p->frecventa >= M-10){
            printf("THE NUMBER %d: frecventa %d\n", p->numar, p->frecventa);

            p->afisat = 1;
        }





    return NULL;
}
int main(int argc, char *argv[]){

    int n = 0;
    int contor = 0;
    for(int j = 1; j <= 100; j++){
        if(prim(j)){

            prime[contor] = j;
            contor++;
        }
    }
    printf("Please type the number n: \n");
    scanf("%d", &n);

    ptr = fopen("numere.txt","r");
    for(int i = 0; i < n; i++){
        int nr;

        fscanf(ptr, "%d", &nr);
        a[i] = nr;
    }

    pthread_t *T = malloc(sizeof(pthread_t)*contor);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    data *arg = malloc(sizeof(data)*contor);
    for(int i = 0; i < contor; i++){
            arg[i].numar = prime[i];
            arg[i].mtx = mtx;
            arg[i].elem = n;
            arg[i].frecventa = 0;
            arg[i].afisat = 0;
            if(0!=pthread_create(&T[i],NULL, f, &arg[i] )){
                perror("error on creating");

            }
    }

    for(int i = 0; i< contor; i++){
        pthread_join(T[i], NULL);

    }




    free(mtx);
    free(T);

    return 0;
}
