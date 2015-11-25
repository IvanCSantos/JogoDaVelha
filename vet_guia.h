#ifndef VET_GUIA_H_INCLUDED
#define VET_GUIA_H_INCLUDED
using namespace std;

void vet_guia(int vetL[101], int vetC[101], int &tam, int **matriz){ // função para o vetor que guia no processo da entrada na matriz
    int valor=0, aux=1;
    for(int i = 1; i <= tam*tam; i++){ // vetor guia das linhas, cria um vetor conforme o tamanho, ex: 0, 0, 0, 1, 1, 1, 2, 2, 2.
        if (aux > tam){
            valor++;
            aux=1;
        }
        if (aux <= tam){
            vetL[i]=valor;
            aux++;
        }
    }

    valor=0;
    for(int i = 1; i <= tam*tam; i++){ // vetor guia das colunas, cria um vetor conforme o tamanho, ex: 0, 1, 2, 0, 1, 2, 0, 1, 2.
        if(valor==tam){
            valor=0;
        }
        if (valor < tam){
            vetC[i]=valor;
            valor++;
        }
    }
}

#endif // VET_GUIA_H_INCLUDED
