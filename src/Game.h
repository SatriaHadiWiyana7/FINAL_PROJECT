#ifndef GAME_h
#define GAME_h

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;

struct Node
{
    string username;
    string password;
    int poin;
    Node *next;

    Node(string username, string password, int poin) : username(username), password(password), poin(poin), next(nullptr) {}

    string GetUsername() const
    {
        return username; // Return the username
    }

    int GetPoin() const
    {
        return poin; // Return the player's score
    }
};

class Game
{
public:
    Node *head;
    Node *currentPlayer;
    fstream dataFile;

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

    Node *GetPlayerByUsername(string username)
    {
        // Befungsi untuk nemapilkan nilai dari setiap player tanpa mengubah apapun yang ada dalam data
    }

    void UpdatePlayerToFile(string username, string password, int poin)
    {
        // Melakukan Update Data Kembali mmenggunakan ios::out untuk mereplay data yang sudah ada setelah permainan
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
        Node *current = head;

        while (current)
        {
            if (current->username == username)
            {
                return true;
            }
            current = head->next;
        }
        return false;
    }

private:
    void SavePlayerToFile(string username, string password, int poin)
    {
        // Menu save player ke player.dat
        ofstream dataFile("players.dat");
        dataFile.open("players.dat", ios::app);

        if (dataFile.is_open())
        {
            dataFile << username << "," << password << "," << poin << endl;
        }

        dataFile.close();
    }

    void LoadPlayerFromFile()
    {
        // lLoadPlayerFromFile digunakan untuk melakukan load data player
        string username, password, strpoin, line;
        int poin, baris;
        // while perulanggan digunakan untuk
        dataFile.open("players.dat");
        // melakukan load pada data players.dat
        while (getline(dataFile, line))
        {
            stringstream ss(line);
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, strpoin, ' ');
            poin = stoi(strpoin);

            Node(username, password, poin);
        }
    }
};

#endif