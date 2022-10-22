#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double monteCarloMethod(long long int times) {
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
    return (4.0 * (double)inCircle /(double)times);
}

int main(int argc, char* argv[]) {
    int numThread = atoi(argv[1]);
    long long int times = (long long int)atoi(argv[2]);

    printf("Round: %d, Times: %lld\n", numThread, times);
    printf("PI: %f\n",monteCarloMethod(times));
}