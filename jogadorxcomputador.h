#ifndef JOGADORXCOMPUTADOR_H_INCLUDED
#define JOGADORXCOMPUTADOR_H_INCLUDED

#include "vet_guia.h"
#include "verificacao.h"
#include "desenhar.h"
#include "ia.h"
#include "entrada.h"

using namespace std;

void jogadorxcomputador(int **matriz, int **selecao, int &tam, int &dificuldade){ // fun��o que controla o jogador x computador
    bool vencer = false, computador = true;
    int jogador = 1;
    int vetL[101], vetC[101];
    vet_guia(vetL, vetC, tam, matriz); // chama a fun��o para criar o vetor guia que ajuda a manipular a matriz
    while(vencer == false){ // enquanto ningu�m vencer executa o loop de procedimentos
        jogador=1;
        desenhar(matriz, selecao, tam);
        entrada(matriz, selecao, tam, jogador); // entrada do jogador
        desenhar(matriz, selecao, tam);
        vencer = verificacao(matriz, selecao, tam, jogador, computador); // faz a verifica��o e retorna true ou false para a vari�vel vencer
        if(vencer==false){
            jogador=2;
            ia(matriz, vetL, vetC, tam, dificuldade); // fun��o que faz a jogada do computador
            Sleep(1000);
            vencer = verificacao(matriz, selecao, tam, jogador, computador); // faz a verifica��o e retorna true ou false para a vari�vel vencer
            desenhar(matriz, selecao, tam);
        }
    }
}

#endif // JOGADORXCOMPUTADOR_H_INCLUDED
