#ifndef MOSTRAR_RANKING_H_INCLUDED
#define MOSTRAR_RANKING_H_INCLUDED
#include <conio.h>

#include "struct_ranking.h"
#include "cores.h"
#include "cor.h"
#include "centralizar.h"


using namespace std;

void MostrarRanking(ranking top[10], int ordenacao[10], int num){
    system("cls");
    cor(VERDE_ESCURO);
    cout << "\n\n\n";
    centralizar("RANKING TOP 10");
    cout << "\n\n\n";
    cout << "\tPOSIÇÃO\t\tNOME\t\tTEMPO\t\tMODO DE JOGO\n\n";
    cor(PRETO);
    for(int i=0; i < num; i++){
        if(top[ordenacao[i]].tempo < 10)
            cout.precision(3);
        else
            cout.precision(4);
        gotoxy(9,i+9);
        cout << i+1;
        gotoxy(25,i+9);
        cout << top[ordenacao[i]].nome;
        gotoxy(41,i+9);
        cout << top[ordenacao[i]].tempo;
        gotoxy(57,i+9);
        cout << ((top[ordenacao[i]].modo==0)? "Jogador X Computador" : "Jogador X Jogador") << "\n";
    }
    cout << "\n\n\n";
    centralizar("Pressione qualquer tecla para voltar");
    _getch();
}

#endif // MOSTRAR_RANKING_H_INCLUDED
