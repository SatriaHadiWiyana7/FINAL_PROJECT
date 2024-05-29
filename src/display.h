#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h> //printf
#include <conio.h>
#include <mmsystem.h>

using namespace std;

void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void loading()
{
    system("color f0");
    system("cls");
    printf("\e[?251]");

    SetConsoleCP(437);
    SetConsoleOutputCP(437);

    int bar1 = 177, bar2 = 219;

    gotoxy(55, 13);
    cout << "Loading...";

    for (int i = 47; i < 73; i++)
    {
        gotoxy(i, 15);
        cout << (char)bar1;
    }

    for (int i = 47; i < 73; i++)
    {
        gotoxy(i, 15);
        cout << (char)bar2;
        Sleep(150);
    }

    system("cls");
}

void title()
{
    PlaySound(TEXT("backsong.mp3"), NULL, SND_SYNC);

    gotoxy(12, 3);
    cout << "          ________   _________  ___    ___  ___  ___   __________  ___________  __________    " << endl;
    gotoxy(12, 4);
    cout << "         /  __   /  /  ___   / /   |  /  / /  / /  /  /  _______/ /  _____   / /  _______/    " << endl;
    gotoxy(12, 5);
    cout << "        /  /_/  /  /  /  /  / /    | /  / /  /_/  /  /  /______  /  /    /  / /  /______      " << endl;
    gotoxy(12, 6);
    cout << "       /  ___  <  /  /__/  / /  /| |/  / /  _   <   /______   / /  /    /  / /______   /      " << endl;
    gotoxy(12, 7);
    cout << "      /  /__/  / /  ___   / /  / |    / /  / |  |  _______/  / /  /____/  / _______/  /       " << endl;
    gotoxy(12, 8);
    cout << "     /________/ /__/  /__/ /__/  |___/ /__/  |__| /_________/ /__________/ /_________/        " << endl;
    gotoxy(12, 9);
    cout << "                                                                                              " << endl;
    gotoxy(12, 10);
    cout << "                                      --Bank Soal Siswa--                                     " << endl;
}