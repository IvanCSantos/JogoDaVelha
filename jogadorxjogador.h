#ifndef JOGADORXJOGADOR_H_INCLUDED
#define JOGADORXJOGADOR_H_INCLUDED

#include "struct_ranking.h"
#include "vet_guia.h"
#include "desenhar.h"
#include "entrada.h"
#include "verificacao.h"
#include "inserir_ranking.h"
#include "salvar_ranking.h"

using namespace std;

void jogadorxjogador(int **matriz, int **selecao, int &tam, int &jogador, int &num, string &jogador1, string &jogador2, ranking top[10]){ // fun��o que controla o jogador x jogador
    bool vencer = false;
    int vetL[101], vetC[101], resultado = 0;
    vet_guia(vetL, vetC, tam, matriz); // chama a fun��o para criar o vetor guia que ajuda a manipular a matriz
    float tempo1 = GetTickCount();
    while(vencer == false){ // enquanto ningu�m vencer executa o loop de procedimentos
        desenhar(matriz, selecao, tam, jogador);
        entrada(matriz, selecao, tam, jogador, jogador1, jogador2); // entrada do jogador
        vencer = verificacao(matriz, selecao, tam, jogador, resultado); // faz a verifica��o e retorna true ou false para a vari�vel vencer
        desenhar(matriz, selecao, tam, jogador);
        if (vencer == false){ // se ningu�m venceu ainda, troca de jogador
			((jogador == 1)? jogador = 2 : jogador = 1);
        }
    }
    string temp;
    const char *msg;
    cout << "\n\n";
    float tempo2 = GetTickCount();
    float tempo = (tempo2-tempo1)/1000;
    if(resultado > 0){
        InserirRanking(((jogador==1)? jogador1 : jogador2), tempo, 1, num, top);
        SalvarRanking(num, top);
        temp="Parab�ns ao jogador " + ((resultado==1)? jogador1 : jogador2) + "!";
        msg=temp.c_str();
        centralizar(msg);
    }
    if(resultado == 0){
        centralizar("Deu velha!");
    }
    cout << "                       \n\n"; centralizar("          "); cout << "\n";
    centralizar("Tempo de jogo: ", 8);
    cout << tempo << " segundos\n\n\n\n\n\n\n";
    centralizar("Pressione qualquer tecla para voltar");
    _getch();
}

#endif // JOGADORXJOGADOR_H_INCLUDED
