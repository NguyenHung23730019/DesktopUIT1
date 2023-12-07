#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <stdio.h>

using namespace std;

struct Point
{
    int x, y;
};

#define MAX 500
// Do dai khung:
int x_min = 5;
int x_max = 75;
int y_min = 7;
int y_max = 30;

// Do dai ran:
int DoDai = 4;

// Huong mac dinh:
int huong = 2;

// Diem khoi tao:
int diem = 0;

Point diemBatDau = {(x_min + x_max) / 3, (y_min + y_max) / 2};
Point moi = {-100, 0};

//===================
void gotoXY(SHORT, SHORT);
void SetColor(WORD);
void showCur(bool);

void khoi_tao_game();
void play_game();
void ve_tuong();
void ve_huong_dan();
void tao_diem();
bool kt_cham_than();
int soNgauNhien(int, int);

class CONRAN
{
public:
    Point thanRan[MAX];

    CONRAN()
    {
        for (int i = 0; i < DoDai; i++)
        {
            thanRan[i].x = diemBatDau.x--;
            thanRan[i].y = diemBatDau.y;
        }
    }

    void VeRan()
    {
        SetColor(6);
        for (int i = 0; i < DoDai; i++)
        {
            gotoXY(thanRan[i].x, thanRan[i].y);
            if (i == 0)
            {
                switch (huong)
                {
                case 0:
                    cout << "<";
                    break;
                case 1:
                    cout << "V";
                    break;
                case 2:
                    cout << ">";
                    break;
                case 3:
                    cout << "^";
                    break;
                default:
                    break;
                }
            }
            else
            {
                gotoXY(thanRan[i].x, thanRan[i].y);
                cout << "O";
            }
        }
        gotoXY(thanRan[DoDai].x, thanRan[DoDai].y);
        cout << " ";
    }

    void dieu_khien_huong()
    {
        if (_kbhit())
        {
            char pressKey = _getch();
            if (pressKey == -32)
            {
                pressKey = _getch();
            }
            if ((pressKey == 'a' || pressKey == 'A' || pressKey == 75) && huong != 2)
            {
                huong = 0;
            }
            else if ((pressKey == 's' || pressKey == 'S' || pressKey == 80) && huong != 3)
            {
                huong = 1;
            }
            else if ((pressKey == 'd' || pressKey == 'D' || pressKey == 77) && huong != 0)
            {
                huong = 2;
            }
            else if ((pressKey == 'w' || pressKey == 'W' || pressKey == 72) && huong != 1)
            {
                huong = 3;
            }
        }
    }

    void di_chuyen()
    {
        switch (huong)
        {
        case 0:
            // a: trai
            for (int i = DoDai; i > 0; i--)
            {
                thanRan[i] = thanRan[i - 1];
            }
            thanRan[0].x -= 1;
            break;
        case 1:
            // s: xuong
            for (int i = DoDai; i > 0; i--)
            {
                thanRan[i] = thanRan[i - 1];
            }
            thanRan[0].y += 1;
            break;
        case 2:
            // d: phai
            for (int i = DoDai; i > 0; i--)
            {
                thanRan[i] = thanRan[i - 1];
            }
            thanRan[0].x += 1;
            break;
        case 3:
            // w: len
            for (int i = DoDai; i > 0; i--)
            {
                thanRan[i] = thanRan[i - 1];
            }
            thanRan[0].y -= 1;
            break;

        default:
            break;
        }
    }

    void tao_moi()
    {
        if (moi.x == -100)
        {
            bool check_moi = false;

            do
            {
                moi.x = soNgauNhien(x_min + 1, x_max - 1);
                moi.y = soNgauNhien(y_min + 1, y_max - 1);

                for (int i = 0; i < DoDai; i++)
                {
                    if (thanRan[i].x == moi.x && thanRan[i].y == moi.y)
                    {
                        check_moi = true;
                        break;
                    }
                }
            } while (check_moi);

            gotoXY(moi.x, moi.y);
            SetColor(10);
            cout << "X";
        }
    }

    void cong_diem()
    {
        SetColor(10);
        gotoXY(x_min + 3, y_min - 1);
        cout << "Diem: " << diem;
    }

    void kt_cham_tuong()
    {
        if (thanRan[0].x >= x_max)
        {
            thanRan[0].x = x_min + 1;
        }
        else if (thanRan[0].x <= x_min)
        {
            thanRan[0].x = x_max - 1;
        }

        if (thanRan[0].y >= y_max)
        {
            thanRan[0].y = y_min + 1;
        }
        else if (thanRan[0].y <= y_min)
        {
            thanRan[0].y = y_max - 1;
        }
    }

    void kt_cham_than()
    {
        // Dang xu ly
    }
    void tang_do_dai()
    {
        if (thanRan[0].x == moi.x && thanRan[0].y == moi.y && DoDai < MAX - 5)
        {
            diem++;
            DoDai++;
            moi.x = -100;
        }
    }
};

CONRAN conRan;

//====MAIN: START============================================
int main()
{
    srand(time(NULL));
    system("cls");
    khoi_tao_game();
    while (1)
    {
        play_game();
        Sleep(300);
    }
    _getch();
    return 0;
}
//====MAIN: END============================================

void khoi_tao_game()
{
    showCur(0); // Ẩn con trỏ chuột
    ve_tuong();
    ve_huong_dan();
    // tao_ret();
    conRan.VeRan();
}

void play_game()
{
    conRan.tao_moi();
    conRan.cong_diem();
    conRan.tang_do_dai();
    conRan.kt_cham_tuong();
    conRan.VeRan();
    conRan.dieu_khien_huong();
    conRan.di_chuyen();
}

void ve_tuong()
{
    string strNgang = "-";
    string strGoc = "O";
    string strDoc = "|";

    for (int x = x_min; x <= x_max; x++)
    {
        for (int y = y_min; y <= y_max; y++)
        {
            if ((x == x_min && y == y_min) ||
                (x == x_min && y == y_max) ||
                (x == x_max && y == y_min) ||
                (x == x_max && y == y_max))
            {
                gotoXY(x, y);
                cout << strGoc;
            }
            else if (x == x_min || x == x_max)
            {
                gotoXY(x, y);
                cout << strDoc;
            }
            else if (y == y_min || y == y_max)
            {
                gotoXY(x, y);
                cout << strNgang;
            }
        }
    }
}

void ve_huong_dan(){
        int can_phai_1 = 32;
        int can_phai_2 = 32;
        int can_phai_3 = 8;
        int dong_1 = 4;
        int dong_2 = 3;
        int dong_3 = 2;
        int dong_4 = 1;
        SetColor(6);
        gotoXY(x_max - can_phai_2, y_min - dong_2);
        cout << "W: Len";
        gotoXY(x_max - can_phai_2, y_min - dong_3);
        cout << "D: Xuong";
        gotoXY(x_max - can_phai_1, y_min - dong_4);
        cout << "(Co the di chuyen bang MUI TEN)";
        gotoXY(x_max - can_phai_2, y_min - dong_1);
        cout << "Space: Pause/Reset";
        gotoXY(x_max - can_phai_3, y_min - dong_2);
        cout << "F: Phai";
        gotoXY(x_max - can_phai_3, y_min - dong_3);
        cout << "A: Trai";
}

int soNgauNhien(int min, int max)
{
    int random;
    random = rand() % (max - min + 1) + min;
    return random;
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

void showCur(bool type_num)
{
    // 0 : an -- 1: mo -- 2: normal
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, type_num};
    SetConsoleCursorInfo(handle, &cursor);
}