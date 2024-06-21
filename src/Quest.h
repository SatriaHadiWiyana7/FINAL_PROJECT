#ifndef QUEST_h
#define QUEST_h

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
#include "displayQuest.h"
using namespace std;

class Quest
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
  const int JUMLAH_SOAL = 1;

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
  void PlayGame(int Type, Node &playerNode)
  {
    int Timer;
    // Pada Awal Hapus Semua data lalu Load kembali data
    ClearData();
    if (Type == 1)
    {
      PlaySound(TEXT("sounds/backsong.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
      LoadAllData_Easy();
      Timer = 10;
    }
    else if (Type == 2)
    {
      PlaySound(TEXT("sounds/backsong.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
      LoadAllData_Medium();
      Timer = 5;
    }
    else if (Type == 3)
    {
      PlaySound(TEXT("sounds/backsong.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
      LoadAllData_Hard();
      Timer = 3;
    }
    else if (Type == 4)
    {
      PlaySound(TEXT("sounds/backsong.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
      LoadAllData_God();
      Timer = 2;
    }
    else
    {
      AlertQ("Anda Menemukan Hidden Quest");
    }

    system("cls");
    string Jawaban, tempJawaban;
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
          dis_quest();

          gotoxyQ(18, 5);
          cout << "Name : " << playerNode.GetUsername() << endl;
          string question = Questions.Soal[index];
          int lineCount = 0;
          for (int j = 0; j < question.size(); j++)
          {
            if (question[j] == '|')
            {
              lineCount++;
              gotoxyQ(18, 12 + lineCount);
            }
            else
            {
              cout << question[j];
            }
          }
          gotoxyQ(40, 20);
          cout << "Poin Benar : " << Questions.Benar[index] << endl;
          gotoxyQ(60, 20);
          cout << "Poin Salah : " << "-" << Questions.Salah[index] << endl;

          int waktuSisa = Timer; // Set Default Time
          thread timerThread([&waktuSisa]()
                             {
            while (waktuSisa > 0) {
              this_thread::sleep_for(chrono::seconds(1)); // Chrono berguna untuk memanipulasi waktu 1 detik berfungsi untuk membatasi waktu
              waktuSisa--;

              if (waktuSisa == 0) {
              	gotoxyQ(47,13);
              	cout << "+----------------------+";
                gotoxyQ(47,14);
				cout << "| W A K T U  H A B I S |";
                gotoxyQ(47,15);
				cout << "+----------------------+";
              }
            } });

          // Kondisi ini berfungsi agar ketika soal keluar pertama kita dapat Menjawab Soal Tersebut
          if (i == 0)
          {
            cin.ignore();
          }

          // Input Jawaban

          gotoxyQ(18, 24);
          getline(cin, tempJawaban);
          transform(tempJawaban.begin(), tempJawaban.end(), tempJawaban.begin(), ::tolower);
          Jawaban = tempJawaban;

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
      PlaySound(TEXT("sounds/game_clear.wav"), NULL, SND_FILENAME | SND_ASYNC);
      Total_Score = Score_Benar - Score_Salah;
      dis_score();
      gotoxyQ(43, 8);
      cout << "Nama Pemain : " << playerNode.GetUsername() << endl;
      gotoxyQ(43, 9);
      cout << "Total Soal....................  " << Total_Soal << endl;
      gotoxyQ(43, 10);
      cout << "Soal Tidak Terjawab...........  " << Soal_TidakTerjawab << endl;
      gotoxyQ(43, 11);
      cout << "Jawaban Benar (" << Jawaban_Benar << ") -> Poin.....  " << Score_Benar << endl;
      gotoxyQ(43, 12);
      cout << "Jawaban Salah (" << Jawaban_Salah << ") -> Poin..... -" << Score_Salah << endl;
      gotoxyQ(43, 13);
      cout << "Skor..........................  " << Total_Score << endl;

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
      gotoxyQ(47, 15);
      cout << "Terima kasih telah bermain!" << endl;

      gotoxyQ(50, 17);
      cout << "Ingin bermain ulang?";
      char pilihan;
      pilihan = getch();

      if (tolower(pilihan) != 'y' && tolower(pilihan) != 'n')
      {
        AlertQ("Pilihan tidak valid.\nMasukkan y/n");
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

  bool penuh()
  {
    if (Antrian.tail == max)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void LoadAllData_Easy()
  {
    ifstream File;
    File.open("Questions_Easy.dat", ios::in);

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
      AlertQ("Error: Gagal membuka file Questions.dat.");
    }
  }

  void LoadAllData_Medium()
  {
    ifstream File;
    File.open("Questions_Medium.dat", ios::in);

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
      AlertQ("Error: Gagal membuka file Questions.dat.");
    }
  }

  void LoadAllData_Hard()
  {
    ifstream File;
    File.open("Questions_Hard.dat", ios::in);

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
      AlertQ("Error: Gagal membuka file Questions.dat.");
    }
  }

  void LoadAllData_God()
  {
    ifstream File;
    File.open("Questions.God", ios::in);

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
      AlertQ("Error: Gagal membuka file Questions.dat.");
    }
  }
};

#endif
