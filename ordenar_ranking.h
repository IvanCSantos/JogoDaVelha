#ifndef ORDENAR_RANKING_H_INCLUDED
#define ORDENAR_RANKING_H_INCLUDED

using namespace std;

void OrdenarRanking(ranking ranking[10], int ordenacao[10], int &num){
    for(int i=0; i < num; i++){
        ordenacao[i]=i;
    }
    int aux;
    for(int j=0; j <= num; j++){
        for(int i=0; i < num-1; i++){
            if(ranking[ordenacao[i]].tempo > ranking[ordenacao[i+1]].tempo){
                aux=ordenacao[i+1];
                ordenacao[i+1]=ordenacao[i];
                ordenacao[i]=aux;
            }
        }
    }
}

#endif // ORDENAR_RANKING_H_INCLUDED
