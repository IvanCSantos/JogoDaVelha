#ifndef LIMPARMATRIZ_H_INCLUDED
#define LIMPARMATRIZ_H_INCLUDED
using namespace std;

void LimparMatriz(int **matriz, int &tam){ // fun��o para limpar a matriz toda vez que um novo jogo come�ar
    for(int i=0; i < tam; i++){
        for(int j=0; j < tam; j++){
            matriz[i][j]=0;
        }
    }
}

#endif // LIMPARMATRIZ_H_INCLUDED
