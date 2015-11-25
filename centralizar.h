#ifndef CENTRALIZAR_H_INCLUDED
#define CENTRALIZAR_H_INCLUDED
#include <string.h>
using namespace std;

void centralizar(char* c, int menos = 0) // função para centralizar uma string no console
{
    int l=strlen(c); // tamanho da string
    int pos = (int)((80-l)/2);
    for(int i = 0; i < pos-menos; i++){ // 'menos' serve para reduzir a centralização
        cout << " "; // espaços necessários para centralizar o conteúdo
    }
    cout << c;
}
#endif // CENTRALIZAR_H_INCLUDED