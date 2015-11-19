#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "centralizar.h"

int ia(int matriz[5][5], int vetL[26], int vetC[26], int &tam, int &dificuldade){
    int opcao;
    bool jogada=false;
    cout << "\n\n"; centralizar("Vez do computador", 0);

    if(dificuldade==1){ // dificuldade f�cil
        do{
            opcao = rand() % (tam*tam) + 1; // numero aleat�rio entre 1 e tam*tam (9, 16 ou 25)
        }while(matriz[vetL[opcao]][vetC[opcao]]!=0); // gera um numero aleat�rio enquanto n�o achar um campo em branco
        matriz[vetL[opcao]][vetC[opcao]] = 2;
    }

    if(dificuldade==2){ // dificuldade dificil
        int somaX[4]={0}, somaO[4]={0}, aux[4]={0}, auxO[4][3]={0}, auxX[4][3]={0};
        /*
        Matriz de escolha=
                        opcao(0 ou 1) x posicao_linha x posicao_coluna
        horizontal     o   i   j  --> 0 significa n�o houve opcao para horizontal
        vertical       1   i   j  --> 1 significa que existe a opcao vertical
        DP             0   i   j  --> 0 significa n�o houve opcao para DP
        DS             1   i   j  --> 1 significa que existe a opcao DS

        Vetor de soma:
        horizontal      0          --> incrementa soma horizontal
        vertical        1          --> incrementa soma vertical
        DP              2          --> incrementa soma DP
        DS              3          --> incrementa soma DS

        Vetor aux:
        horizontal      0          --> guarda posicao horizontal
        vertical        1          --> guarda posicao vertical
        DP              2          --> guarda posicao DP
        DS              3          --> guarda posicao DS
        */
        for (int i=0; i < tam; i++){
            aux[0]=0, aux[1]=0, aux[2]=0, aux[3]=0;
            somaX[0]=0, somaX[1]=0;
            somaO[0]=0, somaO[1]=0;
            for (int j=0; j < tam; j++){
                // verifica��o horizontal
                if (matriz[i][j]==0){
                    aux[0]=j;
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
                }
                // verifica��o vertical
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
                }
            }
        }
        aux[2]=0, aux[3]=0;
        somaX[2]=0, somaX[3]=0;
        somaO[2]=0, somaO[3]=0;
        for (int ii=0; ii < tam; ii++){
            // verfica��o diagonal principal
            if (matriz[ii][ii]==0){
                aux[2]=ii;
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
            }
            // verifica��o diagonal secund�ria
            if (matriz[ii][tam-1-ii]==0){
                aux[3]=ii;
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
        if(jogada==false){ // caso n�o h� chance de ganhar ou risco de perder, joga aleat�rio
            do{
                opcao = rand() % (tam*tam) + 1;
            }while(matriz[vetL[opcao]][vetC[opcao]]!=0);
            matriz[vetL[opcao]][vetC[opcao]] = 2;
        }
    }
}

#endif // IA_H_INCLUDED
