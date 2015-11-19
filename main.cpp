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
#include <string.h> // para manipula��o das strings, usado na fun��o centralizar
#include <locale.h> // para localiza��o das strings, habilitar a acentua��o
#include <windows.h> // para usar comandos do sistema, tal como CLS (limpar a tela)
#include <stdlib.h> // para usar comandos como srand, rand
#include <time.h> // time auxilia no rand
#include "ia.h"
#include "centralizar.h"
#include "conio.h"
using namespace std;

#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define KEY_ENTER 13

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void desenhar(int matriz[5][5],int selecao[5][5], int &tam){
    gotoxy(1, 1); // limpa a tela toda vez que desenhar
    cout << "\n\n";
    for(int i = 0; i < tam; i++)
    {
        cout << "\n";
        switch(tam){ // centraliza a velha no console, mas com -x caracteres (depende do tam) para continuar centralizada mesmo ap�s preenchimento dos valores da matriz
            case 3:
                centralizar("", 5);
                break;
            case 4:
                centralizar("", 7);
                break;
            case 5:
                centralizar("", 9);
                break;
            }
        for(int j = 0; j < tam; j++)
        {
            if(j == 0){ // se for a primeira coluna, deixa um espa�o em branco para alinhamento
               cout << "";
            }
            if(j > 0 and j < tam){ // se for a parte do meio da velha, colocar barra para separar
                cout << " | ";
            }
            if(selecao[i][j]==3 and matriz[i][j]==0){
                    cout << "@";
            }
            switch(matriz[i][j]){
                case 0:
                    if(selecao[i][j]!=3){
                        cout << " "; // valor 0 = branco
                    }
                    break;
                case 1:
                    cout << "X"; // valor 1 = X
                    break;
                case 2:
                    cout << "O"; // valor 2 = O
                    break;
            }
        }
        if(i < tam-1){
            cout << "\n";
            switch(tam){
                case 3:
                    centralizar("-----------"); // separa��o de linha da velha
                    break;
                case 4:
                    centralizar("---------------"); // separa��o de linha da velha
                    break;
                case 5:
                    centralizar("-------------------"); // separa��o de linha da velha
                    break;
            }
        }
    }
    cout << "\n\n";
}

bool verificacao(int matriz[5][5], int selecao[5][5], int &tam, int &jogador, bool ia=false){
    int auxH1=0, auxH2=0, auxV1=0, auxV2=0, auxDP1=0, auxDP2=0, auxDS1=0, auxDS2=0, geral=0;
    for(int i = 0; i < tam; i++){
        auxH1=0;
        auxH2=0;
        auxV1=0;
        auxV2=0;
        auxDP1=0;
        auxDP2=0;
        auxDS1=0;
        auxDS2=0;
        // incrementa��o somas
        // verifica��o horizontal
        for(int j = 0; j < tam; j++){
            if (matriz[i][j]==1){
                auxH1++;
                geral++;
            } else if (matriz[i][j]==2){
                auxH2++;
                geral++;
            }
        // verifica��o vertical
            if (matriz[j][i]==1){
                auxV1++;
            } else if (matriz[j][i]==2){
                auxV2++;
            }
        // verifica��o diagonal principal
            if (matriz[j][j]==1){
                auxDP1++;
            } else if (matriz[j][j]==2){
                auxDP2++;
            }
        // verifica��o diagonal secund�ria
            if (matriz[j][(tam-1)-j]==1){
                auxDS1++;
            } else if (matriz[j][(tam-1)-j]==2){
                auxDS2++;
            }
        // verifica��o final
            if(auxH1==tam or auxH2==tam or auxV1==tam or auxV2==tam or auxDP1==tam or auxDP2==tam or auxDS1==tam or auxDS2==tam){
                if(ia==false){
                    desenhar(matriz, selecao, tam);
                    cout << "\n\n"; centralizar("Parab�ns ao jogador "); cout << jogador << "!" << "\n\n";
                    system("pause");
                    return true;
                } else if(ia==true) {
                    if(jogador==1){
                        desenhar(matriz, selecao, tam);
                        cout << "\n\n"; centralizar("Parab�ns ao jogador 1!\n\n");
                    }
                    if(jogador==2){
                        desenhar(matriz, selecao, tam);
                        cout << "\n\n"; centralizar("Parab�ns ao computador\n\n");
                    }
                    system("pause");
                    return true;
                }
            }
            if(geral==tam*tam){ // verifica��o velha
                desenhar(matriz, selecao, tam);
                cout << "\n\n"; centralizar("Deu velha!"); cout << "\n\n";
                system("pause");
                return true;
            }
        }
    }
}

void vet_guia(int vetL[26], int vetC[26], int &tam, int matriz[5][5]){ // fun��o para o vetor que guia no processo da entrada na matriz
    int valor=0, aux=1;
    for(int i = 1; i <= tam*tam; i++){ // vetor guia das linhas, cria um vetor conforme o tamanho, ex: 0, 0, 0, 1, 1, 1, 2, 2, 2.
        if (aux > tam){
            valor++;
            aux=1;
        }
        if (aux <= tam){
            vetL[i]=valor;
            aux++;
        }
    }

    valor=0;
    for(int i = 1; i <= tam*tam; i++){ // vetor guia das colunas, cria um vetor conforme o tamanho, ex: 0, 1, 2, 0, 1, 2, 0, 1, 2.
        if(valor==tam){
            valor=0;
        }
        if (valor < tam){
            vetC[i]=valor;
            valor++;
        }
    }
}

void entrada(int matriz[5][5], int selecao[5][5], int vetL[26], int vetC[26], int &tam, int &jogador){
    int opcao, opL=0, opC=0, c=0;
    bool jogou=false;
    system("cls");
    do {
        desenhar(matriz, selecao, tam);
        cout << "\n\n";
        centralizar("Jogador ");
        cout << jogador << "\n";
            c=0;
            switch((c=_getch())) {
            case KEY_UP:
                selecao[opL][opC]=0;
                opL--;
                break;
            case KEY_DOWN:
                selecao[opL][opC]=0;
                opL++;
                break;
            case KEY_RIGHT:
                selecao[opL][opC]=0;
                opC++;
                break;
            case KEY_LEFT:
                selecao[opL][opC]=0;
                opC--;
                break;
            case KEY_ENTER:
                if(matriz[opL][opC]==0){
                    matriz[opL][opC]=jogador;
                    jogou=true;
                }
                break;
            }
            if(opL >= tam){
                opL=tam-1;
            }
            if(opL < 0){
                opL=0;
            }
            if(opC >= tam){
                opC=tam-1;
            }
            if(opC < 0){
                opC=0;
            }
            selecao[opL][opC]=3;
            desenhar(matriz, selecao, tam);
//        centralizar("Entre com o campo desejado: ");
//        cin >> opcao;
        centralizar("");
    } while(jogou==false); // impede que seja inserido um n�mero maior do que o permitido ou que seja inserido num espa�o j� preenchido
}

void jogadorxcomputador(int matriz[5][5], int selecao[5][5], int &tam, int &dificuldade){ // fun��o que controla o jogador x computador
    bool vencer = false, computador = true;
    int jogador = 1;
    int vetL[26], vetC[26];
    vet_guia(vetL, vetC, tam, matriz); // chama a fun��o para criar o vetor guia que ajuda a manipular a matriz
    while(vencer == false){ // enquanto ningu�m vencer executa o loop de procedimentos
        jogador=1;
        desenhar(matriz, selecao, tam);
        entrada(matriz, selecao, vetL, vetC, tam, jogador); // entrada do jogador
        desenhar(matriz, selecao, tam);
        vencer = verificacao(matriz, selecao, tam, jogador, computador); // faz a verifica��o e retorna true ou false para a vari�vel vencer
        if(vencer==false){
            jogador=2;
            ia(matriz, vetL, vetC, tam, dificuldade); // fun��o que faz a jogada do computador
            Sleep(1000);
            vencer = verificacao(matriz, selecao, tam, jogador, computador); // faz a verifica��o e retorna true ou false para a vari�vel vencer
            desenhar(matriz, selecao, tam);
        }
    }
}

void jogadorxjogador(int matriz[5][5], int selecao[5][5], int &tam){ // fun��o que controla o jogador x jogador
    bool vencer = false;
    int jogador = 1;
    int vetL[26], vetC[26];
    vet_guia(vetL, vetC, tam, matriz); // chama a fun��o para criar o vetor guia que ajuda a manipular a matriz
    while(vencer == false){ // enquanto ningu�m vencer executa o loop de procedimentos
        desenhar(matriz, selecao, tam);
        entrada(matriz, selecao, vetL, vetC, tam, jogador); // entrada do jogador
        vencer = verificacao(matriz, selecao, tam, jogador); // faz a verifica��o e retorna true ou false para a vari�vel vencer
        desenhar(matriz, selecao, tam);
        if (vencer==false){ // se ningu�m venceu ainda, troca de jogador
            if(jogador==1){
                jogador = 2;
            } else {
                jogador = 1;
            }
        }
    }
}

int sair(){
    return EXIT_FAILURE; // retorna algum valor para sair do programa
}


void menu_comojogar(int &tam, int &dificuldade){ // texto de como jogar
    system("cls");
    cout << "\n";
    centralizar("Para jogar basta inserir o n�mero correspondente ao campo que voc� deseja, exemplo:"); cout << "\n\n";
    centralizar(" 1 | 2 | 3 "); cout << "\n";
    centralizar("-----------"); cout << "\n";
    centralizar(" 4 | 5 | 6 "); cout << "\n";
    centralizar("-----------"); cout << "\n";
    centralizar(" 7 | 8 | 9 "); cout << "\n\n";
    centralizar("----------------------"); cout << "\n\n";
    centralizar("  1 | 2  | 3  | 4  "); cout << "\n";
    centralizar("-------------------"); cout << "\n";
    centralizar("  5 | 6  | 7  | 8  "); cout << "\n";
    centralizar("-------------------"); cout << "\n";
    centralizar("  9 | 10 | 11 | 12 "); cout << "\n";
    centralizar("-------------------"); cout << "\n";
    centralizar(" 13 | 14 | 15 | 16 "); cout << "\n\n";
    centralizar("----------------------"); cout << "\n\n";
    system("pause");
}

void menu_tam(int &tam){
    system("cls");
    int opcao; // variavel local para armazenar a op��o escolhida
    cout << "\n";
    centralizar("Digite o n�mero do tamanho desejado:"); cout << "\n\n";
    centralizar("1. 3x3"); cout << "\n";
    centralizar("2. 4x4"); cout << "\n";
    centralizar("3. 5x5"); cout << "\n\n";
    centralizar("Op��o: ");
    cin >> opcao;
    switch(opcao) // define o tamanho da matriz com base na escolha do usu�rio
    {
        case 1:
            tam = 3;
            break;
        case 2:
            tam = 4;
            break;
        case 3:
            tam = 5;
            break;
    }
}

void menu_dificuldade(int &dificuldade){
    system("cls");
    int opcao; // variavel local para armazenar a op��o escolhida
    cout << "\n";
    centralizar("Digite o n�mero da dificuldade desejada"); cout << "\n\n";
    centralizar("1. F�cil"); cout << "\n";
    centralizar("2. Dif�cil"); cout << "\n\n";
    centralizar("Op��o: ");
    cin >> opcao;
    dificuldade = opcao; // define a dificuldade do jogo com base na escolha do usu�rio
}

void LimparMatriz(int matriz[5][5]){ // fun��o para limpar a matriz toda vez que um novo jogo come�ar
    for(int i=0; i < 5; i++){
        for(int j=0; j < 5; j++){
            matriz[i][j]=0;
        }
    }
}

void menu(int &tam, int &dificuldade, int matriz[5][5], int selecao[5][5])
{
    LimparMatriz(matriz);
    LimparMatriz(selecao);
    system("cls");
    int opcao; // variavel local para armazenar a op��o escolhida
    cout << "\n";
    centralizar("BEM-VINDO AO JOGO DA VELHA!"); cout << "\n\n";
    centralizar("Digite o n�mero da op��o desejada:"); cout << "\n\n";
    centralizar("1. Jogador vs. Computador"); cout << "\n";
    centralizar("2. Jogador vs. Jogador"); cout << "\n";
    centralizar("3. Como jogar"); cout << "\n";
    centralizar("4. Sair"); cout << "\n\n";
    centralizar("Op��o: ");
    cin >> opcao;
    switch(opcao) // redireciona para outras fun��es com base na escolha do usu�rio
    {
        case 1:
            menu_tam(tam);
            menu_dificuldade(dificuldade);
            jogadorxcomputador(matriz, selecao, tam, dificuldade);
            menu(tam, dificuldade, matriz, selecao);
            break;
        case 2:
            menu_tam(tam);
            jogadorxjogador(matriz, selecao, tam);
            menu(tam, dificuldade, matriz, selecao);
            break;
        case 3:
            menu_comojogar(tam, dificuldade);
            menu(tam, dificuldade, matriz, selecao);
            break;
        case 4:
            sair();
    }
}

int main()
{
    system("color f0");
    setlocale(LC_ALL, "Portuguese_Brazil"); // para a acentua��o funcionar
    srand (time(NULL));
    int tam = 3, dificuldade = 1, matriz[5][5]={0}, selecao[5][5]={0}; // vari�veis int
    menu(tam, dificuldade, matriz, selecao); // chama o menu
}
