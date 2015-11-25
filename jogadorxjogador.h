#ifndef JOGADORXJOGADOR_H_INCLUDED
#define JOGADORXJOGADOR_H_INCLUDED

#include "vet_guia.h"
#include "desenhar.h"
#include "entrada.h"
#include "verificacao.h"

using namespace std;

void jogadorxjogador(int **matriz, int **selecao, int &tam){ // função que controla o jogador x jogador
    bool vencer = false;
    int jogador = 1;
    int vetL[101], vetC[101];
    vet_guia(vetL, vetC, tam, matriz); // chama a função para criar o vetor guia que ajuda a manipular a matriz
    while(vencer == false){ // enquanto ninguém vencer executa o loop de procedimentos
        desenhar(matriz, selecao, tam);
        entrada(matriz, selecao, tam, jogador); // entrada do jogador
        vencer = verificacao(matriz, selecao, tam, jogador); // faz a verificação e retorna true ou false para a variável vencer
        desenhar(matriz, selecao, tam);
        if (vencer==false){ // se ninguém venceu ainda, troca de jogador
            if(jogador==1){
                jogador = 2;
            } else {
                jogador = 1;
            }
        }
    }
}

#endif // JOGADORXJOGADOR_H_INCLUDED
