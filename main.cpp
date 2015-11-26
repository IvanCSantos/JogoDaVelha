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

#include "dimensaojanela.h"
#include "menu.h"
#include "struct_ranking.h"

using namespace std;

int main()
{
    system("color f0"); // cor do console
    DimensaoJanela(80, 30);
    setlocale(LC_ALL, "Portuguese_Brazil"); // para a acentua��o funcionar
    srand(time(NULL)); // para usar random
    int tam = 3, dificuldade = 1; // vari�veis int
    ranking ranking[10];
    menu(tam, dificuldade); // chama o menu
}
