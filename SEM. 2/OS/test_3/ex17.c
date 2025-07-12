//Scrieti un program C care citeste de la tastatura un numar N si creeaza 2 thread-uri. Unul dintre thread-uri va genera un numar par si il va insera intr-un thread primit ca parametru. Celalalt thread va genera un numar impar si il va insera in acelasi sir de numere primit ca parametru. Implementati un mecanism de sincronizare intre cele 2 thread-uri astfel incat alterneaza in inserarea de numere in sir, pana cand sirul contine N numere.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
typedef struct{
    int idx;
    int *contor;
    pthread_mutex_t *mtx;
    pthread_cond_t *cond;
    int *flag; //0 - pt pare si 1 - impare
    int *a;
    int *elem;
}data;

void* f(void* args){
    data *d = ((data*)args);
    while(1){
        pthread_mutex_lock(d->mtx);
        while(*(d->flag) != 1){
            pthread_cond_wait(d->cond, d->mtx);
        }
        printf("IMPAR: %d - %d\n", *(d->contor), *(d->elem));
        int np = *(d->contor);
        int ne = *(d->elem);
        if(np >= ne){
            printf("aici");
            pthread_cond_broadcast(d->cond);
             pthread_mutex_unlock(d->mtx);
            return NULL;

        }else printf("uite\n");
        int n1 = random()%1000;
        n1 = n1*2+1;
        printf("generated number from IMPAR is: %d\n", n1 );
        if(n1 % 2 == 1){
            d->a[*(d->contor)] = n1;
            *(d->contor) += 1;
            *(d->flag) = 0;
            pthread_cond_signal(d->cond);
            pthread_mutex_unlock(d->mtx);

        }
        pthread_cond_signal(d->cond);
        pthread_mutex_unlock(d->mtx);

    }
    return NULL;
}

void* g(void *args){
    data *d = (data*)args;
    while(1){
        pthread_mutex_lock(d->mtx);
        while(*(d->flag) != 0){
            pthread_cond_wait(d->cond, d->mtx);
        }
        printf("PAR: %d - %d\n", *(d->contor), *(d->elem));
        if(*(d->contor) >= *(d->elem)){
            printf("aici");
            pthread_mutex_unlock(d->mtx);
            pthread_cond_broadcast(d->cond);
            return NULL;
        }else printf("uite\n");
        int n1 = random()%1000;
        n1 = n1*2;
        printf("generated number from PAR is: %d\n", n1 );
        if(n1 % 2 == 0){
            d->a[*(d->contor)] = n1;
            *(d->contor) += 1;
            *(d->flag) = 1;
            pthread_cond_signal(d->cond);
            pthread_mutex_unlock(d->mtx);

        }
        pthread_cond_signal(d->cond);
        pthread_mutex_unlock(d->mtx);



    }
    return NULL;
}
int main(int argc, char *argv[]){
    int n, i;
    printf("Please type a value for n: \n");
    scanf("%d", &n);
    pthread_t *T = malloc(sizeof(pthread_t)*2);
    int *a = malloc(sizeof(int)*n);
    int *poz = malloc(sizeof(int));
    *poz = 0;
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(cond, NULL);
    int *flag = malloc(sizeof(int));
    *flag = 0; //incepem cu par
    data *arg = malloc(sizeof(data)*2);
    int *contor = malloc(sizeof(int));
    *contor = 0;
    int *elem = malloc(sizeof(int));
    *elem = n;
    arg[0].idx = 0;
    arg[0].contor = contor;
    arg[0].mtx = mtx;
    arg[0].cond = cond;
    arg[0].flag = flag;
    arg[0].a = a;
    arg[0].elem = elem;
        if(0 != pthread_create(&T[0], NULL, f, &arg[0]))
        {
            perror("error on creating one of the threads");

        }
    arg[1].idx = 1;
    arg[1].contor = contor;
    arg[1].mtx = mtx;
    arg[1].cond = cond;
    arg[1].flag = flag;
    arg[1].a = a;
    arg[1].elem = elem;
    if(0 != pthread_create(&T[1], NULL, g, &arg[1])){
        perror("error on creating one of the threads");
    }

    for(i = 0; i < 2; i++){
        pthread_join(T[i], NULL);
    }
    for(i = 0; i < n; i++){
        printf("%d  ",a[i]);
    }
    free(arg);
    free(flag);
    free(cond);
    free(mtx);
    free(poz);
    free(a);
    free(T);
    return 0;
}
