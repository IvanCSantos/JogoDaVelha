//          //==============================================\\          \\
//          ||                                              ||          \\
//          ||                 JOGO DA VELHA                ||          \\
//          ||                                              ||          \\
//          ||  Desenvolvido por André Luiz e Ivan Carlos   ||          \\
//          ||  Disciplina: Algoritmos e Programação        ||          \\
//          ||  2º período                                  ||          \\
//          ||  Professora: Elisangela Maschio de Miranda   ||          \\
//          ||  UNIVALI - Universidade do Vale do Itajaí    ||          \\
//          ||                                              ||          \\
//          \\==============================================//          \\

#include <iostream>
#include <locale.h> // para localização das strings, habilitar a acentuação.
#include <windows.h> // para usar comandos do sistema, tal como CLS (limpar a tela).
#include <stdlib.h> // para usar comandos como srand, rand.
#include <time.h> // time auxilia no rand

#include "dimensaojanela.h" // para alterar a dimensão da janela do console
#include "menu.h" // para poder chamar o menu
#include "struct_ranking.h" // para poder criar o vetor de struct

using namespace std;

int main(){
    system("color f0"); // cor do console
    DimensaoJanela(90, 30); // altera a dimensão da janela do console
    setlocale(LC_ALL, "Portuguese_Brazil"); // para a acentuação funcionar
    srand(time(NULL)); // para usar random
    cout.precision(3);
    int tam = 3, dificuldade = 1; // variáveis int
    ranking top[10]; // cria o vetor top 10 da struct ranking
    menu(tam, dificuldade, top); // chama o menu
}
