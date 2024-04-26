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
    Game()
    {
        // Kondisi Membuka file Player.dat agar data dapat masuk kedalam system
    }

    ~Game()
    {
        // Pointer dari Game Gunakan ini untuk melakukan Penutupan File
    }

    int FindPlayerIndex(string username)
    {
        // FindPlayerIndex digunakan untuk mencari player berdasarkan paramater username
    }

    void AddPlayer(string username, string password)
    {
        // AddPlayer digunakan untuk menambahkan data player dengan parameter username dan password
        // jangan lupa masukkan fungsi save dan tambahkan 0 sebagai pemulaian poin yang didapat player
    }

    bool Login(string username, string password)
    {
        // Gunakan FindPlayerIndex untuk menemukan player yang mirip dengan username dan password lalu buat kondisi login
    }

    void DisplayLeaderboard()
    {
        // Buat Untuk menampilkan data player dari file player.dat
        // lebihbagus jika data yang ditampilkan hanya 10 terbesar lakukan dengan memodifikasi perulangannya
    }

    bool IsUsernameExist(string username)
    {
        // Kondisi untuk melakukan pengecekan apakah ada username yang sama dengan username yang sudah pernah dibuat
    }

    void SavePlayerToFile(string username, string password, int poin)
    {
        // Menu save player ke player.dat
    }

private:
    void LoadPlayerFromFile()
    {
        // lLoadPlayerFromFile digunakan untuk melakukan load data player
    }
};

#endif