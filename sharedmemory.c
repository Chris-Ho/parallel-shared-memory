#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t barrier;
double array;
int dimensions;
double precision;  
int noThreads;

void calc(int i){
    bool loop = true;
    while loop = true{
        //stops data race condition on 'loop'
        pthread_barrier_wait(&barrier);
        loop = false;
        //stops data race condition on 'loop' (if one thread sets loop to true, then another thread sets back to false, then while loop won't run)
        pthread_barrier_wait(&barrier);
        //vulnerable to races?
        //doesn't change so no
        int squares = (dimensions) * (dimensions);
        int chunks = squares/noThreads;
        //vulnerable to races?
        //hope not, but if so -> make a duplicate copy of array and use that instead
        values = malloc(sizeof(int) * chunks);
        if (values == NULL){ 
            printf("Fail");
            exit(EXIT_FAILURE);
        }
        //might clash in multiple threads
        int counter = 0;

        //loop variables clash? if yes, then use primitives to stop? kind of pointless since its all sequential?
        for (int x = chunks*i; x<chunks*i+chunks; x++){
            if(x%dimensions <= 1 && x > dimensions-1 && x < dimensions * (dimensions-1)){
                //new value in array = (left neighbour + right neighbour + up neighbour + down neighbour) / 4
                values[x - chunks*i] = ((array[x-1] + array[x+1] + array[x-dimensions+1] + array[x+dimensions+1])/4);
            }
            else{
                values[x - chunks*i] = array[x];
            }
            counter++;
        }
        //wait to update --> prevent data race on updating array
        pthread_barrier_wait(&barrier);
        
        for (int j = chunks*j; j<chunks*j+chunks; j++){
            if(array[j] - values[j-(chunks*j)] > precision){
                loop = true; 
            }
            array[j] = values[j-(chunks*j)]
        }
    }
}

void main (double inputArray, int arrayDimension, int noThreads, double inputPrecision){
    array = inputArray;
    dimensions = arrayDimension;
    precision = inputPrecision;
    thread = malloc(sizeof(pthread_t) * noThreads);
    if(thread == NULL){
        printf("Fail");
        exit(EXIT_FAILURE);
    }

    for(i =0; i<noThreads;i++){
        if(pthread_create(&thread[i], NULL, void *(calc), i)!=0){
            printf("Fail");
            exit(EXIT_FAILURE);
        }
    }
    pthread_barrier_init(&barrier, NULL, noThreads);
    //stops threads from exiting before completion.
    pthread_join(); 

}