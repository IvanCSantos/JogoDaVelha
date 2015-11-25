#ifndef VERIFICACAO_H_INCLUDED
#define VERIFICACAO_H_INCLUDED

#include "desenhar.h"
#include "centralizar.h"

using namespace std;

bool verificacao(int **matriz, int **selecao, int &tam, int &jogador, bool ia=false){
    int auxH1=0, auxH2=0, auxV1=0, auxV2=0, auxDP1=0, auxDP2=0, auxDS1=0, auxDS2=0, geral=0, lim;
    if(tam < 5)
        lim = tam;
    if(tam >= 5)
        lim = 5;
    for(int i = 0; i < tam; i++){
        auxH1=0;
        auxH2=0;
        auxV1=0;
        auxV2=0;
        auxDP1=0;
        auxDP2=0;
        auxDS1=0;
        auxDS2=0;
        // incrementação somas
        // verificação horizontal
        for(int j = 0; j < tam; j++){
            if (matriz[i][j]==1){
                auxH1++;
                geral++;
            } else if (matriz[i][j]==2){
                auxH2++;
                geral++;
            }
        // verificação vertical
            if (matriz[j][i]==1){
                auxV1++;
            } else if (matriz[j][i]==2){
                auxV2++;
            }
        // verificação diagonal principal
            if (matriz[j][j]==1){
                auxDP1++;
            } else if (matriz[j][j]==2){
                auxDP2++;
            }
        // verificação diagonal secundária
            if (matriz[j][(tam-1)-j]==1){
                auxDS1++;
            } else if (matriz[j][(tam-1)-j]==2){
                auxDS2++;
            }
        // verificação final
            if(auxH1==lim or auxH2==lim or auxV1==lim or auxV2==lim or auxDP1==lim or auxDP2==lim or auxDS1==lim or auxDS2==lim){
                if(ia==false){
                    desenhar(matriz, selecao, tam);
                    cout << "\n"; centralizar("Parabéns ao jogador ", 2); cout << jogador << "!";
                    return true;
                } else if(ia==true) {
                    if(jogador==1){
                        desenhar(matriz, selecao, tam);
                        cout << "\n"; centralizar("Parabéns ao jogador 1!");
                    }
                    if(jogador==2){
                        desenhar(matriz, selecao, tam);
                        cout << "\n"; centralizar("Parabéns ao computador!");
                    }

                    return true;
                }
            }
            if(geral==tam*tam){ // verificação velha
                desenhar(matriz, selecao, tam);
                cout << "\n"; centralizar("Deu velha!");
                return true;
            }
        }
    }
}

#endif // VERIFICACAO_H_INCLUDED
