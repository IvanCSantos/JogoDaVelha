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
#include <string.h> // para manipulação das strings, usado na função centralizar.
#include <locale.h> // para localização das strings, habilitar a acentuação.
#include <windows.h> // para usar comandos do sistema, tal como CLS (limpar a tela).
#include <stdlib.h> // para usar comandos como srand, rand.
#include <time.h> // time auxilia no rand
#include "ia.h"
#include "centralizar.h"
#include "conio.h"
using namespace std;

enum { // enum com o código das teclas
    KEY_UP      = 72,
    KEY_DOWN    = 80,
    KEY_LEFT    = 75,
    KEY_RIGHT   = 77,
    KEY_ENTER   = 13,
};

enum { // enum com todas as constantes de cor simplificadas com um nome mais fácil
    PRETO, AZUL_ESCURO, VERDE_ESCURO, CYAN_ESCURO, VERMELHO_ESCURO, ROXO, AMARELO_ESCURO, CINZA, CINZA_ESCURO, AZUL, VERDE, AZUL_CLARO, VERMELHO, ROSA, AMARELO, BRANCO,
};

void cor(int cor){ // função para mudar cor do texto
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

void gotoxy(int x, int y){ // usado para mudar a posição de escrita do console
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void LimparMatriz(int **matriz, int &tam){ // função para limpar a matriz toda vez que um novo jogo começar
    for(int i=0; i < tam; i++){
        for(int j=0; j < tam; j++){
            matriz[i][j]=0;
        }
    }
}

void desenhar(int **matriz, int **selecao, int &tam){
    int reducao=(tam*2)-1;
    gotoxy(1, 1); // limpa a tela toda vez que desenhar
    cout << "\n\n";
    for(int i = 0; i < tam; i++)
    {
        cout << "\n";
        centralizar("", reducao);
        for(int j = 0; j < tam; j++)
        {
            if(j == 0){ // se for a primeira coluna, deixa um espaço em branco para alinhamento
               cout << "";
            }
            if(j > 0 and j < tam){ // se for a parte do meio da velha, colocar barra para separar
                cout << " | ";
            }
            if(selecao[i][j]==3 and matriz[i][j]==0){ // valor 3 = posição selecionada - insere apenas se não tiver nenhum valor na matriz principal
                cor(VERDE_ESCURO); // define a cor do cursor como verde escuro
                cout << "X";
                cor(PRETO);
            }
            switch(matriz[i][j]){
                case 0:
                    if(selecao[i][j]!=3){ // se for diferente de 3 na matriz seleção, pode inserir o espaço em branco, se não teria inserido a posição selecionada
                        cout << " "; // valor 0 = branco
                    }
                    break;
                case 1:
                    if(selecao[i][j]==3)
                        cor(VERMELHO); // se o cursor estiver em cima do X, representa ele vermelho, indicando que não é possível jogar em cima
                    cout << "X"; // valor 1 = X
                    break;
                case 2:
                    if(selecao[i][j]==3)
                        cor(VERMELHO); // se o cursor estiver em cima da O, representa ela vermelha, indicando que não é possível jogar em cima
                    cout << "O"; // valor 2 = O
                    break;
            }
            cor(PRETO); // volta a cor do texto para preto
        }
        if(i < tam-1){
            cout << "\n";
            switch(tam){
                case 3:
                    centralizar("-----------"); // separação de linha da velha
                    break;
                case 4:
                    centralizar("---------------"); // separação de linha da velha
                    break;
                case 5:
                    centralizar("-------------------"); // separação de linha da velha
                    break;
                case 6:
                    centralizar("-----------------------"); // separação de linha da velha
                    break;
                case 7:
                    centralizar("---------------------------"); // separação de linha da velha
                    break;
                case 8:
                    centralizar("-------------------------------"); // separação de linha da velha
                    break;
                case 9:
                    centralizar("-----------------------------------"); // separação de linha da velha
                    break;
                case 10:
                    centralizar("---------------------------------------"); // separação de linha da velha
                    break;
            }
        }
    }
    cout << "\n\n";
}

bool verificacao(int **matriz, int **selecao, int &tam, int &jogador, bool ia=false){
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
        // incrementação somas
        // verificação horizontal
        for(int j = 0; j < tam; j++){
            if (matriz[i][j]==1){
                auxH1++;
                geral++;
            } else if (matriz[i][j]==2){
                auxH2++;
                geral++;
            }
        // verificação vertical
            if (matriz[j][i]==1){
                auxV1++;
            } else if (matriz[j][i]==2){
                auxV2++;
            }
        // verificação diagonal principal
            if (matriz[j][j]==1){
                auxDP1++;
            } else if (matriz[j][j]==2){
                auxDP2++;
            }
        // verificação diagonal secundária
            if (matriz[j][(tam-1)-j]==1){
                auxDS1++;
            } else if (matriz[j][(tam-1)-j]==2){
                auxDS2++;
            }
        // verificação final
            if(auxH1==tam or auxH2==tam or auxV1==tam or auxV2==tam or auxDP1==tam or auxDP2==tam or auxDS1==tam or auxDS2==tam){
                if(ia==false){
                    desenhar(matriz, selecao, tam);
                    cout << "\n\n"; centralizar("Parabéns ao jogador "); cout << jogador << "!" << "\n\n";
                    system("pause");
                    return true;
                } else if(ia==true) {
                    if(jogador==1){
                        desenhar(matriz, selecao, tam);
                        cout << "\n\n"; centralizar("Parabéns ao jogador 1!\n\n");
                    }
                    if(jogador==2){
                        desenhar(matriz, selecao, tam);
                        cout << "\n\n"; centralizar("Parabéns ao computador\n\n");
                    }
                    system("pause");
                    return true;
                }
            }
            if(geral==tam*tam){ // verificação velha
                desenhar(matriz, selecao, tam);
                cout << "\n\n"; centralizar("Deu velha!"); cout << "\n\n";
                system("pause");
                return true;
            }
        }
    }
}

void vet_guia(int vetL[101], int vetC[101], int &tam, int **matriz){ // função para o vetor que guia no processo da entrada na matriz
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

void entrada(int **matriz, int **selecao, int &tam, int &jogador){
    int opcao, opL=0, opC=0, c=0;
    bool jogou=false; // variável que controla o loop de jogada
    system("cls");
    LimparMatriz(selecao, tam);
    selecao[0][0]=3; // sempre que começar uma nova entrada, volta o cursor para a primeira posição
    do {
        desenhar(matriz, selecao, tam);
        cout << "\n\n";
        centralizar("Jogador ");
        cout << jogador << "\n";
            c=0;
            switch((c=_getch())) { // C será o código da tecla pressionada
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
            case KEY_ENTER: // caso for tecla ENTER insere a jogada na posição selecionada apenas se já estiver vazia
                if(matriz[opL][opC]==0){
                    matriz[opL][opC]=jogador;
                    jogou=true;
                }
                break;
            }
            if(opL >= tam){ // impede que a posição passe dos limites da matriz
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
            selecao[opL][opC]=3; // insere a posição desejada na matriz seleção
            desenhar(matriz, selecao, tam);
    } while(jogou==false); // repete o loop de posição até que seja jogado numa posição
}

void jogadorxcomputador(int **matriz, int **selecao, int &tam, int &dificuldade){ // função que controla o jogador x computador
    bool vencer = false, computador = true;
    int jogador = 1;
    int vetL[101], vetC[101];
    vet_guia(vetL, vetC, tam, matriz); // chama a função para criar o vetor guia que ajuda a manipular a matriz
    while(vencer == false){ // enquanto ninguém vencer executa o loop de procedimentos
        jogador=1;
        desenhar(matriz, selecao, tam);
        entrada(matriz, selecao, tam, jogador); // entrada do jogador
        desenhar(matriz, selecao, tam);
        vencer = verificacao(matriz, selecao, tam, jogador, computador); // faz a verificação e retorna true ou false para a variável vencer
        if(vencer==false){
            jogador=2;
            ia(matriz, vetL, vetC, tam, dificuldade); // função que faz a jogada do computador
            Sleep(1000);
            vencer = verificacao(matriz, selecao, tam, jogador, computador); // faz a verificação e retorna true ou false para a variável vencer
            desenhar(matriz, selecao, tam);
        }
    }
}

void jogadorxjogador(int **matriz, int **selecao, int &tam){ // função que controla o jogador x jogador
    bool vencer = false;
    int jogador = 1;
    int vetL[101], vetC[101];
    vet_guia(vetL, vetC, tam, matriz); // chama a função para criar o vetor guia que ajuda a manipular a matriz
    while(vencer == false){ // enquanto ninguém vencer executa o loop de procedimentos
        desenhar(matriz, selecao, tam);
        entrada(matriz, selecao, tam, jogador); // entrada do jogador
        vencer = verificacao(matriz, selecao, tam, jogador); // faz a verificação e retorna true ou false para a variável vencer
        desenhar(matriz, selecao, tam);
        if (vencer==false){ // se ninguém venceu ainda, troca de jogador
            if(jogador==1){
                jogador = 2;
            } else {
                jogador = 1;
            }
        }
    }
}

int** DeletarMatriz(int **matriz){
    delete matriz[0];
    delete matriz;
}

int** CriarMatriz(int &tam){
    int **matriz = new int*[tam];
    matriz[0] = new int [tam*tam];

    for (int i=1; i<tam; i++)
        matriz[i] = matriz[i-1]+tam;

    for (int i=0; i<tam; i++)
        for (int j=0; j<tam; j++)
            matriz[i][j] = i+j;
    return matriz;
}

int sair(){
    return EXIT_FAILURE; // retorna algum valor para sair do programa
}


void menu_comojogar(int &tam, int &dificuldade){ // texto de como jogar
    system("cls");
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Como jogar:"); cout << "\n\n";
    cor(PRETO);
    centralizar("Controle do cursor: setas do teclado"); cout << "\n\n";
    centralizar("Inserir jogada: ENTER"); cout << "\n\n";
    system("pause");
}

void menu_tam(int &tam){
    system("cls");
    int opcao; // variavel local para armazenar a opção escolhida
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Digite o número do tamanho desejado (de 3 à 10):"); cout << "\n\n";
    cor(PRETO);
    centralizar("Tamanho: ", 1);
    cin >> tam; // define o tamanho da matriz com base na escolha do usuário
    if(tam < 3 or tam > 10)
        menu_tam(tam);
}

void menu_dificuldade(int &dificuldade){
    system("cls");
    int opcao; // variavel local para armazenar a opção escolhida
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("Digite o número da dificuldade desejada"); cout << "\n\n";
    cor(PRETO);
    centralizar("1. Fácil"); cout << "\n";
    centralizar("2. Difícil"); cout << "\n\n";
    centralizar("Opção: ", 1);
    cin >> opcao;
    if(opcao < 1 or opcao > 2)
        menu_dificuldade(dificuldade);
    dificuldade = opcao; // define a dificuldade do jogo com base na escolha do usuário
}

void menu(int &tam, int &dificuldade){
    system("cls");
    int opcao; // variavel local para armazenar a opção escolhida
    bool saiu=false;
    cout << "\n\n\n";
    cor(VERDE_ESCURO);
    centralizar("BEM-VINDO AO JOGO DA VELHA!"); cout << "\n\n";
    cor(PRETO);
    centralizar("Digite o número da opção desejada:"); cout << "\n\n";
    centralizar("1. Jogador vs. Computador"); cout << "\n";
    centralizar("2. Jogador vs. Jogador"); cout << "\n";
    centralizar("3. Como jogar"); cout << "\n";
    centralizar("4. Sair"); cout << "\n\n";
    centralizar("Opção: ", 1);
    cin >> opcao;
    if(opcao < 1 or opcao > 4)
        menu(tam, dificuldade);
    if(opcao==4 or opcao==3)
        saiu=true;
    if(saiu==false)
        menu_tam(tam);
    int** matriz = CriarMatriz(tam);
    int** selecao = CriarMatriz(tam);
    LimparMatriz(matriz, tam); // toda vez que voltar ao menu limpa as matrizes
    LimparMatriz(selecao, tam);
    switch(opcao) // redireciona para outras funções com base na escolha do usuário
    {
        case 1:
            menu_dificuldade(dificuldade);
            jogadorxcomputador(matriz, selecao, tam, dificuldade);
            DeletarMatriz(matriz);
            DeletarMatriz(selecao);
            menu(tam, dificuldade);
            break;
        case 2:
            jogadorxjogador(matriz, selecao, tam);
            DeletarMatriz(matriz);
            DeletarMatriz(selecao);
            menu(tam, dificuldade);
            break;
        case 3:
            menu_comojogar(tam, dificuldade);
            menu(tam, dificuldade);
            break;
        case 4:
            sair();
            break;
    }
}

bool DimensaoJanela(int largura, int altura)
    {
    _COORD coord;
    coord.X = largura;
    coord.Y = altura;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = altura - 1;
    Rect.Right = largura - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (Handle == NULL)
        {
        cout << GetLastError();
        return FALSE;
        }

    if(!SetConsoleScreenBufferSize(Handle, coord))
        {
        cout << GetLastError();
        return FALSE;
        }

    if(!SetConsoleWindowInfo(Handle, TRUE, &Rect))
        {
        cout << GetLastError();
        return FALSE;
        }
    return TRUE;
}

int main()
{
    system("color f0"); // cor do console
    DimensaoJanela(80, 30);
    setlocale(LC_ALL, "Portuguese_Brazil"); // para a acentuação funcionar
    srand(time(NULL)); // para usar random
    int tam = 3, dificuldade = 1; // variáveis int
    menu(tam, dificuldade); // chama o menu
}
