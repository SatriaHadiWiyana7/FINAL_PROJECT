#ifndef GAME_H
#define GAME_H

#include "displayGame.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
  string username;
  string password;
  int poin;
  Node *next;

  // Constructor Default
  Node() : username(""), password(""), poin(0), next(nullptr) {}

  // Constructor
  Node(string username, string password, int poin) : username(username), password(password), poin(poin), next(nullptr) {}

  // Fungsi mengembalikan Username tanpa bisa merubah nilai Username
  string GetUsername() const
  {
    return username; // Return the username
  }

  // Fungsi mengembalikan nilai Poin tanpa bisa merubah nilai poin
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
  vector<Node> players;
  fstream dataFile;

  Game()
  {
    // Inisialisasi head menjadi null
    head = nullptr;
    // dalam mode menulis,append,membaca
    dataFile.open("players.dat", ios::in | ios::out | ios::app);
    if (dataFile.is_open())
    {
      // ketika data dalam keadaan open maka akan menjalankan fungsi load
      LoadPlayerFromFile();
    }
    else
    {
      AlertG("Data Pemain Gagal Dibuka!");
    }
  }

  // Negasi jika dataFile dalam keadaan open maka close
  ~Game()
  {
    if (dataFile.is_open())
    {
      dataFile.close();
    }
  }

  // Fungsi menambahkan Player Baru
  void AddPlayer(string username, string password)
  {
    // membuat player baru menggunakan username dan password
    // lalu membuat nilai default poin menjadi 0
    Node *newNode = new Node(username, password, 0);

    // Kondisi jika terdapat head dalam keadaan kosong
    if (!head)
    {
      // menambahkan newNode ke dalam head
      head = newNode;
    }
    // Ketika head tidak dalam keadaan kosong
    // Menambahkan pada next
    else
    {
      Node *current = head;
      while (current->next)
      {
        current = current->next;
      }
      current->next = newNode;
    }

    SavePlayerToFile(username, password, 0);
  }

  // Kondisi menghapus Semua Node
  void ClearAllNode()
  {
    Node *current = head;
    Node *prev = nullptr;

    while (current)
    {
      prev = current;
      current = current->next;
      delete prev;
    }

    head = nullptr;
  }

  // Fungsi Login menggunakan paramater username dan password
  bool Login(string username, string password)
  {
    // Memposisikan current pada posisi head
    Node *current = head;
    while (current)
    {
      // Jika data player memiliki username dan password yang sama
      if (current->username == username && current->password == password)
      {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  // Fungsi untuk melakukan pengecekan username
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
    return nullptr;
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

      // cout << "Data pemain berhasil diperbarui!" << endl;
    }
    else
    {
      AlertG("Data Tidak Tersimpan!");
    }

    dataFile.close();
  }

  // Fungsi Memodifikasi Player berdasarkan Username
  // melakukan referensi kedalam username tanpa menggubah username tersebut
  bool ModifyPlayerData(const string &username)
  {
    // Mencari Player berdasarkan Username
    Node *player = GetPlayerByUsername(username);
    // Kondisi Jika Player tidak ditemukan
    if (!player)
    {
    	dis_searchmodplayer();
    	gotoxyG(39,16);
    	cout << "Player with username '" << username << "' not found!" << endl;
    	return false;
    }

    // inisialisasi variables untuk modified data
    string newUsername = player->username;
    string newPassword = player->password;
    int newPoin = player->poin;

    int choice;
    // Display Melakukan Perubahan
    do
    {

      gotoxyG(40, 14);	
      cout << "Select data to modify for player '" << username << "'" << endl;
      gotoxyG(52, 16);
      cout << "[1] Username" << endl;
      gotoxyG(52, 17);
      cout << "[2] Password" << endl;
      gotoxyG(52, 18);
      cout << "[3] Poin" << endl;
      gotoxyG(52, 19);
      cout << "[4] Changes All" << endl;
      gotoxyG(52, 27);
      cout << "Enter choice";
      choice = getch();

      switch (choice)
      {
      case '1':
      {
      	system("cls");
      	titleG();
      	dis_modifyPlayerSelect();
      	
      	gotoxyG(40, 17);
        cout << "Enter new username: ";
        cin >> newUsername;
        break;
      }
      case '2':
      {
      	system("cls");
      	titleG();
      	dis_modifyPlayerSelect();
      	
      	gotoxyG(40, 17);
        cout << "Enter new password: ";
        cin >> newPassword;
        break;
      }
      case '3':
      {
      	system("cls");
      	titleG();
      	dis_modifyPlayerSelect();
      	
      	gotoxyG(40, 17);
        cout << "Enter new poin: ";
        cin >> newPoin;
        break;
      }
      case '4':
      {
      	system("cls");
      	titleG();
      	dis_modifyPlayer();
      	
      	gotoxyG(40, 16);
        cout << "Masukkan New Username : ";
        cin >> newUsername;
        gotoxyG(40, 17);
        cout << "Masukkan New Password : ";
        cin >> newPassword;
        gotoxyG(40, 18);
        cout << "Masukkan New Poin : ";
        cin >> newPoin;
        break;
      }
      default:
      {
        AlertG("Invalid choice!");
      }
      }
      // Melakukan Perubahan dimana player->username dll diganti menjadi = new
      player->username = newUsername;
      player->password = newPassword;
      player->poin = newPoin;
      // Melakukan Update Kedalam File
      SavePlayerChanges(username, newUsername, newPassword, newPoin);
    } while (choice < 1 || choice > 4);

    return false;
  }

  // melakukan referensi kedalam username tanpa menggubah username tersebut
  bool deletePlayer(const string &username)
  { // Fungsi Admin
    // Membuat Pointer berada pada current yang dimana current merupakan head
    Node *current = head;
    // Membuat Pointer prev berada pada kondisi Kosong
    Node *prev = nullptr;

    while (current && current->username != username)
    {
      // Memperbarui Prev agar selalu sama dengan curret -> untuk penghapusands
      prev = current;
      current = current->next;
    }

    // kondisi jika tidak menemukan player maka false
    if (!current)
    {
      dis_searchmodplayer();
      gotoxyG(39,16);
      cout << "Player with username '" << username << "' not found!" << endl;
      return false;
    }

    // Kondisi Penghapusan Node berdasarkan Posisinya
    if (!prev)
    {
      // Kondisi jika pemain yang dihapus berada di head maka head->next
      head = current->next;
    }
    else
    {
      // Memperbarui pointer next dari node sebelumnya (prev) untuk melewatkan node yang akan dihapus dan menunjuk langsung ke node setelahnya
      prev->next = current->next;
    }

    // Melakukan Pengahapusan Curret
    delete current;
    current = nullptr;
    // Memeperbarui data pada File
    ClearAndRewritePlayers();
    
    dis_delplayerG();
    gotoxyG(39,16);
    
    cout << "Player '" << username << "' deleted successfully!" << endl;
    return true;
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
	
	gotoxyG(55,13);
    cout << "-=TOP 10=-" << endl;
    // min 10 merupakan agar data yang tertampil pada perulangan memiliki max limit 10
    for (int i = 0; i < min(10, (int)players.size()); ++i)
    {
    	gotoxyG(42,14+i);
      	cout << i + 1 << ". " << players[i].username << " - " << players[i].poin << endl;
    }
  }

private:
  // Fungsi Menulis Ulang Data Pemain
  void ClearAndRewritePlayers()
  {
    // Kondisi menulis dan Memotong data
    ofstream dataFile("players.dat", ios::out | ios::trunc);

    if (dataFile.is_open())
    {
      // Memposisikan curret pada head
      Node *current = head;
      // Melakukan Perulangan sampai curret habis
      while (current)
      {
        dataFile << current->username << "," << current->password << "," << current->poin << endl;
        current = current->next;
      }
    }
    else
    {
      AlertG("Failed to clear and rewrite player data!");
    }

    dataFile.close();
  }

  void SavePlayerChanges(const string &username, const string &newUsername, const string &newPassword, int newPoin)
  {
    // Berada Pada Mode Menulis
    ofstream dataFile("players.dat", ios::out);

    if (dataFile.is_open())
    {
      // Perulangan Sederhana dimana Player berada pada head; lalu sampai data player habis; player berpindah ke next
      for (Node *player = head; player; player = player->next)
      {
        // Jika pada Perulanggan tersebut menemukan Player
        if (player->username == username)
        {
          // Operator Ternary
          // Pada Kondisi ini akan dilakukan Pengecekan apakah newUsername kosong jika iya player->username akan ditulis jika tidak newUsername yang akan ditulis
          dataFile << (newUsername.empty() ? player->username : newUsername) << ","
                   << (newPassword.empty() ? player->password : newPassword) << ","
                   << (newPoin == -1 ? player->poin : newPoin) << endl;
        }
        else
        {
          // Jika tidak Menemukan mana yang akan diubah Maka Akan Ditambahkan Sebagai Data Baru
          dataFile << player->username << "," << player->password << "," << player->poin << endl;
        }
      }

      AlertG("Player data saved successfully!");
      dataFile.close();
    }
    else
    {
      AlertG("Failed to save player data!");
    }
  }

  void LoadPlayerFromFile()
  {
    // Posisi akan Dipindahkan Pada index ke 0 pada file
    dataFile.seekg(0);
    string line, username, password, strPoin;
    int poin;

    while (getline(dataFile, line))
    {
      // Objek stringstream bernama ss dibuat untuk memproses baris data line
      stringstream ss(line);
      getline(ss, username, ',');
      getline(ss, password, ',');
      getline(ss, strPoin);
      // merubah string ke dalam int
      poin = stoi(strPoin);

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

  void SavePlayerToFile(string username, string password, int poin)
  {
    ofstream dataFile;
    // pada mode append dimana data akan ditulis pada akhir tanpa menimpa data yang sudah ada
    dataFile.open("players.dat", ios::app);
    if (dataFile.is_open())
    {
      dataFile << username << "," << password << "," << poin << endl;
    }
    else
    {
      AlertG("Data Tidak Tersimpan!");
    }
  }
};

#endif
