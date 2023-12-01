#pragma once // tránh xung đột thư viện
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>

#define KEY_NONE -1

int whereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        return csbi.dwCursorPosition.X;
    }
    return -1;
}

int whereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        return csbi.dwCursorPosition.Y;
    }
    return -1;
}

void gotoXY(SHORT x, SHORT y)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cursor_an_Pos = {x, y};
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

    GetConsoleScreenBufferInfo(hConsoleOutput, &screenBufferInfo);

    WORD wAttr = screenBufferInfo.wAttributes;
    color &= 0x000f;
    wAttr &= 0xfff0;
    wAttr |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttr);
}

void textcolor(int x)
{
    HANDLE backcolor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(backcolor, x);
}

void showCur(bool type_num)
{
    // 0 : an -- 1: mo -- 2: normal
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, type_num};
    SetConsoleCursorInfo(handle, &cursor);
}

int inputKey()
{
    if (_kbhit())
    {
        int key = _getch();

        if (key == 224)
        {
            key = _getch();
            return key + 1000;
        }
        return key;
    }
    else
    {
        return KEY_NONE;
    }
    return KEY_NONE;
}