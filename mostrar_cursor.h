#ifndef MOSTRAR_CURSOR_H_INCLUDED
#define MOSTRAR_CURSOR_H_INCLUDED
#include <windows.h>
using namespace std;

void mostrar_cursor(bool ativar){
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = ativar;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}

#endif // MOSTRAR_CURSOR_H_INCLUDED
