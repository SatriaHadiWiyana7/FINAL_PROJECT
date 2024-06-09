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

    void UpdatePlayerToFile(string username, string password, int newPoin)
  {
    // Mode menulis
    fstream dataFile("players.dat", ios::out);

    if (dataFile.is_open())
    {
      // Inisialisasi Variabel
      bool playerFound = false;
      // Memposisikan Current pada posisi head
      Node *current = head;

      while (current)
      {
        // Kondisi jika ketemu dengan username dan password
        if (current->username == username && current->password == password)
        {
          // merubah current->poin agar berubah menjadi poin yang baru
          current->poin = newPoin;
          playerFound = true;
          break;
        }
        current = current->next;
      }

      // Kondisi jika Player Tidak ditemukan
      if (!playerFound)
      {
        // Menambahkan Node Baru
        Node *newNode = new Node(username, password, newPoin);
        // Jika pada head kosong
        if (!head)
        {
          head = newNode;
        }
        // jika head tidak kosong
        else
        {
          // jika node tidak kosong
          Node *last = head;
          while (last->next)
          {
            last = last->next;
          }
          last->next = newNode;
        }
      }

      current = head;
      while (current)
      {
        dataFile << current->username << "," << current->password << "," << current->poin << endl;
        current = current->next;
      }

      cout << "Data pemain berhasil diperbarui!" << endl;
    }
    else
    {
      cout << "Data Tidak Tersimpan!" << endl;
    }

    dataFile.close();
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
    // Memposisikan current pada posisi head
    Node *current = head;
    while (current)
    {
      // jika terdapat username yang mirip
      if (current->username == username)
      {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  // Fungsi untuk mencari player melalui Username
  Node *GetPlayerByUsername(string username)
  {
    // Memposisikan current berada pada head
    Node *current = head;
    while (current)
    {
      // Jika menemukan username yang sama maka akan mengembalikan nilai dalam curret
      if (current->username == username)
      {
        return current;
      }
      current = current->next;
    }
    // Kondisi jika tidak terdapt data yang sama
    return nullptr;
  }






    // Fungsi Sorting Menggunakan Vector
  void SortPlayersByScore()
  {
    // digunakan untuk vector agar dalam keadaan clear atau bersih
    players.clear();

    // meninisialisasi
    Node *current = head;
    while (current)
    {
      // untuk mendorong data masuk kedalam vector kembali
      players.push_back(*current);
      current = current->next;
    }

    // fungsi sort merupakan fungsi bawaan dari vector.
    // melakukan perbandingan antara player.a dan player.b dimana jika kondisi memenuhi dia akan mengeluarkan true yang
    // jika false maka akan tukar
    sort(players.begin(), players.end(), [](const Node &a, const Node &b)
         { return a.poin > b.poin; });
  }

   void ShowLeaderboard()
  {
    SortPlayersByScore();

    cout << "Top 10 Leaderboard" << endl;
    // min 10 merupakan agar data yang tertampil pada perulangan memiliki max limit 10
    for (int i = 0; i < min(10, (int)players.size()); ++i)
    {
      cout << i + 1 << ". " << players[i].username << " - " << players[i].poin << endl;
    }
    cout << "--------------------------" << endl;
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

            // Memasukkan Data yang telah terbaca ke dalam Node
            Node *newNode = new Node(username, password, poin);

            // Kondisi Pengecekan Apakah head adalah kosong
            if (!head)
            {
                // player baru menjadi head
                head = newNode;
            }
            // jika head tidak kosong
            else
            {
                // pointer akan berada pada current
                Node *current = head;
                // perulanggan dimana jika masih dapat dinext maka akan next
                while (current->next)
                {
                    current = current->next;
                }
                // jika data sudah tidak bisa di next maka data akan ditaruh disitu
                current->next = newNode;
            }
        }
    }
};

#endif