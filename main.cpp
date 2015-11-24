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
#include <string.h> // para manipula��o das strings, usado na fun��o centralizar.
#include <locale.h> // para localiza��o das strings, habilitar a acentua��o.
#include <windows.h> // para usar comandos do sistema, tal como CLS (limpar a tela).
#include <stdlib.h> // para usar comandos como srand, rand.
#include <time.h> // time auxilia no rand.
#include "ia.h"
#include "centralizar.h"
#include "conio.h"
using namespace std;

enum { // enum com o c�digo das teclas
    KEY_UP      = 119
    KEY_DOWN    = 115
    KEY_LEFT    = 97
    KEY_RIGHT   = 100
    KEY_ENTER   = 13
};

enum { // enum com todas as constantes de cor simplificadas com um nome mais f�cil
    PRETO               = 0,
    AZUL_ESCURO         = FOREGROUND_BLUE,
    VERDE_ESCURO        = FOREGROUND_GREEN,
    CYAN_ESCURO         = FOREGROUND_GREEN | FOREGROUND_BLUE,
    VERMELHO_ESCURO     = FOREGROUND_RED,
    ROXO                = FOREGROUND_RED | FOREGROUND_BLUE,
    AMARELO_ESCURO      = FOREGROUND_RED | FOREGROUND_GREEN,
    CINZA_ESCURO        = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    CINZA               = FOREGROUND_INTENSITY,
    AZUL                = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    VERDE               = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    CYAN                = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    VERMELHO            = FOREGROUND_INTENSITY | FOREGROUND_RED,
    ROSA                = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    AMARELO             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    BRANCO              = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

void cor(int cor){ // fun��o para mudar cor do texto
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

void gotoxy(int x, int y){ // usado para mudar a posi��o de escrita do console
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void LimparMatriz(int matriz[5][5]){ // fun��o para limpar a matriz toda vez que um novo jogo come�ar
    for(int i=0; i < 5; i++){
        for(int j=0; j < 5; j++){
            matriz[i][j]=0;
        }
    }
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
            if(selecao[i][j]==3 and matriz[i][j]==0){ // valor 3 = posi��o selecionada - insere apenas se n�o tiver nenhum valor na matriz principal
                cor(VERDE_ESCURO); // define a cor do cursor como verde escuro
                cout << "X";
                cor(PRETO);
            }
            switch(matriz[i][j]){
                case 0:
                    if(selecao[i][j]!=3){ // se for diferente de 3 na matriz sele��o, pode inserir o espa�o em branco, se n�o teria inserido a posi��o selecionada
                        cout << " "; // valor 0 = branco
                    }
                    break;
                case 1:
                    if(selecao[i][j]==3)
                        cor(VERMELHO); // se o cursor estiver em cima do X, representa ele vermelho, indicando que n�o � poss�vel jogar em cima
                    cout << "X"; // valor 1 = X
                    break;
                case 2:
                    if(selecao[i][j]==3)
                        cor(VERMELHO); // se o cursor estiver em cima da O, representa ela vermelha, indicando que n�o � poss�vel jogar em cima
                    cout << "O"; // valor 2 = O
                    break;
            }
            cor(PRETO); // volta a cor do texto para preto
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

void entrada(int matriz[5][5], int selecao[5][5], int &tam, int &jogador){
    int opcao, opL=0, opC=0, c=0;
    bool jogou=false; // vari�vel que controla o loop de jogada
    system("cls");
    selecao[0][0]=3; // sempre que come�ar uma nova entrada, volta o cursor para a primeira posi��o
    do {
        desenhar(matriz, selecao, tam);
        cout << "\n\n";
        centralizar("Jogador ");
        cout << jogador << "\n";
            c=0;
            switch((c=_getch())) { // C ser� o c�digo da tecla pressionada
            case KEY_UP: // caso for tecla para cima (W) diminui a linha em 1
                selecao[opL][opC]=0;
                opL--;
                break;
            case KEY_DOWN: // caso for tecla para baixo (S) aumenta a linha em 1
                selecao[opL][opC]=0;
                opL++;
                break;
            case KEY_RIGHT: // caso for tecla para direita (D) aumenta a coluna em 1
                selecao[opL][opC]=0;
                opC++;
                break;
            case KEY_LEFT: // caso for tecla para a esquerda (A) diminui a coluna em 1
                selecao[opL][opC]=0;
                opC--;
                break;
            case KEY_ENTER: // caso for tecla ENTER insere a jogada na posi��o selecionada apenas se j� estiver vazia
                if(matriz[opL][opC]==0){
                    matriz[opL][opC]=jogador;
                    jogou=true;
                }
                break;
            }
            if(opL >= tam){ // impede que a posi��o passe dos limites da matriz
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
            selecao[opL][opC]=3; // insere a posi��o desejada na matriz sele��o
            desenhar(matriz, selecao, tam);
    } while(jogou==false); // repete o loop de posi��o at� que seja jogado numa posi��o
}

void jogadorxcomputador(int matriz[5][5], int selecao[5][5], int &tam, int &dificuldade){ // fun��o que controla o jogador x computador
    bool vencer = false, computador = true;
    int jogador = 1;
    int vetL[26], vetC[26];
    vet_guia(vetL, vetC, tam, matriz); // chama a fun��o para criar o vetor guia que ajuda a manipular a matriz
    while(vencer == false){ // enquanto ningu�m vencer executa o loop de procedimentos
        jogador=1;
        desenhar(matriz, selecao, tam);
        entrada(matriz, selecao, tam, jogador); // entrada do jogador
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
        entrada(matriz, selecao, tam, jogador); // entrada do jogador
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
    cor(VERDE_ESCURO);
    centralizar("Como jogar:"); cout << "\n\n";
    cor(PRETO);
    centralizar("Controle do cursor: W, A, S, D"); cout << "\n\n";
    centralizar("Inserir jogada: ENTER"); cout << "\n\n";
    system("pause");
}

void menu_tam(int &tam){
    system("cls");
    int opcao; // variavel local para armazenar a op��o escolhida
    cout << "\n";
    cor(VERDE_ESCURO);
    centralizar("Digite o n�mero do tamanho desejado:"); cout << "\n\n";
    cor(PRETO);
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
    cor(VERDE_ESCURO);
    centralizar("Digite o n�mero da dificuldade desejada"); cout << "\n\n";
    cor(PRETO);
    centralizar("1. F�cil"); cout << "\n";
    centralizar("2. Dif�cil"); cout << "\n\n";
    centralizar("Op��o: ");
    cin >> opcao;
    dificuldade = opcao; // define a dificuldade do jogo com base na escolha do usu�rio
}

void menu(int &tam, int &dificuldade, int matriz[5][5], int selecao[5][5])
{
    LimparMatriz(matriz); // toda vez que voltar ao menu limpa as matrizes
    LimparMatriz(selecao);
    system("cls");
    int opcao; // variavel local para armazenar a op��o escolhida
    cout << "\n";
    cor(VERDE_ESCURO);
    centralizar("BEM-VINDO AO JOGO DA VELHA!"); cout << "\n\n";
    cor(PRETO);
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
    system("color f0"); // cor do console
    setlocale(LC_ALL, "Portuguese_Brazil"); // para a acentua��o funcionar
    srand(time(NULL)); // para usar random
    int tam = 3, dificuldade = 1, matriz[5][5]={0}, selecao[5][5]={0}; // vari�veis int
    menu(tam, dificuldade, matriz, selecao); // chama o menu
}
