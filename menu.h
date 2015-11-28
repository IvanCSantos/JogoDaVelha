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
#include "gotoxy.h"

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
    int opcao; // variavel local para armazenar a op��o escolhida
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Digite o n�mero do tamanho desejado (de 3 � 10):"); cout << "\n\n";
    cor(PRETO);
    centralizar("Tamanho: ");
    cin >> tam; // define o tamanho da matriz com base na escolha do usu�rio
    if(tam < 3 or tam > 10)
        menu_tam(tam);
}

void menu_dificuldade(int &dificuldade){
    system("cls");
    int opcao; // variavel local para armazenar a op��o escolhida
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Digite o n�mero da dificuldade desejada"); cout << "\n\n";
    cor(PRETO);
    centralizar("1. F�cil"); cout << "\n";
    centralizar("2. Dif�cil"); cout << "\n\n";
    centralizar("Op��o: ", 1);
    cin >> opcao;
    if(opcao < 1 or opcao > 2)
        menu_dificuldade(dificuldade);
    dificuldade = opcao; // define a dificuldade do jogo com base na escolha do usu�rio
}

void menu(int &tam, int &dificuldade, ranking top[10]){
    system("cls");
    int opcao=1, jogador=1, num, ordenacao[10]={0}, tecla=0, y=8, _opcao; // variavel local para armazenar a op��o escolhida
    string jogador1, jogador2;
    bool saiu=false, enter=false;
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("BEM-VINDO AO JOGO DA VELHA!"); cout << "\n\n";
    cor(PRETO);
    centralizar("Digite o n�mero da op��o desejada:"); cout << "\n\n";
    centralizar("Jogador vs. Computador"); cout << "\n";
    centralizar("Jogador vs. Jogador"); cout << "\n";
    centralizar("Ranking TOP 10"); cout << "\n";
    centralizar("Como jogar"); cout << "\n";
    centralizar("Sair"); cout << "\n\n";
    cor(VERDE_ESCURO);
    gotoxy(33, y+(opcao-1)); cout << ">"; gotoxy(58, y+(opcao-1)); cout << "<";
    while(enter==false){
        tecla=0;
        _opcao=opcao;
        switch((tecla = _getch())) { // C ser� o c�digo da tecla pressionada
            case KEY_UP: // caso for tecla para cima (W) diminui a linha em 1
                if(opcao > 1)
                    opcao--;
                break;
            case KEY_DOWN: // caso for tecla para baixo (S) aumenta a linha em 1
                if(opcao < 5)
                    opcao++;
                break;
            case KEY_ENTER: // caso for tecla ENTER insere a jogada na posi��o selecionada apenas se j� estiver vazia
                enter=true;
                break;
        }
        gotoxy(33, y+(_opcao-1)); cout << " "; gotoxy(58, y+(_opcao-1)); cout << " ";
        gotoxy(33, y+(opcao-1)); cout << ">"; gotoxy(58, y+(opcao-1)); cout << "<";
    }
    cor(PRETO);
    if(opcao < 1 or opcao > 5)
        menu(tam, dificuldade, top);
    if(opcao > 2)
        saiu=true;
    if(saiu==false)
        menu_tam(tam);
    int** matriz = CriarMatriz(tam);
    int** selecao = CriarMatriz(tam);
    LimparMatriz(matriz, tam); // toda vez que voltar ao menu limpa as matrizes
    LimparMatriz(selecao, tam);
    CarregarRanking(top, num);
    switch(opcao) // redireciona para outras fun��es com base na escolha do usu�rio
    {
        case 1:
            menu_dificuldade(dificuldade);
            jogador1 = menu_nome(1);
            jogadorxcomputador(matriz, selecao, tam, dificuldade, jogador, num, jogador1, top);
            DeletarMatriz(matriz);
            DeletarMatriz(selecao);
            menu(tam, dificuldade, top);
            break;
        case 2:
            jogador1 = menu_nome(1);
            jogador2 = menu_nome(2);
            jogadorxjogador(matriz, selecao, tam, jogador, num, jogador1, jogador2, top);
            DeletarMatriz(matriz);
            DeletarMatriz(selecao);
            menu(tam, dificuldade, top);
            break;
        case 3:
            OrdenarRanking(top, ordenacao, num);
            MostrarRanking(top, ordenacao, num);
            menu(tam, dificuldade, top);
            break;
        case 4:
            menu_comojogar(tam, dificuldade);
            menu(tam, dificuldade, top);
            break;
        case 5:
            sair();
            break;
    }
}

#endif // MENU_H_INCLUDED
