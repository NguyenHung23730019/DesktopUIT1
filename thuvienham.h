#pragma once // tránh xung đột thư viện
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>

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


void showCur(bool type_num)
{
    // 0 : an -- 1: mo -- 2: normal
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, type_num};
    SetConsoleCursorInfo(handle, &cursor);
}
