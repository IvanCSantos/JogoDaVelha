#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "jogadorxcomputador.h"
#include "jogadorxjogador.h"
#include "centralizar.h"
#include "cor.h"
#include "cores.h"
#include "limparmatriz.h"
#include "deletarmatriz.h"
#include "criarmatriz.h"
#include "mostrar_ranking.h"
#include "carregar_ranking.h"
#include "ordenar_ranking.h"

using namespace std;

int sair(){
    return EXIT_FAILURE; // retorna algum valor para sair do programa
}

void menu_comojogar(int &tam, int &dificuldade){ // texto de como jogar
    system("cls");
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("COMO JOGAR"); cout << "\n\n";
    cor(PRETO);
    centralizar("Controle do cursor: setas do teclado"); cout << "\n\n";
    centralizar("Inserir jogada: ENTER"); cout << "\n\n\n\n";
    centralizar("Pressione qualquer tecla para voltar");
    _getch();
}

string menu_nome(int jogador){
    string nome;
    system("cls");
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("NOME DO JOGADOR");
    cout << "\n\n";
    cor(PRETO);
    centralizar("Nome do jogador ", 1); cout << jogador << ":\n\n";
    centralizar("", 4);
    cin >> nome;
    return nome;
}

void menu_tam(int &tam){
    system("cls");
    int opcao; // variavel local para armazenar a opção escolhida
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Digite o número do tamanho desejado (de 3 à 10):"); cout << "\n\n";
    cor(PRETO);
    centralizar("Tamanho: ");
    cin >> tam; // define o tamanho da matriz com base na escolha do usuário
    if(tam < 3 or tam > 10)
        menu_tam(tam);
}

void menu_dificuldade(int &dificuldade){
    system("cls");
    int opcao; // variavel local para armazenar a opção escolhida
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Digite o número da dificuldade desejada"); cout << "\n\n";
    cor(PRETO);
    centralizar("1. Fácil"); cout << "\n";
    centralizar("2. Difícil"); cout << "\n\n";
    centralizar("Opção: ", 1);
    cin >> opcao;
    if(opcao < 1 or opcao > 2)
        menu_dificuldade(dificuldade);
    dificuldade = opcao; // define a dificuldade do jogo com base na escolha do usuário
}

void menu(int &tam, int &dificuldade, ranking ranking[10]){
    system("cls");
    int opcao, jogador=1, num, ordenacao[10]={0}; // variavel local para armazenar a opção escolhida
    string jogador1, jogador2;
    bool saiu=false;
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("BEM-VINDO AO JOGO DA VELHA!"); cout << "\n\n";
    cor(PRETO);
    centralizar("Digite o número da opção desejada:"); cout << "\n\n";
    centralizar("1. Jogador vs. Computador"); cout << "\n";
    centralizar("2. Jogador vs. Jogador"); cout << "\n";
    centralizar("3. Ranking TOP 10"); cout << "\n";
    centralizar("4. Como jogar"); cout << "\n";
    centralizar("5. Sair"); cout << "\n\n";
    centralizar("Opção: ", 1);
    cin >> opcao;
    if(opcao < 1 or opcao > 5)
        menu(tam, dificuldade, ranking);
    if(opcao > 2)
        saiu=true;
    if(saiu==false)
        menu_tam(tam);
    int** matriz = CriarMatriz(tam);
    int** selecao = CriarMatriz(tam);
    LimparMatriz(matriz, tam); // toda vez que voltar ao menu limpa as matrizes
    LimparMatriz(selecao, tam);
    switch(opcao) // redireciona para outras funções com base na escolha do usuário
    {
        case 1:
            menu_dificuldade(dificuldade);
            jogador1 = menu_nome(1);
            jogadorxcomputador(matriz, selecao, tam, dificuldade, jogador, jogador1);
            DeletarMatriz(matriz);
            DeletarMatriz(selecao);
            menu(tam, dificuldade, ranking);
            break;
        case 2:
            jogador1 = menu_nome(1);
            jogador2 = menu_nome(2);
            jogadorxjogador(matriz, selecao, tam, jogador, jogador1, jogador2);
            DeletarMatriz(matriz);
            DeletarMatriz(selecao);
            menu(tam, dificuldade, ranking);
            break;
        case 3:
            CarregarRanking(ranking, num);
            OrdenarRanking(ranking, ordenacao, num);
            MostrarRanking(ranking, ordenacao, num);
            menu(tam, dificuldade, ranking);
            break;
        case 4:
            menu_comojogar(tam, dificuldade);
            menu(tam, dificuldade, ranking);
            break;
        case 5:
            sair();
            break;
    }
}

#endif // MENU_H_INCLUDED
