#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *test_routine (void *arg) {
    double *value;
    value = (double*)malloc(sizeof(double));
    *value = 100.0;
    pthread_exit(value);
    /*** fix me ***/
}

int main( int argc, char **argv) {
    pthread_t thr;
    double *res;
    int status;

    status = pthread_create(&thr, NULL, test_routine, NULL);
    if (status != 0)
        exit(1);

    status = pthread_join (thr, (void **) &res);
    if (status != 0)
        exit(1);

    printf("resultado retornado: %.2f\n", *res);
    free(res);
}
