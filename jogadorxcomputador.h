#ifndef JOGADORXCOMPUTADOR_H_INCLUDED
#define JOGADORXCOMPUTADOR_H_INCLUDED

#include "vet_guia.h"
#include "verificacao.h"
#include "desenhar.h"
#include "ia.h"
#include "entrada.h"

using namespace std;

void jogadorxcomputador(int **matriz, int **selecao, int &tam, int &dificuldade, int &jogador, string &jogador1){ // função que controla o jogador x computador
    bool vencer = false, computador = true;
    int vetL[101], vetC[101];
    vet_guia(vetL, vetC, tam, matriz); // chama a função para criar o vetor guia que ajuda a manipular a matriz
    float tempo1 = GetTickCount();
    while(vencer == false){ // enquanto ninguém vencer executa o loop de procedimentos
        jogador=1;
        desenhar(matriz, selecao, tam, jogador);
        entrada(matriz, selecao, tam, jogador, jogador1); // entrada do jogador
        desenhar(matriz, selecao, tam, jogador);
        vencer = verificacao(matriz, selecao, tam, jogador, computador); // faz a verificação e retorna true ou false para a variável vencer
        if(vencer==false){
            jogador=2;
            ia(matriz, vetL, vetC, tam, dificuldade); // função que faz a jogada do computador
            Sleep(1000);
            vencer = verificacao(matriz, selecao, tam, jogador, computador); // faz a verificação e retorna true ou false para a variável vencer
            desenhar(matriz, selecao, tam, jogador);
        }
    }
    float tempo2 = GetTickCount();
    float tempo = (tempo2-tempo1)/1000;
    cout << "\n"; centralizar("                   "); cout << "\n";
    centralizar("Tempo de jogo: ", 8);
    cout << tempo << " segundos\n\n\n\n\n";
    centralizar("Pressione qualquer tecla para voltar");
    _getch();
}

#endif // JOGADORXCOMPUTADOR_H_INCLUDED
