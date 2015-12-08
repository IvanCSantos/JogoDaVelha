#ifndef INSERIR_RANKING_H_INCLUDED
#define INSERIR_RANKING_H_INCLUDED

using namespace std;

void InserirRanking(string jogador, float tempo, int modo, int &num, ranking top[10]){
    if(num < 10){
        top[num].nome=jogador;
        top[num].tempo=tempo;
        top[num].modo=modo;
        num++;
    }else if(num == 10){
        int indice, maior=0;
        for(int i=0; i < num; i++){
            if(top[i].tempo > maior){
                indice=i;
                maior=top[i].tempo;
            }
        }
        if(tempo < maior){
            top[indice].nome=jogador;
            top[indice].tempo=tempo;
            top[indice].modo=modo;
        }else{
            centralizar("Jogador não inserido no ranking, tempo muito grande!");
            cout << "\n\n";
        }
    }
}

#endif // INSERIR_RANKING_H_INCLUDED
