#ifndef COR_H_INCLUDED
#define COR_H_INCLUDED
#include <windows.h>
using namespace std;

void cor(int cor){ // função para mudar cor do texto
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

#endif // COR_H_INCLUDED
