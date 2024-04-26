#include "game.h"
#include "Quest.h"
#include "admin.h"

#include <iostream>
#include <windows.h>

using namespace std;
void MenuGame();
void AdminLoginPage();

string username, password;
// inisialisai
Quest quest;
Game game;

int main()
{
    int choice;

    do
    {
        system("cls");
        cout << "Menu Game" << endl;
        cout << "1. Registrasi " << endl;
        cout << "2. Login " << endl;
        cout << "3. Exit " << endl;
        cout << "Masukkan Pilihan : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Masukkan username: ";
            cin >> username;
            cout << "Masukkan password: ";
            cin >> password;
            /*
            if ( Function Pengecekan Apakah ada Username yang sama )
            {
                cout << "Username sudah ada!" << endl;
                cout << "Silahkan pilih username lain." << endl;
                system("pause");
            }
            else
            {
                //Function Memasukkan Data Player pada file player.dat
                cout << "Registrasi berhasil!" << endl;
                //Function Menjalankan Game / Masuk Kedalam Dasboard Game
                system("pause");
            }
            */
            break;
        }
        case 2:
        {
            cout << "Masukkan Username : ";
            cin >> username;
            cout << "Masukkan Password : ";
            cin >> password;
            // Buat if else kondisi pengecekan
            break;
        }
        }
    } while (choice != 4);
    return 0;
}

void MenuGame()
{
    int choice;
    // Inisal Pengambilan Data Player

    do
    {
        system("cls");
        cout << "Welcome" << endl;
        cout << "Player : " << endl; // Data Player Dikeluarkan
        cout << "Score : " << endl;  // Data Plyer Dikeluarkan
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
            // Fuction Main Game
            break;
        };
        case 2:
            // Function Menampilkan Leaderboard
            break;
        }
    } while (choice != 3);
}

void AdminLoginPage()
{
    string us_admin, pw_admin;
    do
    {
        cout << "Siapakah Anda : ";
        cin >> us_admin;
        cout << "Kunci : ";
        cin >> pw_admin;
        // If else dari kondisi pengecekan admin dan masuk kedalam menu admin
    } while (false);
}
