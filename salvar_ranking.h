#ifndef SALVAR_RANKING_H_INCLUDED
#define SALVAR_RANKING_H_INCLUDED
#include <fstream>

using namespace std;

void SalvarRanking(int &num, ranking top[10]){
    char sep=';';
    bool primeira=true;
    int i=0, controle=0;
    ofstream txt;
    txt.open("ranking.txt", ofstream::out | ofstream::trunc);
    txt << num << "\n";
    for(int i=0; i < num; i++){
        txt << sep << top[i].nome << sep << top[i].tempo << sep << top[i].modo << "\n";
    }
    txt.close();
}

#endif // SALVAR_RANKING_H_INCLUDED
