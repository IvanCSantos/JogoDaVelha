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
    bool jogou=false; // vari�vel que controla o loop de jogada
    system("cls");
    LimparMatriz(selecao, tam);
    selecao[0][0]=3; // sempre que come�ar uma nova entrada, volta o cursor para a primeira posi��o
    do {
        desenhar(matriz, selecao, tam);
        cout << "\n\n";
        centralizar("Jogador ");
        cout << jogador << "\n";
            c=0;
            switch((c=_getch())) { // C ser� o c�digo da tecla pressionada
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
                case KEY_ENTER: // caso for tecla ENTER insere a jogada na posi��o selecionada apenas se j� estiver vazia
                    if(matriz[opL][opC]==0){
                        matriz[opL][opC]=jogador;
                        jogou=true;
                    }
                    break;
            }
            if(opL >= tam){ // impede que a posi��o passe dos limites da matriz
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
            selecao[opL][opC]=3; // insere a posi��o desejada na matriz sele��o
            desenhar(matriz, selecao, tam);
    } while(jogou==false); // repete o loop de posi��o at� que seja jogado numa posi��o
}

#endif // ENTRADA_H_INCLUDED
