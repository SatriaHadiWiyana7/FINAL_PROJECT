#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h> //printf
#include <conio.h>
#include <mmsystem.h>

using namespace std;

void gotoxyA(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

int AlertAdmin(string Prompt="", string Title="",UINT BtnLst=MB_OK)
{
    return MessageBox(nullptr,Prompt.c_str(),Title.c_str(),BtnLst);
}

void dis_Aboutme() {
	gotoxyA(44,15);
    cout << "+------= W H O  A M I =------+";
    for (int i = 1; i <= 5 ; i++) {
		gotoxyA(44, 15+i);
		cout << "|                            |";
	}
    gotoxyA(44,20);
	cout << "+----------------------------+";
}

void dis_usrnotfound(){
	gotoxyA(40,15);
    cout << "+------------------------------------------+";
    gotoxyA(40,16);
	cout << "|                                          |";
    gotoxyA(40,17);
	cout << "+------------------------------------------+";
}

void dis_allplayer(){
	for (int i = 1; i <= 116 ; i++) {
		gotoxyA(0+i, 3);
		cout << "-";
	}
}

void dis_delsuccess(){
	gotoxyA(40,15);
    cout << "+-----------------------------------------------+";
    gotoxyA(40,16);
	cout << "|                                               |";
    gotoxyA(40,17);
	cout << "+-----------------------------------------------+";
}

void dis_modify() {
	gotoxyA(38, 14);
	cout << "--------------= M O D I F Y =--------------";
	for (int i = 1; i <= 5 ; i++) {
		gotoxyA(38, 14+i);
		cout << "|                                         |";
	}
	gotoxyA(38, 20);
	cout << "-------------------------------------------";
}

void dis_modsuccess(){
	gotoxyA(40,15);
    cout << "+-----------------------------------------------+";
    gotoxyA(40,16);
	cout << "|                                               |";
    gotoxyA(40,17);
	cout << "+-----------------------------------------------+";
}

