#include "game.h"
#include "Quest_Easy.h"
#include "Quest_Medium.h"
#include "Quest_Hard.h"
#include "Quest_God.h"

#include <iostream>
#include <windows.h>

using namespace std;
void MenuGame();
void AdminLoginPage();

string admin_user = "satria";
string admin_pass = "satria";
string username, password;
Game game;
Quest quest;

int main()
{
    quest.LoadAllData();
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
            cout << "Buat Username Anda : ";
            cin >> username;
            cout << "Buat Password Anda : ";
            cin >> password;
            if (game.IsUsernameExist(username))
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
                MenuGame();
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
                AdminLoginPage();
            }
            else if (game.Login(username, password))
            {
                cout << "Login Berhasil!" << endl;
                system("puase");
                MenuGame();
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

void MenuGame()
{
    int choice;
    Player player = game.GetPlayerByUsername(username);

    do
    {
        system("cls");
        cout << "Welcome" << endl;
        cout << "Player : " << player.getUsername() << endl; // nama player
        cout << "Score : " << player.getPoin() << endl;      // poin player
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
            quest.PlayGame(username, player);
            break;
        };
        case 2:
            game.DisplayLeaderboard();
            break;
        }
    } while (choice != 3);
}

void AdminLoginPage()
{
    string us_admin, pw_admin;
    int choice;
    int batas = 3;

    do
    {
        system("cls");
        cout << "Welcome To Dasboard Admin" << endl;
        cout << "1. Login " << endl;
        cout << "2. Back " << endl;
        cout << "Masukkan Pilihan Anda : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            while (batas > 0)
            {
                system("cls");
                cout << "Masukkan Username Admin : ";
                cin >> us_admin;
                cout << "Masukkan Password Admin : ";
                cin >> pw_admin;

                if (us_admin == admin_user && pw_admin == admin_pass)
                {
                    cout << "Anda Masuk Kedalam Menu Admin" << endl;
                }
                else
                {
                    batas--;
                    cout << "Gagal Masuk Kedalam System!!" << endl;
                }
                if (batas == 0)
                {
                    Sleep(2000);
                    cout << "System Menilai Anda Melakukan Bruteforce " << endl;
                    Sleep(1000);
                    cout << "System Melakukan Tindakan" << endl;
                    Sleep(500);
                    cout << "Tindakan Dilakukan!!" << endl;
                    exit(0);
                }
            }
        }
        }
    } while (choice != 2);
}
