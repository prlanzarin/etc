#define MAX_THREADS 4
#define SIZE 960

#include <pthread.h>
#include <stdlib.h>

typedef struct {
	char* img1;
	char* img2;
	char* imgRes;
	int linhaInicio;
	int colunaInicio;
	int linhas;
	int colunas;
	int largura;
} mediaMatrizParam; 

void *mediaMatriz(void *arg) {
	mediaMatrizParam* p = (mediaMatrizParam*)arg;
	int linhaInicio = p->linhaInicio;
	int colunaInicio = p->colunaInicio;
	char* img1 = p->img1;
	char* img2 = p->img2;
	char* imgRes = p->imgRes;
	int largura = p->largura;
	int i,j;
	for(i = 0; i < p->linhas; i++) {
		for(j = 0; j < p->colunas; ++j) {
			(imgRes)[(linhaInicio+i)*largura + colunaInicio+j] = ((img1)[(linhaInicio+i)*largura + colunaInicio+j] + (img2)[(linhaInicio+i)*largura + colunaInicio+j])/2;
		}
	}
}

int main() {
	char img1[SIZE][SIZE], img2[SIZE][SIZE], img3[SIZE][SIZE];
	
	pthread_t child[MAX_THREADS];
	int nthreads = MAX_THREADS;
	int i;

	/* Run */
	for (i = 0; i < nthreads; i++) {
		mediaMatrizParam* par = (mediaMatrizParam*)malloc(sizeof(mediaMatrizParam));
		par->img1 = (char*)img1;
		par->img2 = (char*)img2;
		par->imgRes = (char*)img3;
		par->linhaInicio = (SIZE/nthreads) * i;
		par->colunaInicio = (SIZE/nthreads) * i;
		par->linhas = SIZE/nthreads;
		par->colunas = SIZE/nthreads;
		par->largura = SIZE;
		pthread_create(&child[i], NULL, mediaMatriz, par);
	}

	for (i = 1; i < nthreads; i++) {
		pthread_join(child[i], NULL);
	}
	return 0;

}
