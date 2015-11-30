#ifndef JOGADORXCOMPUTADOR_H_INCLUDED
#define JOGADORXCOMPUTADOR_H_INCLUDED

#include "struct_ranking.h"
#include "vet_guia.h"
#include "verificacao.h"
#include "desenhar.h"
#include "ia.h"
#include "entrada.h"
#include "inserir_ranking.h"
#include "salvar_ranking.h"

using namespace std;

void jogadorxcomputador(int **matriz, int **selecao, int &tam, int &dificuldade, int &jogador, int &num, string &jogador1, ranking top[10]){ // função que controla o jogador x computador
    bool vencer = false, computador = true;
    int vetL[101], vetC[101], resultado=0;
    vet_guia(vetL, vetC, tam, matriz); // chama a função para criar o vetor guia que ajuda a manipular a matriz
    float tempo1 = GetTickCount();
    while(vencer == false){ // enquanto ninguém vencer executa o loop de procedimentos
        desenhar(matriz, selecao, tam, jogador);
        entrada(matriz, selecao, tam, jogador, jogador1); // entrada do jogador
        desenhar(matriz, selecao, tam, jogador);
        vencer = verificacao(matriz, selecao, tam, jogador, resultado, computador); // faz a verificação e retorna true ou false para a variável vencer
        if(vencer==false){
            ((jogador == 1)? jogador = 2 : jogador = 1);
            ia(matriz, vetL, vetC, tam, dificuldade); // função que faz a jogada do computador
            Sleep(1000);
            vencer = verificacao(matriz, selecao, tam, jogador, resultado, computador); // faz a verificação e retorna true ou false para a variável vencer
            desenhar(matriz, selecao, tam, jogador);
        }
    }
    string temp;
    const char *msg;
    cout << "\n\n";
    float tempo2 = GetTickCount();
    float tempo = (tempo2-tempo1)/1000;
    if(resultado == 1){
        InserirRanking(jogador1, tempo, 0, num, top);
        SalvarRanking(num, top);
        temp="Parabéns ao jogador " + jogador1 + "!";
        msg=temp.c_str();
        centralizar(msg);
    }
    if(resultado == 2){
        centralizar("O computador venceu!");
    }
    if(resultado == 0){
        centralizar("Deu velha!");
    }
    cout << "\n\n"; centralizar("                   "); cout << "\n";
    centralizar("Tempo de jogo: ", 8);
    cout << tempo << " segundos\n\n\n\n\n";
    centralizar("Pressione qualquer tecla para voltar");
    _getch();
}

#endif // JOGADORXCOMPUTADOR_H_INCLUDED
