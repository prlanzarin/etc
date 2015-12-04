#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define	TRUE 1

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *minha_funcao (void *arg) {
   int n = *(int *) arg;

   while(TRUE) {
      
      pthread_mutex_lock(&m);	   
      printf("Thread %d iniciando a SC\n ", n);
      printf("Thread %d ainda na SC\n ", n);
      sleep(rand()%5); 
      printf("Thread %d saindo da SC\n ", n);
      pthread_mutex_unlock(&m);
	   
	  sleep(rand()%5); 
   }
}

int main (int argc, char *argv[]) {
   pthread_t  thr1, thr2;
   int n1 = 1;
   int n2 = 2;

   pthread_create(&thr1, NULL, minha_funcao,(void *) &n1);
   pthread_create(&thr2, NULL, minha_funcao,(void *) &n2);

   pthread_exit(0);
}
