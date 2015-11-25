#ifndef ENTRADA_H_INCLUDED
#define ENTRADA_H_INCLUDED
#include <conio.h>

#include "teclas.h"
#include "centralizar.h"
#include "desenhar.h"
#include "limparmatriz.h"

using namespace std;

void entrada(int **matriz, int **selecao, int &tam, int &jogador){
    int opcao, opL=0, opC=0, c=0;
    bool jogou=false; // variável que controla o loop de jogada
    system("cls");
    LimparMatriz(selecao, tam);
    selecao[0][0]=3; // sempre que começar uma nova entrada, volta o cursor para a primeira posição
    do {
        desenhar(matriz, selecao, tam);
        cout << "\n\n";
        centralizar("Jogador ");
        cout << jogador << "\n";
            c=0;
            switch((c=_getch())) { // C será o código da tecla pressionada
                case KEY_UP: // caso for tecla para cima (W) diminui a linha em 1
                    selecao[opL][opC]=0;
                    opL--;
                    break;
                case KEY_DOWN: // caso for tecla para baixo (S) aumenta a linha em 1
                    selecao[opL][opC]=0;
                    opL++;
                    break;
                case KEY_RIGHT: // caso for tecla para direita (D) aumenta a coluna em 1
                    selecao[opL][opC]=0;
                    opC++;
                    break;
                case KEY_LEFT: // caso for tecla para a esquerda (A) diminui a coluna em 1
                    selecao[opL][opC]=0;
                    opC--;
                    break;
                case KEY_ENTER: // caso for tecla ENTER insere a jogada na posição selecionada apenas se já estiver vazia
                    if(matriz[opL][opC]==0){
                        matriz[opL][opC]=jogador;
                        jogou=true;
                    }
                    break;
            }
            if(opL >= tam){ // impede que a posição passe dos limites da matriz
                opL=tam-1;
            }
            if(opL < 0){
                opL=0;
            }
            if(opC >= tam){
                opC=tam-1;
            }
            if(opC < 0){
                opC=0;
            }
            selecao[opL][opC]=3; // insere a posição desejada na matriz seleção
            desenhar(matriz, selecao, tam);
    } while(jogou==false); // repete o loop de posição até que seja jogado numa posição
}

#endif // ENTRADA_H_INCLUDED
