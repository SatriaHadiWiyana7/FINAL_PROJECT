// Melakukan Inisialisai pada file Header
#include "game.h"
#include "Quest_Easy.h"
#include "Quest_Medium.h"
#include "Quest_Hard.h"
#include "Quest_God.h"
#include "display.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

void MenuGame(string username);
void AdminDisplayMenu();

//  Inisialisasi untuk melakuka akses pada class
Game game;
Quest_Easy quest_easy;
Quest_Medium quest_medium;
Quest_Hard quest_hard;
Quest_God quest_god;

int main()
{
    int choice;
    string username, password;

    do
    {
        system("cls");
        title(); // show the title

        gotoxy(48, 14);
        cout << "   M A I N  M E N U   " << endl;

        gotoxy(51, 16);
        cout << "[1] Registration" << endl;
        gotoxy(51, 17);
        cout << "[2] Login       " << endl;
        gotoxy(51, 20);
        cout << "[0] Exit        " << endl;
        gotoxy(48, 25);
        cout << "Inputkan salah satu menu... ";
        choice = getch();

        switch (choice)
        {
        case 1:
        {
            cout << "Buat Username Anda : ";
            cin >> username;
            cout << "Buat Password Anda : ";
            cin >> password;
            if (username == "admin" && password == "admin")
            {
                cout << "Mohon Buat Username dan Password Baru" << endl;
                system("pause");
            }
            else if (game.IsUsernameExist(username))
            {
                cout << "Username Sudah Ada!" << endl;
                cout << "Silahkan Buat Username Lain!" << endl;
                system("pause");
            }
            else
            {
                game.AddPlayer(username, password);
                game.Login(username, password);
                cout << "Registrasi Telah Berhasil" << endl;
                system("pause");
                MenuGame(username);
            }
            break;
        }
        case 2:
        {
            cout << "Masukkan Username : ";
            cin >> username;
            cout << "Masukkan Password : ";
            cin >> password;
            if (username == "admin" && password == "admin")
            {
                // Menu Admin
            }
            else if (game.Login(username, password))
            {
                cout << "Login Berhasil!" << endl;
                system("puase");
                MenuGame(username);
            }
            else
            {
                cout << "Username/Password Salah!" << endl;
            }
            break;
        }
        case 3:
            cout << "Anda Keluar!!" << endl;
            break;
        }
    } while (choice != 3);

    return 0;
}

void MenuGame(string username)
{
    int choice;
    // Melakukan Akses untuk mendapatkan username melalui fungsi dengan paramater username
    Node *playerNode = game.GetPlayerByUsername(username);

    do
    {
        system("cls");
        cout << "Welcome" << endl;
        cout << "Player : " << playerNode->GetUsername() << endl; // nama player
        cout << "Score : " << playerNode->GetPoin() << endl;      // poin player
        cout << "============================" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. LeaderBoard" << endl;
        cout << "3. Back" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string pilihan;
            // quest.PlayGame(*playerNode);
            if (pilihan == "EASY")
            {
                // Quest Easy
                break;
            }
            else if (pilihan == "MEDIUM")
            {
                // Quest Medium
                break;
            }
            else if (pilihan == "HARD")
            {
                // Quest Hard
                break;
            }
            else if (pilihan == "GOD")
            {
                // Quest God
                break;
            }
            else
            {
                cout << "Pilihan Tidak Tersedia" << endl;
            }
        };
        case 2:
            // Display Leaderboard
            game.DisplayLeaderboard();
            break;
        }
    } while (choice != 3);
}

void AdminDisplayMenu()
{
    int choice;
    string username, password;
    int position;

    cout << "Masukkan Username Anda : ";
    cin >> username;
    cout << "Masukkan Password Anda : ";
    cin >> password;

    /*
        if (!admin.Login(username, password)) {
            system("pause");
            return;
        }
     */
    do
    {
        system("cls");
        cout << "Menu Admin" << endl;
        cout << "1. Who" << endl; // clear
        cout << "2. Modify Admin" << endl;
        cout << "3. Tampilkan Admin" << endl; // clear
        cout << "4. Tambah Admin" << endl;    // clear
        cout << "5. Menghapus Admin" << endl;
        cout << "6. Lihat Semua Player" << endl; // clear
        cout << "7. Modify Player" << endl;
        cout << "8. Menambahkan Player" << endl;
        cout << "9. Menghapus Player" << endl; // byusername
        cout << "10. Menghapus AllPlayer" << endl;
        cout << "11. Menambahkan Soal(Easy)" << endl;
        cout << "12. Menambahkan Soal(Medium)" << endl;
        cout << "13. Menambahkan Soal(Hard)" << endl;
        cout << "14. Menambahkan Soal(God)" << endl;
        cout << "15. Menghapus AllSoal" << endl;
        cout << "Who untuk Mengetahui Identitas" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // admin.AboutMe(username);
            system("pause");
            break;
        }
        case 2:
        {
            // admin.DisplayAllPlayers(game);
            system("pause");
            break;
        }

        case 3:
        {
            // Add admin
            cout << "Masukkan username : ";
            cin >> username;
            cout << "Masukkan password : ";
            cin >> password;
            cout << "Masukkan Position : ";
            cin >> position;
            // admin.AddNode(username, password,position);
            break;
        }
        case 4:
            // Back to main menu
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (choice != 4);
}