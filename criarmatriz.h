#ifndef CRIARMATRIZ_H_INCLUDED
#define CRIARMATRIZ_H_INCLUDED
using namespace std;

int** CriarMatriz(int &tam){
    int **matriz = new int*[tam];
    matriz[0] = new int [tam*tam];

    for (int i=1; i<tam; i++)
        matriz[i] = matriz[i-1]+tam;

    for (int i=0; i<tam; i++)
        for (int j=0; j<tam; j++)
            matriz[i][j] = i+j;
    return matriz;
}

#endif // CRIARMATRIZ_H_INCLUDED
