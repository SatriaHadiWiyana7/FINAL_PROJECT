/*
	Name		: BANKSOS (Bank Soal Siswa)
	Copyright	: 2024 | Naspad team
	Author		: Naspad Team
	Description	: This software is made to fulfill the Data Structure's Final Project 
*/

/*------------------------Note: IMPORTANT!--------------------------!!
!!	Add this command to compiler before build this code :			!!
!!	-lwinmm    (DEVC++ -> compiler option -> add following command) !!
!!		or															!!
!!	winmm.lib  (VisualStudio -> linker -> input)					!!
!!------------------------------------------------------------------*/

#include "game.h"
#include "Quest.h"
#include "admin.h"
#include "display.h"

#include <iostream>
#include <windows.h>

using namespace std;
void MenuGame(string username);
void AdminDisplayMenu();
void ManagementAdmin(string username);
void ManagementSoal(string username);
void ManagemenPlayer(string username);

Game game;
Quest quest;
Admin admin(game);

int main()
{
	int choice;
	string username, password;
	loading();
	PlaySound(TEXT("sounds/register.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	do
	{
		system("cls");
		
		title(); // show the title

        gotoxy(50, 14);
        cout << "L O G I N   P A G E" << endl;

        gotoxy(51, 16);
        cout << "[1] Registration" << endl;
        gotoxy(51, 17);
        cout << "[2] Login       " << endl;
        gotoxy(51, 20);
        cout << "[0] Exit        " << endl;
        gotoxy(48, 25);
        cout << "Tekan salah satu menu... ";
        choice = getch();


		switch (choice)
		{
		case '1':
		{
			system("cls");
			title();
			dis_registration();
			
			gotoxy(45, 16);
			cout << "Buat Username Anda : ";
			cin >> username;
			gotoxy(45, 17);
			cout << "Buat Password Anda : ";
			cin >> password;
			if (username == "admin" && password == "admin")
			{
				Alert("Silakan buat Username lain!!!");
			}
			else if (game.IsUsernameExist(username))
			{
				Alert("Username Sudah ada\nSilakan Buat Username Lain!");
			}
			else
			{
				game.AddPlayer(username, password);
				game.Login(username, password);
				Alert("Registrasi telah berhasil");
				MenuGame(username);
			}
			break;
		}
		case '2':
		{
			system("cls");
			title();
			dis_login();
			
			gotoxy(45, 16);
			cout << "Masukkan Username : ";
			cin >> username;
			gotoxy(45, 17);
			cout << "Masukkan Password : ";
			cin >> password;
			if (username == "admin" && password == "admin")
			{
				Alert("Welcome to Dashboard Admin");
				AdminDisplayMenu();
			}
			else if (game.Login(username, password))
			{
				Alert("Login berhasil!");
				MenuGame(username);
			}
			else
			{
				Alert("Username/Password Salah!");
			}
			break;
		}
		}
	} while (choice != '0');

	return 0;
}

void MenuGame(string username)
{
	int choice;
	int count = 1;
	string Achievement;
	Node *playerNode = game.GetPlayerByUsername(username);

	do
	{
		system("cls");
		title();
		dis_menugame();
		PlaySound(TEXT("sounds/menu_player.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		
		gotoxy(47,16);
		cout << "Player : " << playerNode->GetUsername() << Achievement << endl; // nama player
		gotoxy(47,17);
		cout << "Score  : " << playerNode->GetPoin() << endl;	  // poin player
		gotoxy(46,18);
		cout << "---------------------------" << endl;
		gotoxy(52,20);
		cout << "[1] Play Game" << endl;
		gotoxy(52,21);
		cout << "[2] LeaderBoard" << endl;
		gotoxy(52,22);
		cout << "[3] Back" << endl;
		gotoxy(48, 28);
        cout << "Tekan salah satu menu... ";
		choice = getch();

		switch (choice)
		{
		case '1':
		{
			int type;
			system("cls");
			title();
			dis_dificulty();
			
			do{
			gotoxy(52, 16);
			cout << "[1] Easy Mode" << endl;
			gotoxy(52, 17);
			cout << "[2] Medium Mode" << endl;
			gotoxy(52, 18);
			cout << "[3] Hard Mode" << endl;
			gotoxy(52, 19);
			cout << "[4] God Mode" << endl;
			gotoxy(54, 21);
			cout << "Pilihan : ";
			cin >>type;
			if(type == 23115626 && count == 1) {
				Alert("Achievement Pencundang Didapatkan");
				Alert("Game Master Memberikan Title Pencundang");
				Achievement = " Poops";
				count ++;
				break;	
			}
			}while(type <= 0 || type >= 5);
			quest.PlayGame(type, *playerNode);
			break;
		};
		case '2':
		{
			system("cls");
			title();
			dis_leaderboard();
			
			game.ShowLeaderboard();
			gotoxy(44, 28);
			system("pause");
			break;
		}
		case '3':
		{
			PlaySound(TEXT("sounds/register.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			return;
			break;
		}
		}
	} while (choice != '3');
}

void AdminDisplayMenu()
{
	int choice;
	string username, password;
	int Hak_Akses, position;
	system("cls");
	title();
	dis_loginAdmin();

	gotoxy(43, 16);
	cout << "Masukkan Username Anda : ";
	cin >> username;
	gotoxy(43, 17);
	cout << "Masukkan Password Anda : ";
	cin >> password;

	if (!admin.Login(username, password))
	{
		Alert("Username/Password Admin Salah!!");
		return;
	}

	Hak_Akses = admin.position(username);

	do
	{
	Menu:
		system("cls");
		title();
		PlaySound(TEXT("sounds/music_admin.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		
		gotoxy(50, 13);
		cout << "M E N U  A D M I N" << endl;
		gotoxy(49, 15);
		cout << "[1] Who" << endl;
		gotoxy(49, 16);
		cout << "[2] Management Admin" << endl;
		gotoxy(49, 17);
		cout << "[3] Managemnt Player" << endl;
		gotoxy(49, 18);
		cout << "[4] Management Game" << endl;
		gotoxy(49, 19);
		cout << "[5] Back" << endl;
		gotoxy(45, 21);
		cout << "Who untuk Mengetahui Identitas" << endl;
		gotoxy(48, 25);
        cout << "Tekan salah satu menu... ";
		choice = getch();

		switch (choice)
		{
		case '1':
		{
			system("cls");
			title();
			
			admin.AboutMe(username);
			gotoxy(45, 25);
			system("pause");
			goto Menu;
			break;
		}
		case '2':{
			ManagementAdmin(username);	
			goto Menu;
			break;
		}
		case '3': {
			ManagemenPlayer(username);
			goto Menu;
			break;
		}
		case '4': {
			ManagementSoal(username);
			goto Menu;
			break;
		}
		case '5': {
			PlaySound(TEXT("sounds/register.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			return;
		}
	}
	} while (choice <= 0 || choice >= 6);
}

void ManagemenPlayer(string username) {
	int choice;
	
	int Hak_Akses = admin.position(username);
	do {
		Menu:
		system("cls");
		title();
		gotoxy(45, 13);
		cout << "M A N A G E M E N T  P L A Y E R" << endl;
		gotoxy(49, 15);
		cout << "[1] Lihat Semua Player " << endl;
		gotoxy(49, 16);
		cout << "[2] Tambah Player" << endl;
		gotoxy(49, 17);
		cout << "[3] Modify Player" << endl;
		gotoxy(49, 18);
		cout << "[4] Hapus Player" << endl;
		gotoxy(49, 19);
		cout << "[5] Hapus Semua Player" << endl;
		gotoxy(49, 20);
		cout << "[6] Back" << endl;
		gotoxy(48, 25);
        cout << "Tekan salah satu menu... ";
		choice = getch();
		switch(choice) {
			case '1': {
				system("cls");
				admin.DisplayAllPlayers(game);
				system("pause");
				goto Menu;
				break;
			}
			case '2': {
				string new_username_player, new_password_player;
				char add_more;	
				
				do
				{
					system("cls");
					title();
					dis_addplayer();
					
					gotoxy(41,15);
					cout << "Masukkan Username Player : ";
					cin >> new_username_player;
					gotoxy(41,16);
					cout << "Masukkan Password Player : ";
					cin >> new_password_player;
					admin.AddPlayerFromAdmin(new_username_player, new_password_player);
					
					gotoxy(50,18);
					cout << "Tambah Player Lagi? ";
					add_more = getch();
				} while (tolower(add_more) == 'y');
				goto Menu;
				break;
			}
			case '3':{
				if (Hak_Akses <= 2) {
					system("cls");
					title();
					dis_finduser();
					
					string find_username;
					gotoxy(38, 16);
					cout << "Masukkan Username yang mau diubah : ";
					cin >> find_username;
					
					system("cls");
					title();
					
					game.ModifyPlayerData(find_username);	
				}else {
					Alert("Anda tidak Memiliki Hak Akses! ");
				}
				goto Menu;
				break;
			}
			case '4':{
				system("cls");
				title();
				dis_delplayer();
				
				string player_username_delete;
				gotoxy(40, 16);
				cout << "Masukkan Username : ";
				cin >> player_username_delete;
				game.deletePlayer(player_username_delete);
				goto Menu;
				break;
			}
			case '5':{
				if(Hak_Akses <= 1) {
					Alert("Menghapus All Player!");
					admin.ClearPlayerData();				
				}else {
					Alert("Anda Tidak Memiliki Hak Akses !");
				}
				goto Menu;
				break;
			}
			case '6':{
				return;
			}
		}
	}while(choice <= '0' || choice >= '7');
}

void ManagementAdmin(string username) {
	int choice;
	
	int Hak_Akses = admin.position(username);
	do{
		Menu:
		system("cls");
		title();
		gotoxy(44, 13);
		cout << "M A N A G E M E N T  A D M I N" << endl;
		gotoxy(51, 15);
		cout << "[1] Lihat Admin" << endl;
		gotoxy(51, 16);
		cout << "[2] Tambah Admin" << endl;
		gotoxy(51, 17);
		cout << "[3] Modify Admin" << endl;
		gotoxy(51, 18);
		cout << "[4] Hapus Admin" << endl;
		gotoxy(51, 19);
		cout << "[5] Back" << endl;
		gotoxy(48, 25);
        cout << "Tekan salah satu menu... ";
		choice = getch();
		
		switch(choice) {
			case '1': {
				system("cls");
        		gotoxy(48,1);
        		cout << "<- L I S T  O F  A D M I N ->" << endl;
        		
				admin.PrintTree(admin.GetRoot());
				gotoxy(48, 25);
				system("pause");
				goto Menu;
				break;
			}
			case '2': {
				string username, password;
				int position;
				system("cls");
				title();
				dis_tambahadmin();
				
				if(Hak_Akses == 0) {
					gotoxyA(40, 16);
					cout << "Masukkan username : ";
					cin >> username;
					gotoxyA(40, 17);
					cout << "Masukkan password : ";
					cin >> password;
					gotoxyA(40, 18);
					cout << "Masukkan Position : ";
					cin >> position;
					if (position <= 1) {
						position = 1;
						admin.AddNode(username, password, position);
					}else {
						admin.AddNode(username, password, position);
					}
				} else {
					Alert("Anda Tidak Memiliki Akses!");
				}
				goto Menu;
				break;
			}
			case '3': {
				if (Hak_Akses <= 2)
				{
					system("cls");
					title();
					dis_modadmin();
					
					string find_username;
					gotoxy(38, 16);
					cout << "Masukkan Admin Yang Mau Diubah : ";
					cin >> find_username;
					
					system("cls");
					title();
					
					admin.modifyAdmin(find_username);
					gotoxy(48, 25);
					system("pause");
				}
				else
				{
					Alert("Tidak Mendapat Akses! ");
				}
				goto Menu;
				break;
			}
			case '4': {
				if (Hak_Akses <= 1)
				{
					system("cls");
					title();
					dis_deladmin();
					
					gotoxy(38, 16);
					cout << "Masukkan Nama Yang Ingin Dihapus : ";
					string Admin_username_delete;
					cin >> Admin_username_delete;
					admin.RemoveAdmin(Admin_username_delete);
				}
				else
				{
					Alert("Tidak Mendapat Akses! ");
				}
				goto Menu;
				break;
			}
			case '5':{
				return;
			}
		}
	}while(choice <= 0 || choice >= 6);
}

void ManagementSoal(string username) {
	int choice;
	
	int Hak_Akses = admin.position(username);
	do{
		Menu:
		system("cls");
		title();
		gotoxy(46, 13);
		cout << "M A N A G E M E N T  S O A L" << endl;
		gotoxy(49, 15);
		cout << "[1] Tambah Soal Easy" << endl;
		gotoxy(49, 16);
		cout << "[2] Tambah Soal Medium" << endl;
		gotoxy(49, 17);
		cout << "[3] Tambah Soal Hard" << endl;
		gotoxy(49, 18);
		cout << "[4] Tambah Soal God" << endl;
		gotoxy(49, 19);
		cout << "[5] Back" << endl;
		gotoxy(48, 25);
        cout << "Tekan salah satu menu... ";
		choice = getch();
		
		switch(choice) {
			case '1': {
				if(!quest.penuh()) {
					string soal, kunci;
					int benar, salah;
					char add_more;
					do
					{
						system("cls");
						title();
						dis_tambahsoal();
						
						gotoxy(19,15);
						cout << "Masukkan Soal       : ";
						getline(cin,soal);
						gotoxy(19,16);
						cout << "Masukkan Kunci Soal : ";
						getline(cin,kunci);
						gotoxy(19,17);
						cout << "Poin Jika Benar     : ";
						cin >> benar;
						gotoxy(19,18);
						cout << "Poin Jika Salah     : ";
						cin >> salah;
						admin.Insert_Easy(soal, kunci, benar, salah);
						dis_pilihan();
						gotoxy(50,15);
						cout << "Tambah Soal Lagi?";
						add_more = getch();
					} while (tolower(add_more) == 'y');
				}else {
					Alert("Data Telah Penuh");
				}
				goto Menu;
				break;
			}
			case '2': { 
				if(!quest.penuh()) {
					string soal, kunci;
					int benar, salah;
					char add_more;
					do
					{
						system("cls");
						title();
						dis_tambahsoal();
						
						gotoxy(19,15);
						cout << "Masukkan Soal       : ";
						getline(cin,soal);
						gotoxy(19,16);
						cout << "Masukkan Kunci Soal : ";
						getline(cin,kunci);
						gotoxy(19,17);
						cout << "Poin Jika Benar     : ";
						cin >> benar;
						gotoxy(19,18);
						cout << "Poin Jika Salah     : ";
						cin >> salah;
						admin.Insert_Medium(soal, kunci, benar, salah);
						dis_pilihan();
						gotoxy(50,15);
						cout << "Tambah Soal Lagi?";
						add_more = getch();
					} while (tolower(add_more) == 'y');
				}else {
					cout << "Data Telah Penuh" << endl;
				}
				goto Menu;
				break;
			}
			case '3': {
				if(!quest.penuh()) {
					string soal, kunci;
					int benar, salah;
					char add_more;
					do
					{
						system("cls");
						title();
						dis_tambahsoal();
						
						gotoxy(19,15);
						cout << "Masukkan Soal       : ";
						getline(cin,soal);
						gotoxy(19,16);
						cout << "Masukkan Kunci Soal : ";
						getline(cin,kunci);
						gotoxy(19,17);
						cout << "Poin Jika Benar     : ";
						cin >> benar;
						gotoxy(19,18);
						cout << "Poin Jika Salah     : ";
						cin >> salah;
						admin.Insert_Hard(soal, kunci, benar, salah);
						dis_pilihan();
						gotoxy(50,15);
						cout << "Tambah Soal Lagi?";
						add_more = getch();
					} while (tolower(add_more) == 'y');
				}else {
					cout << "Data Telah Penuh" << endl;
				}
				goto Menu;
				break;
			}
			case '4': {
				if(!quest.penuh()) {
					string soal, kunci;
					int benar, salah;
					char add_more;
					do
					{
						system("cls");
						title();
						dis_tambahsoal();
						
						gotoxy(19,15);
						cout << "Masukkan Soal       : ";
						getline(cin,soal);
						gotoxy(19,16);
						cout << "Masukkan Kunci Soal : ";
						getline(cin,kunci);
						gotoxy(19,17);
						cout << "Poin Jika Benar     : ";
						cin >> benar;
						gotoxy(19,18);
						cout << "Poin Jika Salah     : ";
						cin >> salah;
						admin.Insert_God(soal, kunci, benar, salah);
						dis_pilihan();
						gotoxy(50,15);
						cout << "Tambah Soal Lagi?";
						add_more = getch();
					} while (tolower(add_more) == 'y');
				}else {
					cout << "Data Telah Penuh" << endl;
				}
				goto Menu;
				break;
			}
			case '5': {		
				return;
			}
		}
	}while(choice <=0 || choice >= 10);
}
