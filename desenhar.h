#ifndef DESENHAR_H_INCLUDED
#define DESENHAR_H_INCLUDED

#include "gotoxy.h"
#include "cores.h"
#include "cor.h"
#include "centralizar.h"

using namespace std;

void desenhar(int **matriz, int **selecao, int &tam, int &jogador){
    int reducao=(tam*2)-1;
    gotoxy(1, 1); // limpa a tela toda vez que desenhar
    cout << "\n\n";
    for(int i = 0; i < tam; i++)
    {
        cout << "\n";
        centralizar("", reducao);
        for(int j = 0; j < tam; j++)
        {
            if(j == 0){ // se for a primeira coluna, deixa um espa�o em branco para alinhamento
               cout << "";
            }
            if(j > 0 and j < tam){ // se for a parte do meio da velha, colocar barra para separar
                cout << " | ";
            }
            if(selecao[i][j]==3 and matriz[i][j]==0){ // valor 3 = posi��o selecionada - insere apenas se n�o tiver nenhum valor na matriz principal
                cor(VERDE_ESCURO); // define a cor do cursor como verde escuro
                if(jogador==1)
                    cout << "X";
                else
                    cout << "O";
                cor(PRETO);
            }
            switch(matriz[i][j]){
                case 0:
                    if(selecao[i][j]!=3){ // se for diferente de 3 na matriz sele��o, pode inserir o espa�o em branco, se n�o teria inserido a posi��o selecionada
                        cout << " "; // valor 0 = branco
                    }
                    break;
                case 1:
                    if(selecao[i][j]==3)
                        cor(VERMELHO); // se o cursor estiver em cima do X, representa ele vermelho, indicando que n�o � poss�vel jogar em cima
                    cout << "X"; // valor 1 = X
                    break;
                case 2:
                    if(selecao[i][j]==3)
                        cor(VERMELHO); // se o cursor estiver em cima da O, representa ela vermelha, indicando que n�o � poss�vel jogar em cima
                    cout << "O"; // valor 2 = O
                    break;
            }
            cor(PRETO); // volta a cor do texto para preto
        }
        if(i < tam-1){
            cout << "\n";
            string temp="-----------";
            for(int i=4; i <= tam; i++){
                temp = temp + "----";
            }
            const char *sep = temp.c_str();
            centralizar(sep);
        }
    }
    cout << "\n\n";
}

#endif // DESENHAR_H_INCLUDED
