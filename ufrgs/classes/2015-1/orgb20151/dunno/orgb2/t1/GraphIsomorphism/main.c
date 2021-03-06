#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nRows 100
#define nCols 100
#define EOG -1

void graphParser(FILE *arq, int gMIn[][nCols], int gMIn2[][nCols], int *fNodos, int *sNodos);
void graphReader(FILE *arq, int gMIn[][nCols], int *fNodos);
void graphPrinter(int gMIn[][nCols]);
int isomorphismChecker(int gMIn[][nCols], int gMIn2[][nCols], int *fNodos, int *sNodos);
int subgraphisomorphism(int gMIn[][nCols], int gMIn2[][nCols], int *sNodos, int nodos[], int dif);
int calcMatrix(int nodos[], int *sNodos, int gMIn[][nCols], int gMIn2[][nRows], int dif);
int swapcompareMatrix(int gMIn[][nCols], int gMIn2[][nCols], int nodos[], int *sNodos, int dif);
void permutation(int *sNodos, int nodos[]);
int combinationUtil(int nodos[], int comb[], int start, int end, int index, int r, int gMIn[][nCols], int gMIn2[][nCols], int auxMatrix[][nCols], int *sNodos);
int deleteNodos(int comb[], int nodos[], int gMIn[][nCols], int gMIn2[][nCols], int auxMatrix[][nCols], int r, int *sNodos);
long long int fat(long long int n);

int main()
{
    FILE *graphIn;
    FILE *saida;
    int graphMatrixIn[nRows][nCols], graphMatrixIn2[nRows][nCols], fNodos = 0, sNodos = 0, flag;
    graphParser(graphIn, graphMatrixIn, graphMatrixIn2, &fNodos, &sNodos);
    printf("   GRAFO UM: \n\n");
    graphPrinter(graphMatrixIn);
    printf("\n\n   GRAFO DOIS: \n\n");
    graphPrinter(graphMatrixIn2);
    flag = isomorphismChecker(graphMatrixIn, graphMatrixIn2, &fNodos, &sNodos);
    saida = fopen("saida.txt", "a");
    if(saida == NULL)
        printf("Erro na abertura do arquivo texto dos grafos de entrada.\n");
    else
    {
        if(flag == 1)
        {
            fprintf(saida, "%s \n", "Os grafos sao isomorfos!");
            printf("Os grafos sao isomorfos!\n");
        }
        else if (flag == 0)
        {
            fclose(saida);
            saida = fopen("saida.txt", "w");
            printf("Os grafos nao sao isomorfos!\n");
            fprintf(saida, "%s \n", "Os grafos nao sao isomorfos!");
        }
        else if (flag == 2)
        {
            fclose(saida);
            saida = fopen("saida.txt", "a");
            printf("Ha um subgrafo isomorfo ao outro!\n");
            fprintf(saida, "%s \n", "Ha um subgrafo isomorfo ao outro!");
        }

        else
        {
            fclose(saida);
            saida = fopen("saida.txt", "w");
            printf("Os grafos nao sao isomorfos e nao ha subgrafo isomorfo!\n");
            fprintf(saida, "%s \n", "Os grafos nao sao isomorfos e nao ha subgrafo isomorfo!" );
        }
    }
    fclose(saida);
    system("pause");
    return 0;
}

/* realiza o parsing de dois grafos representados por matrizes de adjac�ncia separadas por '#' */
void graphParser(FILE *arq, int gMIn[][nCols], int gMIn2[][nCols], int *fNodos, int *sNodos)
{
    arq = fopen("grafo1m3.txt", "r");
    if(arq == NULL)
        printf("Erro na abertura do arquivo texto dos grafos de entrada.\n");
    else
    {
        graphReader(arq, gMIn, fNodos);
        graphReader(arq, gMIn2, sNodos);
    }
    fclose(arq);
}

/* le a matriz no arquivo e a transfere para uma matriz na mem�ria */
void graphReader(FILE *arq, int gMIn[][nCols], int *fNodos)
{
    int i = 0, j = 0;
    char aux;
    char matrixLine[52], *token;
    aux = fgetc(arq);                           // teste para detectar se j� chegou � divis�o de matrizes '#'
    while(aux != '#' && !feof(arq))
    {
        fseek(arq,-sizeof(char), SEEK_CUR);     // se n�o chegou, retorna um caractere no stream do arquivo
        if(fgets(matrixLine, sizeof(matrixLine), arq) != NULL) // l� uma linha do arquivo
        {
            token = strtok(matrixLine," ");     // anula espa�os em branco na linha
            while(token != NULL)
            {
                if(token[0] != '\n')
                {
                    gMIn[i][j] = atoi(token);   // converte n�mero armazenado em ASCII na string token para inteiro
                    i++;
                }
                token = strtok(NULL, " ");      // continua a pegar n�meros entre espa�os at� o fim da linha
            }
            gMIn[i][j] = EOG;                   // fim da linha da matriz
            i = 0;
            j++;
            fscanf(arq, "%c", &aux);            // testa fim de matriz
        }
    }
    fseek(arq, 2*sizeof(char), SEEK_CUR);       // avan�a duas posi��es na stream para pegar pr�xima matriz
    for(i = j; i >= 0; i--)
        gMIn[i][j] = EOG;                        // preenche fim de colunas da matriz com EOG (end of graph / -1)

    i = 0;
    while(gMIn[i][0] != EOG)
        i++;                                    // conta n�mero de nodos do grafo e armazena no ponteiro fNodos
    *fNodos = i;
}

/* imprime a matriz gMIn de entrada na tela */
void graphPrinter(int gMIn[][nCols])
{
    int i = 0, j = 0;
    printf("-----------MATRIZ DE ADJACENCIA-----------\n");
    while(gMIn[i][j] != EOG)
    {
        while(gMIn[i][j] != EOG)
        {
            printf("%d ", gMIn[i][j]);
            i++;
        }
        i = 0;
        j++;
        printf("\n");
    }
}

/* checa isomorfismos entre os grafos gMIn e gMIn2 solicitados */
int isomorphismChecker(int gMIn[][nCols], int gMIn2[][nCols], int *fNodos, int *sNodos)
{
    int flag = 1, i = 0, j = 0, k = 0, l = 0, nodos[50];
    if(*fNodos != *sNodos)
    {
        //n�mero diferente de nodos

        if(*sNodos - *fNodos > 0)
        {
            flag = subgraphisomorphism(gMIn, gMIn2, sNodos, nodos, (*sNodos - *fNodos));
            if(flag == 1)
                return 2;
        }
        else
        {
            flag = subgraphisomorphism(gMIn2, gMIn, fNodos, nodos, (*fNodos - *sNodos));
            if(flag == 1)
                return 2;
        }
        //checar isomorfismo de subgrafos
    }
    else
    {
        while(flag == 1 && j <= *fNodos)
        {
            for(i = 0; i <= *fNodos; i++)
            {
                if(gMIn[i][j] == 1)
                    k++;
                if(gMIn2[i][j] == 1)
                    l++;
            }

            if(k != l) // chega se o grau dos nodos � diferente
                flag = 0;
            else j++;
        }
    }
    if(flag == 0)
        return 0;
    // se nenhum dos dois casos acima � verdadeiro, ent�o parte-se para o teste de for�a bruta
    else
    {
        flag = calcMatrix(nodos, sNodos, gMIn, gMIn2, 0);
        return flag;
    }

}

/* se um grafo for maior do que o outro, parte para o teste de subgrafos excluindo linhas da matriz atrav�s de combina��es dif a dif */
int subgraphisomorphism(int gMIn[][nCols], int gMIn2[][nCols], int *sNodos, int nodos[], int dif)
{
    int flag = 0, auxMatrix[nRows][nCols], i = 0, k = *sNodos - 1;
    while(flag != 1 && i < fat(k) && flag != -1)
    {
        int comb[dif];
        flag = combinationUtil(nodos, comb, 0, k , 0, dif, gMIn, gMIn2, auxMatrix, sNodos);
        if (flag == -1)
            return flag;
        i++;
    }
    return flag;

}
int calcMatrix(int nodos[], int *sNodos, int gMIn[][nCols], int gMIn2[][nRows], int dif)
{
    int i = 0, k = 0;
    long long int ftorial, j;
    FILE *saida;
    while(i < *sNodos) // preenche array para ordenar
    {
        nodos[i] = i+1;
        i++;
    }
    nodos[i] = -1; // fim do array
    j = *sNodos;
    k = 0;
    i = 0;
    ftorial = fat(j);

    while(k == 0 && i < ftorial) // testa fun��es at� achar um isomorfismo entre os dois grafos
    {
        k = swapcompareMatrix(gMIn, gMIn2, nodos, sNodos, dif);
        if(k == 0)
            permutation(sNodos, nodos);
        i++;
    }

    if(k == 1)
    {

        saida = fopen("saida.txt", "w");
        if(saida == NULL)
            printf("Erro na abertura do arquivo texto dos grafos de entrada.\n");
        else
        {
            fprintf(saida, "%s \n", "MAPEAMENTO ");
            for(i = 0; i < *sNodos - dif; i++)
            {
                fprintf(saida,"%d ", i+1);
                fprintf(saida,"%d \n", nodos[i]);
            }
        }
        fclose(saida);

        return k;
    }
    return k;
}
/* troca as posi��es da matrizes conforme o permutado e a compara para testar o isomorfismo */
int swapcompareMatrix(int gMIn[][nCols], int gMIn2[][nCols], int nodos[], int *sNodos, int dif)
{
    int auxMatrix2[nRows][nCols], auxMatrix[nRows][nCols], i = 0, j = 0, k = 0, flag = 1;
    memcpy(auxMatrix,gMIn2, nRows*nCols*sizeof(int));

    /* SWAPPING */
    for(i = 0; i < *sNodos; i++)  // troca todas as colunas da matriz conforme a posi��o da permuta��o
    {
        k = nodos[i] - 1;
        if(k != i)
        {
            while(j < *sNodos)
            {
                auxMatrix[i][j] = gMIn2[k][j];
                j++;
            }
            j = 0;
        }
    }
    memcpy(auxMatrix2, auxMatrix, nRows*nCols*sizeof(int));
    for(i = 0; i < *sNodos; i++) // troca as linhas da matriz conforme a posi��o na permuta��o
    {
        j = 0;
        k = nodos[i] - 1;
        if(k != i)
        {
            while(j < *sNodos)
            {
                auxMatrix[j][i] = auxMatrix2[j][k];
                j++;
            }
        }
    }
    /* COMPARING */
    i = 0;
    j = 0;
    while(gMIn[i][j] != EOG && flag == 1)
    {
        while(gMIn[i][j] != EOG && flag == 1)
        {
            if(gMIn[i][j] == auxMatrix[i][j])
                flag = 1;
            else
                flag = 0;
            j++;
        }
        j = 0;
        i++;
    }
    if(flag == 1)
        graphPrinter(auxMatrix);
    return flag;
}
/* permuta os �ndices da matriz para poder testar isomorfismo */
void permutation(int *sNodos, int nodos[])
{
    int k = 0, l = 0, i = 0, final = (*sNodos - 1);

    for(i = 0; i < *sNodos; i++)  // acha o maior l tal que i[l] > i[k]
    {
        if(nodos[i] < nodos[i+1]) // acha o menor i[k] tal que i[k] < i[k+1]
            k = i;
    }
    for(i = 0; i < *sNodos; i++)  // acha o maior l tal que i[l] > i[k]
    {
        if(nodos[i] > nodos[k])
            l = i;
    }
    i = nodos[k];
    nodos[k] = nodos[l];
    nodos[l] = i;
    while((k+1) < final)
    {
        i = nodos[k+1];
        nodos[k+1] = nodos[final];
        nodos[final] = i;
        k++;
        final--;
    }
}

long long int fat (long long int n)
{
// Funcao que devolve o fatorial de n (assume que n >= 0)
    long i, fat;
    fat = 1;
    for (i = n; i >= 1 ; i--)
        fat = fat * i;
    return fat;
}

/* gera combina��es de linhas da matriz a serem exclu�das, r a r, do array nodos */
int combinationUtil(int nodos[], int comb[], int start, int end, int index, int r, int gMIn[][nCols], int gMIn2[][nCols], int auxMatrix[][nCols], int *sNodos)
{
    int i = 0, flag = 0;
    if (index == r && flag == 0)
    {
        flag = deleteNodos(comb, nodos, gMIn, gMIn2, auxMatrix, r, sNodos);
        if (flag == 1)
            return flag;
        else if (flag == -1)
            return -1;
    }
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        comb[index] = nodos[i];
        flag = combinationUtil(nodos, comb, i+1, end, index+1, r, gMIn, gMIn2, auxMatrix, sNodos);
    }
    return flag;
}

/* deleta os nodos combinados na fun��o acima, rearranja a matriz e inicia o swapping and comparing */
int deleteNodos(int comb[], int nodos[], int gMIn[][nCols], int gMIn2[][nCols], int auxMatrix[][nCols], int r, int *sNodos)
{
    int i = 0, j = 0, k = 0, l = 0, flag = 1;
    while(j < *sNodos - r)
    {
        for(k = 0; k < r; k++)
        {
            if(j+1 == comb[k])
                j++;
        }
        while(i < *sNodos - r)
        {
            auxMatrix[i][l] = gMIn2[i][j];
            i++;
        }
        auxMatrix[i][l] = EOG;
        i = 0;
        l++;
        j++;
    }

    for(i = l; i >= 0; i--)
        auxMatrix[i][l] = EOG;
    j = 0;
    k = 0;
    l = 0;
    flag = 1;
    while(flag == 1 && j <= *sNodos - r)
    {
        for(i = 0; i <= *sNodos - r; i++)
        {
            if(gMIn[i][j] == 1)
                k++;
            if(auxMatrix[i][j] == 1)
                l++;
        }
        if(k != l) // chega se o grau dos nodos � diferente
            flag = -1;
        else j++;
    }
    if(flag == -1)
        return flag;
    else
        flag = calcMatrix(nodos, sNodos, gMIn, auxMatrix, r);
    return flag;
}
