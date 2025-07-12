#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int a[1000];
int elem;
typedef struct{
    int idx;
    pthread_cond_t *cond;
    pthread_mutex_t *mtx;
    int *flag; //1 - sortat; 0 - nesortat
}data;
void *g(void* args){
    data *p = (data*)args;
pthread_mutex_lock(p->mtx);
    while(*p->flag != 1){
        pthread_cond_wait(p->cond, p->mtx);

    }
    pthread_mutex_unlock(p->mtx);
    int i;
    for(i = 0; i < elem; i++){
        printf("%3d ", a[i]);
    }
    return NULL;
}
void *f(void *args){
    data *p = (data*)args;
    int i;
    while(1){
        pthread_mutex_lock(p->mtx);
        int sortat = 1;
        for(i = 0; i < elem-1; i++){
            if(a[i] > a[i+1]){
                sortat = 0;
            }
        }
        if(sortat == 1){
            *(p->flag) = 1;
            pthread_cond_signal(p->cond);
            pthread_mutex_unlock(p->mtx);
            return NULL;
        }
        i = random()% elem;
        int j = random()% elem;
        if(i < j && a[i] > a[j]){
            int aux = a[i];
            a[i] = a[j];
            a[j] = aux;
        }
        else{
            if(i > j && a[i] < a[j]){
                int aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
        }

        pthread_mutex_unlock(p->mtx);


    }
    return NULL;
}
int main(int argc, char *argv[]){
    int n;
    //citire n
    printf("Please type a value for n: \n");
    scanf("%d", &n);
    elem = n;
    //generare sir
    int i;
    printf("aici\n");
    for(i = 0; i < n; i++){
        a[i] = random()%1000;
        printf("%d ", a[i]);
    }
    printf("aici\n");
    //n+1 thread-uri
    pthread_t *T = malloc(sizeof(pthread_t)*(n+1));
    pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(cond, NULL);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    data *arg = malloc(sizeof(data)*(n+1));
    int *flag = malloc(sizeof(int));
    *flag = 0;
    for(i = 0; i < n; i++){
        arg[i].idx = i;
        arg[i].cond = cond;
        arg[i].mtx = mtx;
        arg[i].flag = flag;
        if(pthread_create(&T[i], NULL, f, &arg[i]) != 0){
            perror("error on creating the threads\n");
        }

    }
    arg[n].idx = n;
    arg[n].cond = cond;
    arg[n].mtx = mtx;
    arg[n].flag = flag;
    if(pthread_create(&T[i], NULL, g, &arg[n]) != 0){
        perror("error on creating the last thread\n");


    }

    for(i = 0; i <= n; i++){
        pthread_join(T[i], NULL);

    }
    free(flag);
    free(arg);
    free(mtx);
    free(cond);
    free(T);
    return 0;
}
