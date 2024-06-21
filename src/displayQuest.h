#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h> //printf
#include <conio.h>
#include <mmsystem.h>

using namespace std;

void gotoxyQ(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

int AlertQ(string Prompt="", string Title="",UINT BtnLst=MB_OK)
{
    return MessageBox(nullptr,Prompt.c_str(),Title.c_str(),BtnLst);
}

void dis_quest(){
	gotoxyQ(15,3);
	cout << "------------------------------------= P L A Y E R =------------------------------------";
	for (int i = 1; i <= 22 ; i++) {
		gotoxyQ(15, 3+i);
		cout << "|                                                                                     |";
	}
	gotoxyQ(16,7);
	cout << "-------------------------------------= S O A L =-------------------------------------";
	gotoxyQ(16,22);
	cout << "------------------------------------= J A W A B =------------------------------------";
	gotoxyQ(15,26);
	cout << "---------------------------------------------------------------------------------------";
}

void dis_score(){
	gotoxyQ(40,5);
	cout << "+-------------= S C O R E =-------------+";
	for (int i = 1; i <= 13 ; i++) {
		gotoxyQ(40, 5+i);
	cout << "|                                       |";
	}
	gotoxyQ(40,19);
	cout << "+---------------------------------------+";
	gotoxyQ(40,20);
	cout << "+-----------------+  +------------------+";
	gotoxyQ(40,21);
	cout << "|    [y] Y E S    |  |	   [n] N O      |";
	gotoxyQ(40,22);
	cout << "+-----------------+  +------------------+";
	
}
