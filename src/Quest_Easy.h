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

    bool JawabanKosong(string jawaban)
    {
        return jawaban.empty();
    }

    void PlayGame(Node &playerNode)
    {
        system("cls");
        string Jawaban;
        int Total_Score = 0, Score_Salah = 0, Score_Benar = 0, Jawaban_Benar = 0, Jawaban_Salah = 0, Soal_TidakTerjawab = 0, Total_Soal = 0;

        const int JUMLAH_SOAL = 5;

        bool restart = true; // Start game by default

        thread timerThread;

        while (restart)
        {
            // menginisialisai vector Soal menjadi bentuk int
            vector<int> indexSoal(JUMLAH_SOAL);
            for (int i = 0; i < JUMLAH_SOAL; i++)
            {
                indexSoal[i] = i;
            }
            // Berfungsi untuk melakukan Shuffle kepada Vector soal dari Awal sampai KeAkhir
            random_shuffle(indexSoal.begin(), indexSoal.end());

            for (int i = 0; i < JUMLAH_SOAL; i++)
            {
                int index = indexSoal[i];
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
                    // thread merupakan program unit ringan yang memungkinkan berjalan secara bersamaan
                    thread timerThread([&waktuSisa]()
                                       {
                        while (waktuSisa > 0) {
                            //chrono berfungsi menghitung waktu
                            this_thread::sleep_for(chrono::seconds(1));
                        waktuSisa--;
                        }
                        cout << "\nWaktu habis!" << endl; });

                    // fungsi dibawah ini berguna untuk perulangan pertama agar kita dapat melakukan input jawaban
                    // dikarenakan jika tidak menggunakan cin.ignore() maka getline(cin,Jawaban) akan terlewati
                    if (i == 0)
                    {
                        cin.ignore();
                    }
                    cout << "Masukkan Jawaban Anda : ";
                    getline(cin, Jawaban);

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
            game.UpdatePlayerToFile(playerNode.username, playerNode.password, playerNode.poin);

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
        system("pause");
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