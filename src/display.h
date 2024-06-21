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

int Alert(string Prompt="", string Title="",UINT BtnLst=MB_OK)
{
    return MessageBox(nullptr,Prompt.c_str(),Title.c_str(),BtnLst);
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

void dis_registration() {
	gotoxy(38, 14);
	cout << "---------= R E G I S T A T I O N =---------";
	for (int i = 1; i < 5 ; i++) {
		gotoxy(38, 14+i);
		cout << "|                                         |";
	}
	gotoxy(38, 19);
	cout << "-------------------------------------------";
}

void dis_login() {
	gotoxy(38, 14);
	cout << "---------------= L O G I N =---------------";
	for (int i = 1; i < 5 ; i++) {
		gotoxy(38, 14+i);
		cout << "|                                         |";
	}
	gotoxy(38, 19);
	cout << "-------------------------------------------";
}

void dis_menugame() {
	gotoxy(45, 14);
	cout << "----= M A I N   M E N U =----";
	for (int i = 1; i <= 9 ; i++) {
		gotoxy(45, 14+i);
		cout << "|                           |";
	}
	gotoxy(45, 24);
	cout << "-----------------------------";
}

void dis_dificulty() {
	gotoxy(45, 14);
	cout << "----= D I F I C U L T Y =----";
	for (int i = 1; i <= 8 ; i++) {
		gotoxy(45, 14+i);
		cout << "|                           |";
	}
	gotoxy(45, 23);
	cout << "-----------------------------"; 
}

void dis_leaderboard() {
	gotoxy(40, 12);
	cout << "-------= L E A D E R B O A R D =-------";
	for (int i = 1; i <= 12 ; i++) {
		gotoxy(40, 12+i);
		cout << "|                                     |";
	}
	gotoxy(40, 25);
	cout << "---------------------------------------";
}

void dis_loginAdmin() {
	gotoxy(38, 14);
	cout << "---------------= A D M I N =---------------";
	for (int i = 1; i < 5 ; i++) {
		gotoxy(38, 14+i);
		cout << "|                                         |";
	}
	gotoxy(38, 19);
	cout << "-------------------------------------------";
}

void dis_finduser(){
	gotoxy(35,15);
    cout << "+----------------------------------------------------+";
    gotoxy(35,16);
	cout << "|                                                    |";
    gotoxy(35,17);
	cout << "+----------------------------------------------------+";
}

void dis_modadmin(){
	gotoxy(35,15);
    cout << "+----------------------------------------------------+";
    gotoxy(35,16);
	cout << "|                                                    |";
    gotoxy(35,17);
	cout << "+----------------------------------------------------+";
}

void dis_deladmin(){
	gotoxy(35,15);
    cout << "+----------------------------------------------------+";
    gotoxy(35,16);
	cout << "|                                                    |";
    gotoxy(35,17);
	cout << "+----------------------------------------------------+";
}

void dis_addplayer(){
	gotoxy(39,13);
	cout << "+--------= A D D   P L A Y E R =--------+";
	for (int i = 1; i <= 6 ; i++) {
		gotoxy(39, 13+i);
	cout << "|                                       |";
	}
	gotoxy(39,20);
	cout << "+---------------------------------------+";
	gotoxy(39,21);
	cout << "+-----------------+  +------------------+";
	gotoxy(39,22);
	cout << "|    [y] Y E S    |  |	   [n] N O      |";
	gotoxy(39,23);
	cout << "+-----------------+  +------------------+";
	
}

void dis_delplayer() {
	gotoxy(38, 14);
	cout << "-------= D E L E T E   P L A Y E R =-------";
	for (int i = 1; i <= 3 ; i++) {
		gotoxy(38, 14+i);
		cout << "|                                         |";
	}
	gotoxy(38, 18);
	cout << "-------------------------------------------";
}

void dis_tambahadmin() {
	gotoxy(38, 14);
	cout << "-----------= A D D   A D M I N =-----------";
	for (int i = 1; i <= 5 ; i++) {
		gotoxy(38, 14+i);
		cout << "|                                         |";
	}
	gotoxy(38, 20);
	cout << "-------------------------------------------";
}

void dis_tambahsoal(){
	gotoxy(17,13);
	cout << "+---------------------------= A D D   Q U E S T I O N =---------------------------+";
	for (int i = 1; i <= 6 ; i++) {
		gotoxy(17, 13+i);
		cout << "|                                      				           |";
	}
	gotoxy(17,20);
	cout << "+---------------------------------------------------------------------------------+";
}

void dis_pilihan() {
	system("cls");
	title();
	gotoxy(39,17);
	cout << "+-----------------+  +------------------+";
	gotoxy(39,18);
	cout << "|    [y] Y E S    |  |	   [n] N O     |";
	gotoxy(39,19);
	cout << "+-----------------+  +------------------+";
}
