#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
/*Write a program that creates 4 threads and had 3 global variables v5, v2, v3.
Each thread generates a random number and:
- if the number is multiple of 2 increments v2
- if the number is multiple of 3, increments v3
- if the number is multiple of 5 increments v5

The number can be a multiple of more numbers (ex. for 10 we will increment both V2 and V5)

Threads print the generated numbers and stop when 30 numbers have been generated
*/
int v5=0, v2=0, v3=0;
int contor = 0;
typedef struct{
    int idx;
    pthread_mutex_t *m;

}data;

void *func(void *arg){
    data d = *((data*) arg);
    while(contor < 30){
        pthread_mutex_lock(d.m);
        int random_n = rand()%1991+1;
        contor++;
        if(random_n%2 == 0){
            v2++;
        }
        if(random_n%3==0){
            v3++;
        }
        if(random_n%5 == 0){
            v5++;
        }
        printf("THE THREAD %d : %d\n", d.idx, random_n);

        pthread_mutex_unlock(d.m);
    }
    return 0;

}
int main(){
    int i;
    pthread_mutex_t *m=malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(m, NULL);
    data *args = malloc(sizeof(data)*3);
    pthread_t *T = malloc(sizeof(pthread_t)*3);

    for(i = 0; i< 2; i++){
        args[i].idx = i;
        args[i].m = m;
        if(pthread_create(&T[i], NULL, func, (void*)&args[i])){
            perror("error");
            free(args);
            free(T);
            free(m);
            exit(1);
        }

    }
    for(i = 0; i < 3; i++){
        pthread_join(T[i], NULL);
    }


    wait(0);
    printf("V2 = %d\nV3 = %d\nV5 = %d\n", v2, v3, v5);
    free(args);
    free(T);
    free(m);

    return 0;
}
