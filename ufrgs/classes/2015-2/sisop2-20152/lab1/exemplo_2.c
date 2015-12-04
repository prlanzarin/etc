#include <stdio.h>
#include <pthread.h>

int g;

void *do_it_1(void *arg) {
    int i, n = *(int *) arg, *ret;

    ret = (int *) malloc(sizeof(int));
    for(i = 0; i < n; i++)
        g = i;
    *ret = 10;
    pthread_exit(ret);
}

void *do_it_2(void *arg) {
    int i, n = *(int *) arg, *ret;

    ret = (int *) malloc(sizeof(int));
    for(i = 0; i < n; i++)
        printf("%d\n", g);
    *ret = 20;
    pthread_exit(ret);
}

int main( int argc, char **argv) {
    pthread_t th1, th2;
    int n = 10, *res;

    pthread_create(&th1, NULL, do_it_1, &n);
    pthread_create(&th2, NULL, do_it_2, &n);
    pthread_join(th1, (void **) &res);
    printf("t1 res: %d\n", *res);
    pthread_join(th2, (void **) &res);
    printf("t2 res: %d\n", *res);
	
    printf("acabando...\n");
    exit(0);
}
