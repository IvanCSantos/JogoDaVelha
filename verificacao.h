#ifndef VERIFICACAO_H_INCLUDED
#define VERIFICACAO_H_INCLUDED

#include "desenhar.h"
#include "centralizar.h"

using namespace std;

bool verificacao(int **matriz, int **selecao, int &tam, int &jogador, int &resultado, bool ia=false){
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
        for(int j = 0; j < tam; j++){
            // verificação horizontal
            switch(matriz[i][j]){
                case 0:
                    auxH1=0;
                    auxH2=0;
                    break;
                case 1:
                    auxH1++;
                    auxH2=0;
                    geral++;
                    break;
                case 2:
                    auxH2++;
                    auxH1=0;
                    geral++;
                    break;
            }
            // verificação vertical
            switch(matriz[j][i]){
                case 0:
                    auxV1=0;
                    auxV2=0;
                    break;
                case 1:
                    auxV1++;
                    auxV2=0;
                    break;
                case 2:
                    auxV2++;
                    auxV1=0;
                    break;
            }
            // verificação diagonal principal
            switch(matriz[j][j]){
                case 0:
                    auxDP1=0;
                    auxDP2=0;
                    break;
                case 1:
                    auxDP1++;
                    auxDP2=0;
                    break;
                case 2:
                    auxDP2++;
                    auxDP1=0;
                    break;
            }
            // verificação diagonal secundária
            switch(matriz[j][(tam-1)-j]){
                case 0:
                    auxDS1=0;
                    auxDS2=0;
                    break;
                case 1:
                    auxDS1++;
                    auxDS2=0;
                    break;
                case 2:
                    auxDS2++;
                    auxDS1=0;
                    break;
            }

            // verificação final
            if(auxH1==lim or auxH2==lim or auxV1==lim or auxV2==lim or auxDP1==lim or auxDP2==lim or auxDS1==lim or auxDS2==lim){
                if(jogador==1)
                    resultado=1;
                else
                    resultado=2;
                return true;
            }
            if(geral >= tam*tam){ // verificação velha
                resultado=0;
                return true;
            }
        }
    }
    return false;
}

#endif // VERIFICACAO_H_INCLUDED
