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

using namespace std;

int sair(){
    return EXIT_FAILURE; // retorna algum valor para sair do programa
}


void menu_comojogar(int &tam, int &dificuldade){ // texto de como jogar
    system("cls");
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Como jogar:"); cout << "\n\n";
    cor(PRETO);
    centralizar("Controle do cursor: setas do teclado"); cout << "\n\n";
    centralizar("Inserir jogada: ENTER"); cout << "\n\n";
    system("pause");
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
    centralizar("Tamanho: ", 1);
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

void menu(int &tam, int &dificuldade){
    system("cls");
    int opcao, jogador=1; // variavel local para armazenar a opção escolhida
    string jogador1, jogador2;
    bool saiu=false;
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("BEM-VINDO AO JOGO DA VELHA!"); cout << "\n\n";
    cor(PRETO);
    centralizar("Digite o número da opção desejada:"); cout << "\n\n";
    centralizar("1. Jogador vs. Computador"); cout << "\n";
    centralizar("2. Jogador vs. Jogador"); cout << "\n";
    centralizar("3. Como jogar"); cout << "\n";
    centralizar("4. Sair"); cout << "\n\n";
    centralizar("Opção: ", 1);
    cin >> opcao;
    if(opcao < 1 or opcao > 4)
        menu(tam, dificuldade);
    if(opcao==4 or opcao==3)
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
            menu(tam, dificuldade);
            break;
        case 2:
            jogador1 = menu_nome(1);
            jogador2 = menu_nome(2);
            jogadorxjogador(matriz, selecao, tam, jogador, jogador1, jogador2);
            DeletarMatriz(matriz);
            DeletarMatriz(selecao);
            menu(tam, dificuldade);
            break;
        case 3:
            menu_comojogar(tam, dificuldade);
            menu(tam, dificuldade);
            break;
        case 4:
            sair();
            break;
    }
}

#endif // MENU_H_INCLUDED
