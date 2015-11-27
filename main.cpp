//          //==============================================\\          \\
//          ||                                              ||          \\
//          ||                 JOGO DA VELHA                ||          \\
//          ||                                              ||          \\
//          ||  Desenvolvido por Andr� Luiz e Ivan Carlos   ||          \\
//          ||  Disciplina: Algoritmos e Programa��o        ||          \\
//          ||  2� per�odo                                  ||          \\
//          ||  Professora: Elisangela Maschio de Miranda   ||          \\
//          ||  UNIVALI - Universidade do Vale do Itaja�    ||          \\
//          ||                                              ||          \\
//          \\==============================================//          \\

#include <iostream>
#include <locale.h> // para localiza��o das strings, habilitar a acentua��o.
#include <windows.h> // para usar comandos do sistema, tal como CLS (limpar a tela).
#include <stdlib.h> // para usar comandos como srand, rand.
#include <time.h> // time auxilia no rand

#include "dimensaojanela.h" // para alterar a dimens�o da janela do console
#include "menu.h" // para poder chamar o menu
#include "struct_ranking.h" // para poder criar o vetor de struct

using namespace std;

int main(){
    system("color f0"); // cor do console
    DimensaoJanela(90, 30); // altera a dimens�o da janela do console
    setlocale(LC_ALL, "Portuguese_Brazil"); // para a acentua��o funcionar
    srand(time(NULL)); // para usar random
    cout.precision(3);
    int tam = 3, dificuldade = 1; // vari�veis int
    ranking top[10]; // cria o vetor top 10 da struct ranking
    menu(tam, dificuldade, top); // chama o menu
}
