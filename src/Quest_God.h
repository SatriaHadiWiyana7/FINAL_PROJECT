#ifndef QUESTGod_h
#define QUESTGod_h

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <fstream>
#define max 100

#include "game.h"
using namespace std;

class Quest_God
{
public:
  Game game;
  fstream QuestFile;

  struct Question
  {
    string Soal[max];
    string Kunci[max];
    int Benar[max];
    int Salah[max];
  } Questions;

  struct QUEUE
  {
    int tail;
    int head;

    Question Questions[max];
  } Antrian;

  bool used[max];
  const int JUMLAH_SOAL = 6;

  // kondisi pengecekan apakah string jawaban berupa string kosong
  bool JawabanKosong(string jawaban)
  {
    return jawaban.empty();
  }
  // Fungsi Untuk Melakukan Radom Soal
  void ShuffleQuestions()
  {
    // Questions.soal merupakan Alamat Array Awal
    // Questions.soal + Antrian.tail merupakan Alamat Terakir pada Array yang akan di acak
    // random_shuffle merupakan fungsi standart yang berasar dari library <algorithm>
    random_shuffle(Questions.Soal, Questions.Soal + Antrian.tail);
  }

  // Fungsi Utama menggunakan Paramater Node &playerNode
  void PlayGame(Node &playerNode)
  {
    // Pada Awal Hapus Semua data lalu Load kembali data
    ClearData();
    LoadAllData();

    system("cls");
    string Jawaban;
    int Total_Score = 0, Score_Salah = 0, Score_Benar = 0, Jawaban_Benar = 0, Jawaban_Salah = 0, Soal_TidakTerjawab = 0, Total_Soal = 0;

    bool restart = true; // Start game by default

    // tread merupakan mikro program yang bisa berjalan dibalik program utama
    thread timerThread; // Thread untuk mengatur waktu per soal

    while (restart)
    {
      ShuffleQuestions(); // Mengacak soal

      for (int i = 0; i < JUMLAH_SOAL; i++)
      {
        int index = i;
        if (!used[index])
        {
          system("cls");
          cout << "Nama Pemain : " << playerNode.GetUsername() << endl;
          cout << "==========================" << endl;
          cout << "Soal " << i + 1 << endl;
          cout << "Soal : " << Questions.Soal[index] << endl;
          cout << "Poin Benar : " << Questions.Benar[index] << endl;
          cout << "Poin Salah : " << "-" << Questions.Salah[index] << endl;

          int waktuSisa = 5; // Set Default Time
          thread timerThread([&waktuSisa]()
                             {
            while (waktuSisa > 0) {
              this_thread::sleep_for(chrono::seconds(1)); // Chrono berguna untuk memanipulasi waktu 1 detik berfungsi untuk membatasi waktu
              waktuSisa--;

              if (waktuSisa == 0) {
                cout << "\nWaktu habis!" << endl;
              }
            } });

          // Kondisi ini berfungsi agar ketika soal keluar pertama kita dapat Menjawab Soal Tersebut
          if (i == 0)
          {
            cin.ignore();
          }

          // Input Jawaban
          cout << "Masukkan Jawaban Anda : ";
          getline(cin, Jawaban);

          // Kondisi Pengecekan
          if (!JawabanKosong(Jawaban))
          {
            if (Jawaban == Questions.Kunci[index])
            {
              Score_Benar += Questions.Benar[index];
              Jawaban_Benar++;
              Total_Soal++;
              used[index] = true;
            }
            else if (Jawaban != Questions.Kunci[index])
            {
              Score_Salah += Questions.Salah[index];
              Jawaban_Salah++;
              Total_Soal++;
              used[index] = true;
            }
          }
          else
          {
            Soal_TidakTerjawab++;
            Total_Soal++;
            used[index] = true;
          }
          waktuSisa = 1;
          timerThread.join();
        }
      }

      // Menampilkan Hasil Score
      system("cls");
      Total_Score = Score_Benar - Score_Salah;
      cout << "**Hasil Permainan**" << endl;
      cout << "Nama Pemain : " << playerNode.GetUsername() << endl;
      cout << "Skor : " << Total_Score << endl;
      cout << "Jawaban Benar : " << Jawaban_Benar << " -> Poin :" << Score_Benar << endl;
      cout << "Jawaban Salah : " << Jawaban_Salah << " -> Poin :-" << Score_Salah << endl;
      cout << "Soal Tidak Terjawab : " << Soal_TidakTerjawab << endl;
      cout << "Total Soal : " << Total_Soal << endl;

      // Menambahkan skor ke player
      if (Total_Score <= 0)
      {
        playerNode.poin += Total_Score;
      }
      else if (Total_Score >= 0)
      {
        playerNode.poin += Total_Score;
      }

      if (playerNode.poin <= 0)
      {
        playerNode.poin = 0;
      }
      // Data Player akan TerUpdate pada Fungsi yang terdapat pada game
      game.UpdatePlayerToFile(playerNode.username, playerNode.password, playerNode.poin);
      cout << "\nTerima kasih telah bermain!" << endl;

      cout << "Ingin bermain ulang? (y/n): ";
      char pilihan;
      cin >> pilihan;

      if (pilihan != 'y' && pilihan != 'n')
      {
        cout << "Pilihan tidak valid. Masukkan y/n." << endl;
        continue;
      }

      if (pilihan == 'n') // Berhenti bermain
      {
        // Reset
        for (int i = 0; i < Antrian.tail; i++)
        {
          used[i] = false;
        }
        Total_Score = 0;
        Score_Benar = 0;
        Score_Salah = 0;
        Jawaban_Benar = 0;
        Jawaban_Salah = 0;
        Total_Soal = 0;

        restart = false;
      }
      else // Memulai ulang game
      {
        // Reset
        for (int i = 0; i < Antrian.tail; i++)
        {
          used[i] = false;
        }
        Total_Score = 0;
        Score_Benar = 0;
        Score_Salah = 0;
        Jawaban_Benar = 0;
        Jawaban_Salah = 0;
        Total_Soal = 0;
      }
    }
  }

  void ClearData()
  {
    // Reset Antrian
    Antrian.tail = 0;
    Antrian.head = 0;

    // Reset used
    for (int i = 0; i < max; i++)
    {
      used[i] = false;
    }

    // Kosongkan data Questions
    for (int i = 0; i < max; i++)
    {
      Questions.Soal[i] = "";
      Questions.Kunci[i] = "";
      Questions.Benar[i] = 0;
      Questions.Salah[i] = 0;
    }
  }

  void LoadAllData()
  {
    ifstream File;
    File.open("Questions.dat", ios::in);

    if (File.is_open())
    {
      string line, soal, kunci, strBenar, strSalah;
      int benar, salah;

      while (getline(File, line))
      {
        // Objek stringstream bernama ss dibuat untuk memproses baris data line
        stringstream ss(line);
        getline(ss, soal, ',');
        getline(ss, kunci, ',');
        getline(ss, strBenar, ',');
        getline(ss, strSalah, ',');
        // Merubah dari string ke Int
        benar = stoi(strBenar);
        salah = stoi(strSalah);

        // Store data
        Questions.Soal[Antrian.tail] = soal;
        Questions.Kunci[Antrian.tail] = kunci;
        Questions.Benar[Antrian.tail] = benar;
        Questions.Salah[Antrian.tail] = salah;

        // Mark question as loaded
        used[Antrian.tail] = false;

        Antrian.tail++;
      }

      File.close();
    }
    else
    {
      cout << "Error: Gagal membuka file Questions.dat." << endl;
    }
  }
};

#endif
