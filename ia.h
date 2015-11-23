#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "centralizar.h"

int ia(int matriz[5][5], int vetL[26], int vetC[26], int &tam, int &dificuldade){
    int opcao;
    bool jogada=false;
    cout << "\n\n"; centralizar("Vez do computador", 0);

    if(dificuldade==1){ // dificuldade fácil
        do{
            opcao = rand() % (tam*tam) + 1; // numero aleatório entre 1 e tam*tam (9, 16 ou 25)
        }while(matriz[vetL[opcao]][vetC[opcao]]!=0); // gera um numero aleatório enquanto não achar um campo em branco
        matriz[vetL[opcao]][vetC[opcao]] = 2;
    }

    if(dificuldade==2){ // dificuldade dificil
        int somaX[4]={0}, somaO[4]={0}, somaV[4]={0}, aux[4]={0}, auxO[4][3]={0}, auxX[4][3]={0}, auxV[4][3]={0};
        /*

        somaX --> Varíavel destinada a somar os campos preenchidas com "X", um contador para definir se o usuário está perto de fechar uma linha.
        somaO --> Varíavel destinada a somar os campos preenchidas com "O", um contador para definir se o computador está perto de fechar uma linha.
        somaV --> Varíavel destinada a somar os campos não preenchidas, um contador para definir jogadas possíveis para o computador.
        aux   --> Variável destinada a guardar o campo vazio.

        Matriz de escolha (auxO[4][3], auxX[4][3] e auxV[4][3]) :
                        opcao(0 ou 1) x posicao_linha x posicao_coluna
        horizontal     0   i   j  --> 0 significa não houve opcao para horizontal
        vertical       1   i   j  --> 1 significa que existe a opcao vertical
        DP             0   i   j  --> 0 significa não houve opcao para DP
        DS             1   i   j  --> 1 significa que existe a opcao DS

        Vetor de soma (SomaX[4] e SomaO[4]):
        horizontal      0          --> incrementa soma de posições ocupadas na horizontal
        vertical        1          --> incrementa soma de posições ocupadas na vertical
        DP              2          --> incrementa soma de posições ocupadas na DP
        DS              3          --> incrementa soma de posições ocupadas na DS

        Vetor aux (aux[4]):
        horizontal      0          --> guarda posicao vazias da horizontal
        vertical        1          --> guarda posicao vazias da vertical
        DP              2          --> guarda posicao vazias da DP
        DS              3          --> guarda posicao vazias da DS
        */

        for (int i=0; i < tam; i++){
            aux[0]=0, aux[1]=0, aux[2]=0, aux[3]=0;
            somaX[0]=0, somaX[1]=0;
            somaO[0]=0, somaO[1]=0;
            somaV[0]=0, somaV[1]=0;
            for (int j=0; j < tam; j++){
                // verificação horizontal
                if (matriz[i][j]==0){
                    aux[0]=j;
                    somaV[0]++;
                } else if(matriz[i][j]==1){
                    somaX[0]++;
                } else if(matriz[i][j]==2){
                    somaO[0]++;
                }
                if (somaO[0]==tam-1 and matriz[i][aux[0]]==0){
                    auxO[0][0]=1;
                    auxO[0][1]=i;
                    auxO[0][2]=aux[0];
                } else if (somaX[0]==tam-1 and matriz[i][aux[0]]==0){
                    auxX[0][0]=1;
                    auxX[0][1]=i;
                    auxX[0][2]=aux[0];
                } else if (somaV[0]==tam-1 and matriz[i][aux[0]]==0){
                    auxV[0][0]=1;
                    auxV[0][1]=i;
                    auxV[0][2]=aux[0];
                }
                // verificação vertical
                if (matriz[j][i]==0){
                    aux[1]=j;
                } else if(matriz[j][i]==1){
                    somaX[1]++;
                } else if(matriz[j][i]==2){
                    somaO[1]++;
                }
                if (somaO[1]==tam-1 and matriz[aux[1]][i]==0){
                    auxO[1][0]=1;
                    auxO[1][1]=aux[1];
                    auxO[1][2]=i;
                } else if (somaX[1]==tam-1 and matriz[aux[1]][i]==0){
                    auxX[1][0]=1;
                    auxX[1][1]=aux[1];
                    auxX[1][2]=i;
                } else if (somaV[1]==tam-1 and matriz[aux[0]][i]==0){
                    auxV[1][0]=1;
                    auxV[1][1]=aux[1];
                    auxV[1][2]=i;
                }
            }
        }
        aux[2]=0, aux[3]=0;
        somaX[2]=0, somaX[3]=0;
        somaO[2]=0, somaO[3]=0;
        somaV[2]=0, somaV[3]=0;
        for (int ii=0; ii < tam; ii++){
            // verficação diagonal principal
            if (matriz[ii][ii]==0){
                aux[2]=ii;
                somaV[2]++;
            } else if(matriz[ii][ii]==1){
                somaX[2]++;
            } else if(matriz[ii][ii]==2){
                somaO[2]++;
            }
            if (somaO[2]==tam-1 and matriz[aux[2]][aux[2]]==0){
                auxO[2][0]=1;
                auxO[2][1]=aux[2];
                auxO[2][2]=aux[2];
            } else if (somaX[2]==tam-1 and matriz[aux[2]][aux[2]]==0){
                auxX[2][0]=1;
                auxX[2][1]=aux[2];
                auxX[2][2]=aux[2];
            } else if (somaV[2]==tam-1 and matriz[aux[2]][aux[2]]==0){
                auxV[2][0]=1;
                auxV[2][1]=aux[2];
                auxV[2][2]=aux[2];
            }
            // verificação diagonal secundária
            if (matriz[ii][tam-1-ii]==0){
                aux[3]=ii;
                somaV[3]++;
            } else if(matriz[ii][tam-1-ii]==1){
                somaX[3]++;
            } else if(matriz[ii][tam-1-ii]==2){
                somaO[3]++;
            }
            if (somaO[3]==tam-1 and matriz[aux[3]][tam-1-aux[3]]==0){
                auxO[3][0]=1;
                auxO[3][1]=aux[3];
                auxO[3][2]=tam-1-aux[3];
            } else if (somaX[3]==tam-1 and matriz[aux[3]][tam-1-aux[3]]==0){
                auxX[3][0]=1;
                auxX[3][1]=aux[3];
                auxX[3][2]=tam-1-aux[3];
            } else if (somaV[3]==tam-1 and matriz[aux[3]][tam-1-aux[3]]==0){
                auxV[3][0]=1;
                auxV[3][1]=aux[3];
                auxV[3][2]=tam-1-aux[3];
            }
        }
        // joga com prioridade vencer.
        for(int ii=0; ii < 4; ii++){
            if(auxO[ii][0]==1){
                matriz[auxO[ii][1]][auxO[ii][2]]=2;
                jogada=true;
                return 0;
            }
        }
        // se nao puder vencer, joga com prioridade bloquear.
        for(int jj=0; jj < 4; jj++){
            if(auxX[jj][0]==1){
                matriz[auxX[jj][1]][auxX[jj][2]]=2;
                jogada=true;
                return 0;
            }
        }
        // se não puder vencer ou bloquear, joga em uma posição estratégica para formar um jogo.
        for(int vv=0; vv < 4; vv++){
            if(auxV[vv][0]==1){
                matriz[auxV[vv][1]][auxV[vv][2]]=2;
                jogada=true;
                return 0;
            }
        }
        if(jogada==false){ // caso não há chance de ganhar ou risco de perder, joga aleatório
            do{
                opcao = rand() % (tam*tam) + 1;
            }while(matriz[vetL[opcao]][vetC[opcao]]!=0);
            matriz[vetL[opcao]][vetC[opcao]] = 2;
        }
    }
}

#endif // IA_H_INCLUDED
