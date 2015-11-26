#ifndef JOGADORXJOGADOR_H_INCLUDED
#define JOGADORXJOGADOR_H_INCLUDED

#include "vet_guia.h"
#include "desenhar.h"
#include "entrada.h"
#include "verificacao.h"

using namespace std;

void jogadorxjogador(int **matriz, int **selecao, int &tam, int &jogador, string &jogador1, string &jogador2){ // função que controla o jogador x jogador
    bool vencer = false;
    int vetL[101], vetC[101];
    vet_guia(vetL, vetC, tam, matriz); // chama a função para criar o vetor guia que ajuda a manipular a matriz
    float tempo1 = GetTickCount();
    while(vencer == false){ // enquanto ninguém vencer executa o loop de procedimentos
        desenhar(matriz, selecao, tam, jogador);
        entrada(matriz, selecao, tam, jogador, jogador1, jogador2); // entrada do jogador
        vencer = verificacao(matriz, selecao, tam, jogador); // faz a verificação e retorna true ou false para a variável vencer
        desenhar(matriz, selecao, tam, jogador);
        if (vencer==false){ // se ninguém venceu ainda, troca de jogador
            if(jogador==1){
                jogador = 2;
            } else {
                jogador = 1;
            }
        }
    }
    float tempo2 = GetTickCount();
    float tempo = (tempo2-tempo1)/1000;
    cout << "\n\n"; centralizar("          "); cout << "\n";
    centralizar("Tempo de jogo: ", 8);
    cout << tempo << " segundos\n\n\n\n\n\n\n";
    centralizar("Pressione qualquer tecla para voltar");
    _getch();
}

#endif // JOGADORXJOGADOR_H_INCLUDED
