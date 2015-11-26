#ifndef CARREGAR_RANKING_H_INCLUDED
#define CARREGAR_RANKING_H_INCLUDED

#include <fstream>

using namespace std;

void CarregarRanking(ranking ranking[10], int &num){
    char sep=';';
    bool primeira=true;
    int i=0, controle=0;
    fstream txt("ranking.txt");
    for(string linha; getline(txt, linha, sep);){
        if(i>3){
            i=1;
            controle++;
        }
        if(primeira==true){
            num=atoi(linha.c_str());
            primeira=false;
        }
        if(primeira==false and i > 0){
            switch(i){
            case 1:
                ranking[controle].nome=linha;
                break;
            case 2:
                ranking[controle].tempo=atof(linha.c_str());
                break;
            case 3:
                ranking[controle].modo=atoi(linha.c_str());
            }
        }
        i++;
    }
}

#endif // CARREGAR_RANKING_H_INCLUDED
