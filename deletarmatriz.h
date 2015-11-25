#ifndef DELETARMATRIZ_H_INCLUDED
#define DELETARMATRIZ_H_INCLUDED
using namespace std;

int** DeletarMatriz(int **matriz){
    delete matriz[0];
    delete matriz;
}

#endif // DELETARMATRIZ_H_INCLUDED
