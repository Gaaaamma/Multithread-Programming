#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

double inCircle = 0.0;
long long int times;
long long int range;
pthread_mutex_t mutex;
double monteCarloMethod() {
    long long int inCircle = 0;
    unsigned int seed = time(NULL);
    for (long long int i = 0; i < times; i++) {
        double xSeat = (double)rand_r(&seed) / RAND_MAX;
        double ySeat = (double)rand_r(&seed) / RAND_MAX;
        if (xSeat * xSeat + ySeat * ySeat < 1) {
            // in the circle
            inCircle ++;
        }
    }
    printf("Incircle: %lld\n", inCircle);
    // return the estimate PI
    return (4.0 * inCircle /times);
}

void* threadMonteCarloMethod(void *tid) {
    int localMonteCarlo = 0;
    unsigned int seed = time(NULL) + *(int*)tid;
    for (long long int i = 0; i < range; i++) {
        double xSeat = (double)rand_r(&seed) / RAND_MAX;
        double ySeat = (double)rand_r(&seed) / RAND_MAX;
        if (xSeat * xSeat + ySeat * ySeat < 1) {
            // in the circle
            localMonteCarlo ++;
        }
    }
    printf("Local Monte Carlo Method: %d\n", localMonteCarlo);
    printf("My PID: %d\n", *(int *)tid);

    // add the result to global variable inCircle;
    pthread_mutex_lock(&mutex);
    inCircle += localMonteCarlo;
    pthread_mutex_unlock(&mutex);
    return 0;
}

int main(int argc, char* argv[]) {
    int numThread = atoi(argv[1]);
    times= (long long int)atoi(argv[2]);
    range = times/numThread;
    pthread_mutex_init(&mutex, 0);
    int srandList[numThread];
    for(int i=0; i<numThread; i++){
        srandList[i] = i;
    }

    // Create threads
    pthread_t threadList[numThread];
    for(int i=0; i<numThread; i++){
        
        if(pthread_create(&threadList[i],NULL, threadMonteCarloMethod, &srandList[i]) !=0){
            perror("pthread_creat() failed\n");
            return 1;
        }
    }

    printf("Round: %d, Times: %lld, Range: %lld\n", numThread, times, range);

    // Wait for thread done
    for(int i=0; i<numThread; i++){
        pthread_join(threadList[i],NULL);
    }

    // Show the result
    printf("PI: %f\n", 4.0 * inCircle / times);
    pthread_mutex_destroy(&mutex);
    return 0;
}