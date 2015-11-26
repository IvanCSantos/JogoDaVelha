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

#include "dimensaojanela.h"
#include "menu.h"
#include "struct_ranking.h"

using namespace std;

int main()
{
    system("color f0"); // cor do console
    DimensaoJanela(80, 30);
    setlocale(LC_ALL, "Portuguese_Brazil"); // para a acentuação funcionar
    srand(time(NULL)); // para usar random
    int tam = 3, dificuldade = 1; // variáveis int
    ranking ranking[10];
    menu(tam, dificuldade); // chama o menu
}
