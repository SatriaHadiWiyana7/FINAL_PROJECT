#ifndef GAME_h
#define GAME_h

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;

class Player
{
public:
    // Data Player
    string username;
    string password;
    int poin;

    // Constructor
    Player(string username, string password, int poin)
    {
        this->username = username;
        this->password = password;
        this->poin = poin;
    }

    // Ketika Butuh Username dapat Memanggil Fungsi ini
    // Syarat Dipanggil pada luar dari Game.h
    string getUsername() { return username; }
    int getPoin() { return poin; }
};

class Game
{
public:
    // Game -> Membuka File Local dan Melakukan load dan kemudian jangan lupa ditutup
    // username is already
    // login Fungsi
    // Leaderboard
    // AddPlayer
    // FindPlayer
    // void save
private:
    // void load
};

#endif