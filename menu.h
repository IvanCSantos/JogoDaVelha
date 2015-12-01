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
#include "mostrar_cursor.h"

using namespace std;

int sair(){
    return EXIT_FAILURE; // retorna algum valor para sair do programa
}

void menu_comojogar(int &tam, int &dificuldade){ // texto de como jogar
    system("cls");
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("COMO JOGAR"); cout << "\n\n\n";
    cor(PRETO);
    centralizar("CONTROLE"); cout << "\n";
    centralizar("Controle do cursor: setas do teclado"); cout << "\n";
    centralizar("Inserir jogada: ENTER"); cout << "\n\n\n";
    centralizar("COMO GANHAR"); cout << "\n";
    centralizar("Do tamanho 3 ao tamanho 5 é necessário uma sequência completa para ganhar."); cout << "\n";
    centralizar("De 5 para cima é necessário uma sequência apenas de 5 para ganhar o jogo"); cout << "\n\n\n\n";
    centralizar("Pressione qualquer tecla para voltar");
    _getch();
}

int escolher_jogador(){
	mostrar_cursor(false);
    int jogador = rand() % 2 + 1;
    int num = 1;
    char graph = '|';
    system("cls");
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("QUEM IRÁ COMEÇAR O JOGO");
    cout << "\n\n";
    cor(PRETO);
    centralizar("Jogador ", 1);
    for(int i=0; i < 75; i++){
        gotoxy(49, 6);
        /*if(i == 99){
            cout << jogador;
        } else {
            cout << num;
            ((num == 1)? num = 2 : num = 1);
        }
        Sleep(25+(i*2));
        */
        if(i == 74){
            cout << jogador;
        } else {
            cout << graph;
            ((num == 1)? graph = '|' : num = num);
            ((num == 2)? graph = '/' : num = num);
            ((num == 3)? graph = '--' : num = num);
            ((num == 4)? graph = '\\' : num = num);
            num++;
            ((num == 5)? num = 1 : num = num);
        }
        Sleep(10+(i*2));
    }
    gotoxy(49, 6);
    cout << jogador << "\n\n\n";
    centralizar("Pressione qualquer tecla");
    _getch();
    return jogador;
}

string menu_nome(int jogador){
	mostrar_cursor(true);
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
	mostrar_cursor(false);
    return nome;
}

void menu_tam(int &tam){
	mostrar_cursor(true);
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
	mostrar_cursor(false);
}

void menu_dificuldade(int &dificuldade){
    system("cls");
    int opcao=1, _opcao, tecla=0, y=6; // variavel local para armazenar a opção escolhida
    bool enter=false;
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Selecione a dificuldade desejada"); cout << "\n\n";
    cor(PRETO);
    centralizar("Fácil"); cout << "\n";
    centralizar("Difícil"); cout << "\n";
    cor(VERDE_ESCURO);
    gotoxy(40, y+(opcao-1)); cout << ">"; gotoxy(50, y+(opcao-1)); cout << "<";
    while(enter==false){
        tecla=0;
        _opcao=opcao;
        gotoxy(45, 8);
        switch((tecla = _getch())) { // C será o código da tecla pressionada
            case KEY_UP: // caso for tecla para cima (W) diminui a linha em 1
                if(opcao == 2)
                    opcao--;
                break;
            case KEY_DOWN: // caso for tecla para baixo (S) aumenta a linha em 1
                if(opcao == 1)
                    opcao++;
                break;
            case KEY_ENTER: // caso for tecla ENTER insere a jogada na posição selecionada apenas se já estiver vazia
                enter=true;
                break;
        }
        gotoxy(40, y+(_opcao-1)); cout << " "; gotoxy(50, y+(_opcao-1)); cout << " ";
        gotoxy(40, y+(opcao-1)); cout << ">"; gotoxy(50, y+(opcao-1)); cout << "<";
    }
    cor(PRETO);
    if(opcao < 1 or opcao > 2)
        menu_dificuldade(dificuldade);
    dificuldade = opcao; // define a dificuldade do jogo com base na escolha do usuário
}

void menu(int &tam, int &dificuldade, ranking top[10]){
	mostrar_cursor(false);
    system("cls");
    int opcao=1, jogador, num, ordenacao[10]={0}, tecla=0, y=8, _opcao; // variavel local para armazenar a opção escolhida
    string jogador1, jogador2;
    bool saiu=false, enter=false;
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("BEM-VINDO AO JOGO DA VELHA!"); cout << "\n\n";
    cor(PRETO);
    centralizar("Selecione a opção desejada:"); cout << "\n\n";
    centralizar("Jogador vs. Computador"); cout << "\n";
    centralizar("Jogador vs. Jogador"); cout << "\n";
    centralizar("Ranking top 10"); cout << "\n";
    centralizar("Como jogar"); cout << "\n";
    centralizar("Sair"); cout << "\n\n";
    cor(VERDE_ESCURO);
    gotoxy(33, y+(opcao-1)); cout << ">"; gotoxy(58, y+(opcao-1)); cout << "<";
    while(enter==false){
        tecla=0;
        _opcao=opcao;
        gotoxy(45, 14);
        switch((tecla = _getch())) { // C será o código da tecla pressionada
            case KEY_UP: // caso for tecla para cima (W) diminui a linha em 1
                if(opcao > 1)
                    opcao--;
                break;
            case KEY_DOWN: // caso for tecla para baixo (S) aumenta a linha em 1
                if(opcao < 5)
                    opcao++;
                break;
            case KEY_ENTER: // caso for tecla ENTER insere a jogada na posição selecionada apenas se já estiver vazia
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
    switch(opcao) // redireciona para outras funções com base na escolha do usuário
    {
        case 1:
            menu_dificuldade(dificuldade);
            jogador1 = menu_nome(1);
            jogador = escolher_jogador();
            jogadorxcomputador(matriz, selecao, tam, dificuldade, jogador, num, jogador1, top);
            DeletarMatriz(matriz);
            DeletarMatriz(selecao);
            menu(tam, dificuldade, top);
            break;
        case 2:
            jogador1 = menu_nome(1);
            jogador2 = menu_nome(2);
            jogador = escolher_jogador();
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
