#ifndef DIMENSAOJANELA_H_INCLUDED
#define DIMENSAOJANELA_H_INCLUDED
#include <windows.h>
using namespace std;

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


#endif // DIMENSAOJANELA_H_INCLUDED
