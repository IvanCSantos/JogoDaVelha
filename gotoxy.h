#ifndef GOTOXY_H_INCLUDED
#define GOTOXY_H_INCLUDED
#include <windows.h>
using namespace std;

void gotoxy(int x, int y){ // usado para mudar a posição de escrita do console
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

#endif // GOTOXY_H_INCLUDED
