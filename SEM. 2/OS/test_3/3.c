#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//5. Write a program that computes the sum of the elements of a matix using threads. Try to come up with a most efficient solution.
typedef struct{
    int idx;
    pthread_mutex_t *mtx;
}data;
int sum_matrix;
int matrix[5][5];
int copy[5][5];
void* f(void* args){
    data p =*((data*)args);
    for(int j = 0; j < 5; j++){
        for(int k = 0; k < 5; k++){
            if(copy[j][k] == 0){
                pthread_mutex_lock(&p.mtx);
                sum_matrix = sum_matrix+matrix[j][k];
                copy[j][k] = 1;
                pthread_mutex_unlock(&p.mtx);
            }
        }

    }

    return NULL;
}
int main(int argc, char *argv[]){
    //schelet thread-uri
    int n = 10;
    for(int j = 0; j < 5; j++){
        for(int k = 0; k < 5; k++){
            matrix[j][k] = (j+k)*2;
            printf("%d ", matrix[j][k]);
        }
        printf("\n");
    }
    pthread_t *T = malloc(sizeof(pthread_t)*n);
    data *arg = malloc(sizeof(data)*10);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    for(int i = 0; i < 10; i++){
        arg[i].idx = i;
        arg[i].mtx = mtx;
        if(0 != pthread_create(&T[i], NULL, f, &arg[i])){
            perror("error on creating the threads");
        }
    }

    for(int i = 0; i < 10; i++){
        pthread_join(T[i], NULL);
    }

    printf("The sum for the matrix is: %d\n", sum_matrix);
    pthread_mutex_destroy(mtx);
    free(mtx);
    free(T);
    free(arg);
    return 0;
}
