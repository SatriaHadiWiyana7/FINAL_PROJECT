#ifndef QUEST_h
#define QUEST_h

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm> // fungsi shuffle
#include <fstream>
#define max 10

#include "game.h"
using namespace std;

class Quest
{
public:
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
    // Batasan jumlah soal
    const int JUMLAH_SOAL = 5;

    void PlayGame(string username, Player &player)
    {
        system("cls");
        char Jawaban[200];
        int Score = 0, Jawaban_Benar = 0, Jawaban_Salah = 0, Total_Soal = 0;

        // Variabel untuk menyimpan status memulai ulang
        bool restart = true; // true nilai default

        while (restart) // Looping selama pemain ingin bermain ulang
        {
            // Mengacak soal dan hanya menampilkan 5
            vector<int> indexSoal(5); // Mengubah ukuran vector menjadi 5
            for (int i = 0; i < 5; i++)
            {
                indexSoal[i] = i;
            }
            random_shuffle(indexSoal.begin(), indexSoal.end());

            for (int i = 0; i < 5; i++)
            {
                int index = indexSoal[i]; // index merupakan soal setelah diacak pada fungsi diatas
                if (!used[index])         // Periksa apakah soal belum pernah keluar
                {
                    system("cls");
                    cout << "Soal " << i + 1 << endl;
                    cout << Questions.Soal[index] << endl;
                    cout << "Poin Benar : " << Questions.Benar[index] << endl;
                    cout << "Poin Salah : " << "-" << Questions.Salah[index] << endl;
                    cout << "Masukkan Jawaban Anda : ";
                    cin >> Jawaban;

                    if (Jawaban == Questions.Kunci[index])
                    {
                        Score += Questions.Benar[index];
                        Jawaban_Benar++;
                        Total_Soal++;
                        used[index] = true; // Soal sudah keluar
                    }
                    else if (Jawaban != Questions.Kunci[index])
                    {
                        Score -= Questions.Salah[index];
                        Jawaban_Salah++;
                        Total_Soal++;
                        used[index] = true; // Soal sudah Keluar
                    }
                    else
                    {
                        cout << "Skip Soal!" << endl;
                    }
                }
            }

            system("cls");
            cout << "**Hasil Permainan**" << endl;
            cout << "Nama Pemain : " << username << endl;
            cout << "Skor : " << Score << endl;
            cout << "Jawaban Benar : " << Jawaban_Benar << endl;
            cout << "Jawaban Salah : " << Jawaban_Salah << endl;
            cout << "Total Soal : " << Total_Soal << endl;

            cout << "\nIngin bermain ulang? (y/n): ";
            char pilihan;
            cin >> pilihan;

            if (pilihan != 'y' && pilihan != 'n')
            {
                cout << "Pilihan tidak valid. Masukkan y/n." << endl;
                continue;
            }

            if (pilihan == 'n') // Berhenti bermain
            {
                restart = false;
            }
            else // Memulai ulang game
            {
                // Reset
                for (int i = 0; i < Antrian.tail; i++)
                {
                    used[i] = false;
                }
                Score = 0;
                Jawaban_Benar = 0;
                Jawaban_Salah = 0;
                Total_Soal = 0;
            }
        }

        // Menambahkan skor ke player
        player.poin += Score;

        cout << "\nTerima kasih telah bermain!" << endl;
    }

    void LoadAllData()
    {
        ifstream File;
        File.open("Questions_Easy.dat", ios::in);

        if (File.is_open())
        {
            string line, soal, kunci, strBenar, strSalah;
            int benar, salah;

            while (getline(File, line)) // Membaca baris demi baris
            {
                stringstream ss(line); // Memisahkan data dalam baris dengan koma

                getline(ss, soal, ',');
                getline(ss, kunci, ',');
                getline(ss, strBenar, ',');
                getline(ss, strSalah, ',');
                benar = stoi(strBenar);
                salah = stoi(strSalah);

                // Menyimpan data soal
                Questions.Soal[Antrian.tail] = soal;
                Questions.Kunci[Antrian.tail] = kunci;
                Questions.Benar[Antrian.tail] = benar;
                Questions.Salah[Antrian.tail] = salah;

                // Menyimpan status soal
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