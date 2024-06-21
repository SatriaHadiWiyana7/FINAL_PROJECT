#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h> //printf
#include <conio.h>
#include <mmsystem.h>

using namespace std;

void gotoxyG(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

int AlertG(string Prompt="", string Title="",UINT BtnLst=MB_OK)
{
    return MessageBox(nullptr,Prompt.c_str(),Title.c_str(),BtnLst);
}

void titleG()
{
    gotoxyG(12, 3);
    cout << "          ________   _________  ___    ___  ___  ___   __________  ___________  __________    " << endl;
    gotoxyG(12, 4);
    cout << "         /  __   /  /  ___   / /   |  /  / /  / /  /  /  _______/ /  _____   / /  _______/    " << endl;
    gotoxyG(12, 5);
    cout << "        /  /_/  /  /  /  /  / /    | /  / /  /_/  /  /  /______  /  /    /  / /  /______      " << endl;
    gotoxyG(12, 6);
    cout << "       /  ___  <  /  /__/  / /  /| |/  / /  _   <   /______   / /  /    /  / /______   /      " << endl;
    gotoxyG(12, 7);
    cout << "      /  /__/  / /  ___   / /  / |    / /  / |  |  _______/  / /  /____/  / _______/  /       " << endl;
    gotoxyG(12, 8);
    cout << "     /________/ /__/  /__/ /__/  |___/ /__/  |__| /_________/ /__________/ /_________/        " << endl;
    gotoxyG(12, 9);
    cout << "                                                                                              " << endl;
    gotoxyG(12, 10);
    cout << "                                      --Bank Soal Siswa--                                     " << endl;
}

void dis_searchmodplayer(){
	gotoxyG(35,15);
    cout << "+----------------------------------------------------+";
    gotoxyG(35,16);
	cout << "|                                                    |";
    gotoxyG(35,17);
	cout << "+----------------------------------------------------+";
}

void dis_delplayerG(){
	gotoxyG(35,15);
    cout << "+----------------------------------------------------+";
    gotoxyG(35,16);
	cout << "|                                                    |";
    gotoxyG(35,17);
	cout << "+----------------------------------------------------+";
}

void dis_modifyPlayer() {
	gotoxyG(38, 14);
	cout << "--------------= M O D I F Y =--------------";
	for (int i = 1; i <= 5 ; i++) {
		gotoxyG(38, 14+i);
		cout << "|                                         |";
	}
	gotoxyG(38, 20);
	cout << "-------------------------------------------";
}

void dis_modifyPlayerSelect() {
	gotoxyG(38, 15);
	cout << "--------------= M O D I F Y =--------------";
	for (int i = 1; i <= 3 ; i++) {
		gotoxyG(38, 15+i);
		cout << "|                                         |";
	}
	gotoxyG(38, 19);
	cout << "-------------------------------------------";
}
