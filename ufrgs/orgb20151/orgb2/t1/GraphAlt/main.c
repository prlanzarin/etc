#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nRows 50
#define nCols 50

void graphParser(FILE *arq, int gMIn[][nCols], int gMIn2[][nCols], int *fNodos, int *sNodos);

int main()
{
    FILE *graphIn;
    int graphMatrixIn[nRows][nCols], graphMatrixIn2[nRows][nCols], *fNodos, *sNodos;
    graphParser(graphIn, graphMatrixIn, graphMatrixIn2, fNodos, sNodos);
    return 0;
}

void graphParser(FILE *arq, int gMIn[][nCols], int gMIn2[][nCols], int *fNodos, int *sNodos)
{
    char matrixLine[52], *token;
    int i = 0, j = 0, aux = 0;
    arq = fopen("grafo1m.txt", "r");
    if(arq == NULL)
        printf("Erro na abertura do arquivo texto dos grafos de entrada.\n");
    else
    {
        aux = fgetc(arq);
        while(!feof(arq) || aux != '#')
        {
            printf("TST\n");
            fseek(arq,-sizeof(char), SEEK_CUR);
            if(fgets(matrixLine, sizeof(matrixLine), arq) != NULL)
            {
                token = strtok(matrixLine," ");
                while(token != NULL)
                {
                    if(token[0] != '\n')
                    {
                        gMIn[i][j] = atoi(token);
                        i++;
                    }
                    token = strtok(NULL, " ");
                }
                gMIn[i][j] = -1;
                i = 0;
                j++;
                fscanf(arq, "%c", &aux);
                printf("%c TST3\n", aux);
            }
        }

        for(i = j; i >= 0; i--)
            gMIn[i][j] = -1;
    }

    printf("-----------ADJACENCY MATRIX-----------\n");
    i = 0;
    j = 0;
    while(gMIn[i][j] != -1)
    {
        while(gMIn[i][j] != -1)
        {
            printf("%d ", gMIn[i][j]);
            i++;
        }
        i = 0;
        j++;
        printf("\n");
    }
    fclose(arq);
}
