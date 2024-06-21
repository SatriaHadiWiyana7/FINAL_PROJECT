#ifndef ADMIN_H
#define ADMIN_H

#include "game.h"
#include "displayAdmin.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

class Admin
{
private:
    struct NodeAdmin
    {
        string username;
        string password;
        int position;
        NodeAdmin *left;
        NodeAdmin *right;
        NodeAdmin *parent;

        // Constructor
        NodeAdmin(string username, string password, int position) : username(username), password(password), position(position), left(nullptr), right(nullptr) {}

        // Fungsi untuk Mengembalikan Username tanpa menggubah username
        string GetUsername() const
        {
            return username;
        }

        // Fungsi untuk Mengembalikan Password tanpa menggubah password
        string GetPassword() const
        {
            return password;
        }

        // Fungsi untuk Mengembalikan Position tanpa menggubah position
        int GetPosition() const
        {
            return position;
        }
    };
    // Inisialisasi
    NodeAdmin *root;
    // Inisialisasi game dengan mereferensi game
    Game &game;

public:
    // Merupakan sebuah Inisialisasi Admin dimana ia mereferensi kedalam game dan membuat root dalam keadaan nullptr, dan membuat isadminloggedin menjadi false
    Admin(Game &game) : root(nullptr), game(game)
    {
        // Melakukan Load wifi
        LoadFromFile();
    }

    // Fungsi untuk Insert soal
    bool Insert_Easy(string soal, string kunci, int benar, int salah)
    {
        ofstream dataFile;
        // Dalam mode append
        dataFile.open("Questions_Easy.dat", ios::app);
        if (dataFile.is_open())
        {
            dataFile << soal << "," << kunci << "," << benar << "," << salah << endl;
            AlertAdmin("Questions Berhasil Disimpan");
        }
        else
        {
            AlertAdmin("Questions Tidak Tersimpan!");
        }
    }
    
    // Fungsi untuk Insert soal
    bool Insert_Medium(string soal, string kunci, int benar, int salah)
    {
        ofstream dataFile;
        // Dalam mode append
        dataFile.open("Questions_Medium.dat", ios::app);
        if (dataFile.is_open())
        {
            dataFile << soal << "," << kunci << "," << benar << "," << salah << endl;
            AlertAdmin("Questions Berhasil Disimpan");
        }
        else
        {
            AlertAdmin("Questions Tidak Tersimpan!");
        }
    }
    
        // Fungsi untuk Insert soal
    bool Insert_Hard(string soal, string kunci, int benar, int salah)
    {
        ofstream dataFile;
        // Dalam mode append
        dataFile.open("Questions_Hard.dat", ios::app);
        if (dataFile.is_open())
        {
            dataFile << soal << "," << kunci << "," << benar << "," << salah << endl;
            AlertAdmin("Questions Berhasil Disimpan");
        }
        else
        {
            AlertAdmin("Questions Tidak Tersimpan!");
        }
    }
    
        // Fungsi untuk Insert soal
    bool Insert_God(string soal, string kunci, int benar, int salah)
    {
        ofstream dataFile;
        // Dalam mode append
        dataFile.open("Questions_God.dat", ios::app);
        if (dataFile.is_open())
        {
            dataFile << soal << "," << kunci << "," << benar << "," << salah << endl;
            AlertAdmin("Questions Berhasil Disimpan");
        }
        else
        {
            AlertAdmin("Questions Tidak Tersimpan!");
        }
    }

    // Fungsi Melakukan Clear Player All
    void ClearPlayerData()
    {
        // Dalam Mode Menulis dan Memotong
        ofstream playerFile("players.dat", ios::out | ios::trunc);

        if (playerFile.is_open())
        {
    		playerFile << "Default" << "," << "Default" << "," << 0;
            AlertAdmin("Player data cleared successfully!");
        }
        else
        {
            AlertAdmin("Error clearing player data!");
        }
        // Memanggil fungsi ClearALLNode untuk membersihkan struct yang terdapat pada game.h
        game.ClearAllNode();
        playerFile.close();
    }

    // Fungsi untuk mengAkses Root
    NodeAdmin *GetRoot() const
    {
        return root;
    }

    // Fungsi untuk Menampilkan Data Admin melalui paramater Username
    void AboutMe(string username)
    {
        // Memposisikan Current pada root
        NodeAdmin *current = root;
        // Kondisi akan terus berjalan sampai kondisi current == nullptr
        while (current != nullptr)
        {
            if (username == current->GetUsername())
            {
                // Display Username
                dis_Aboutme();
                gotoxyA(48,17);
                cout << "Username: " << current->GetUsername() << endl;
                // Display Position
                gotoxyA(48,18);
                cout << "Position: " << current->GetPosition() << endl;
                break;
            }
            // Kondisi Pencarian Kekiri
            else if (username < current->GetUsername()) // Berdasarkan Urutan Character pada Username
            {
                current = current->left;
            }
            // Kondisi pencarian Kekanan
            else
            {
                current = current->right;
            }
        }

        // Kondisi jika tidak terdapat username yang sama
        if (current == nullptr)
        {
        	dis_usrnotfound();
        	gotoxyA(42,16);
            cout << "Admin with username " << username << " not found." << endl;
        }
    }

    // Fungsi untuk menambahkan Admin baru
    void AddNode(string username, string password, int position)
    {
        // Fungsi Mencari Apakah terdapat username yang mirip
        if (SearchUsername(username))
        {
            AlertAdmin("Username already exists!!");
            return;
        }

        // Membuat dan Menambahkan Admin baru
        NodeAdmin *newNode = new NodeAdmin(username, password, position);
        // Melakukan Save ke Admin.dat
        SaveToFile(username, password, position);

        if (root == nullptr)
        {
            root = newNode;
            return;
        }

        // Memposisikan current pada root
        NodeAdmin *current = root;
        // Menggunakan Parent untuk Tempat Penyimpanan Sementara
        NodeAdmin *parent;

        // Fungsi ini Terus Berjalan sampai Node untuk admin baru
        while (true)
        {
            // Menyimpan nilai dalam current kedalam parent
            parent = current;
            // Kondisi untuk Menyimpan pada posisi Kiri
            if (username < current->GetUsername())
            {
                current = current->left;
                // Ketika bertemu dengan posisi current == nullptr
                if (current == nullptr)
                {
                    // Node baru ditambahkan
                    parent->left = newNode;
                    return;
                }
            }
            // Kondisi untuk Menyimpan Kekanan
            else
            {
                current = current->right;
                // Ketika bertemu dengan posisi current == nulptr
                if (current == nullptr)
                {
                    // Node baru ditambahkan
                    parent->right = newNode;
                    return;
                }
            }
        }
    }

    // Fungsi Menampilkan AllPlayers dengan mereferensi game
    void DisplayAllPlayers(Game &game)
    {
    	dis_allplayer();
    	gotoxyA(45,1);
        cout << "<- L I S T  O F  P L A Y E R ->" << endl;
        // Access head dengan object game
        Node *current = game.head;
		int index = 1;
		gotoxyA(0,5);
        while (current)
        {
            cout << index << ". Username: " << current->username << " | Score: " << current->poin << endl;
            current = current->next;
			index++;
        }
    }

    // Fungsi Mencari admin menggunakan paramater username
    bool SearchUsername(string username)
    {
        // Memposisikan current pada root
        NodeAdmin *current = root;
        while (current != nullptr)
        {
            // Melakukan Pengecekan  username
            if (username == current->GetUsername())
            {
                return true;
            }
            else if (username < current->GetUsername())
            {
                // Melakukan pengecekan kekiri
                current = current->left;
            }
            else
            {
                // Melakukan Pnegecekan kekanan
                current = current->right;
            }
        }
        return false;
    }

    int position(string username)
    {
        // Memposisikan current pada root
        NodeAdmin *current = root;

        // Melakukan perulangan sampai current nullptr
        while (current != nullptr)
        {
            // Jika username sama dengan username current
            if (username == current->GetUsername())
            {
                // Mengembalikan nilai position
                return current->GetPosition();
            }
            // Jika username < current
            else if (username < current->GetUsername())
            {
                // Current dipindahkan ke kiri
                current = current->left;
            }
            // Jika username > current
            else
            {
                // Current dipindahkan ke kanan
                current = current->right;
            }
        }

        // Menandakan bahwa username tidak ditemukan
        return -1;
    }

    // Fungsi Login Menggunakan paramater username dan password
    bool Login(string username, string password)
    {
            // Memposisikan current berada pada posisi root
            NodeAdmin *current = root;
            // Kondisi berulang sampai current == nullptr
            while (current != nullptr)
            {
                // Kondisi jika Menemukan username yang sama dengan posisi current
                if (username == current->GetUsername())
                {
                    // Melakukan Pengecekan apakah password sama
                    if (password == current->GetPassword())
                    {
                        // Login Berhasil
                        AlertAdmin("Login successful!");
                        cin.ignore();
                        return true;
                    }
                    // Kondisi Jika Salah
                    else
                    {
                        AlertAdmin("Incorrect password, Akses Ditolak");
                        cin.ignore();
                        return false;
                    }
                }
                // Melakukan Pengecekan Kekiri
                else if (username < current->GetUsername())
                {
                    current = current->left;
                }
                // Melakukan Pengecekan Kekanan
                else
                {
                    current = current->right;
                }
            }
            // Mengembalikan Nilai False Jika Tidak ada yang Sama
            return false;
    }

    // Fungsi untuk menampilkan Admin
    void PrintTree(NodeAdmin *node)
    {
        // Kondisi Jika Node dalam Keadaan Nullptr
        if (node == nullptr)
        {
            return;
        }
        // Kondisi untuk Mencetak Username dan Position
        cout << node->GetUsername() << ", " << node->GetPosition() << endl;
        // Kondisi ini akan secara rekunsif (Memanggil Dirinya sendiri) Secara in-Order
        // In-Order merupakan Fungsi pada Tree dimana dia akan Mengunjungi Node yang berada Pada Sebelah kiri sampai habis dan baru kekanan
        PrintTree(node->left);
        PrintTree(node->right);
    }

    // Fungsi untuk Menghapus Admin
    void RemoveAdmin(string username)
    {
        // Menghalau agar root tidak dapat dihapus
        if (username == "satria")
        {
            AlertAdmin("Data Diatas Tidak Dapat diHapus");
            // Mengembalikan Tanpa nilai
            return;
        }
        // Kondisi Melakukan Pencarian Username
        if (SearchUsername(username))
        {
            // Menempatkan nodetoDelete pada posisi root
            NodeAdmin *nodeToDelete = root;
            // Pada Perulanggan berikut mencari nodeToDelete sampai nullprt dan nodeToDelete->username tidak sama dengan username yang dihapus
            while (nodeToDelete != nullptr && nodeToDelete->GetUsername() != username)
            {
                // Kondisi Pengecekan ke Node Kiri
                if (username < nodeToDelete->GetUsername())
                {
                    nodeToDelete = nodeToDelete->left;
                }
                // Kondisi Pengecekan ke Node Kanan
                else
                {
                    nodeToDelete = nodeToDelete->right;
                }
            }

            // Kondisi Jika nodeToDelete tidak ketemu
            if (nodeToDelete == nullptr)
            {
            	dis_usrnotfound();
            	gotoxyA(42,16);
                cout << "Admin with username " << username << " not found." << endl;
                return;
            }

            // Peryataan untuk memerikasa apakah kiri dan kanan nullptr
            if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr)
            {
                // Kondisi jika hanya ada 1 Node
                if (nodeToDelete == root)
                {
                    root = nullptr;
                }
                // Kondisi Pencarikan Ke Node Sebelah Kiri
                // Parent mengacu pada Node
                else if (nodeToDelete == nodeToDelete->parent->left)
                {
                    nodeToDelete->parent->left = nullptr;
                }
                // Kondisi Pencarian Ke Node sebelah Kanan
                else
                {
                    nodeToDelete->parent->right = nullptr;
                }
                // Menghapus Memori nodeToDelete
                delete nodeToDelete;
            }
            // Kondisi jika Tree hanya Memiliki 1 Cabang
            else if (nodeToDelete->left == nullptr)
            {
                // Kondisi Jika Root adalah Yang dihapus maka Node pada sebelah kanan Akan Ditugaskan Menjadi Root
                if (nodeToDelete == root)
                {
                    root = nodeToDelete->right;
                }
                // Kondisi untuk Mengakses Node kiri
                else if (nodeToDelete == nodeToDelete->parent->left)
                {
                    // Mempromosikan Node Kanan untuk Mengantikan Posisinya
                    nodeToDelete->parent->left = nodeToDelete->right;
                }
                // Kondisi untuk Mengakses Node Kanan
                else
                {
                    // Mempromosikan Node Kanan untuk Mengantikan Posisinya
                    nodeToDelete->parent->right = nodeToDelete->right;
                }
                // Fungsi untuk Mengaantikan Node yang terhapus
                nodeToDelete->right->parent = nodeToDelete->parent;
                // Menghapus Memori nodeToDelete
                delete nodeToDelete;
            }
            else
            {
                // Meninisilasisasi Penerus pada Note Kanan
                NodeAdmin *successor = nodeToDelete->right;
                // Perulanggan dimana Akan terus berlanjut sampai node->kiri nullptr
                while (successor->left != nullptr)
                {
                    successor = successor->left;
                }

                successor->left = nodeToDelete->left;
                successor->left->parent = successor;

                // Ketika Root Terhapus
                if (nodeToDelete == root)
                {
                    // root akan digantikan dnegan successor
                    root = successor;
                }
                else if (nodeToDelete == nodeToDelete->parent->left)
                {
                    // Melakukan Penerusan node Pada node kiri
                    nodeToDelete->parent->left = successor;
                }
                else
                {
                    // Melakukan Penerusan node Pada node kiri
                    nodeToDelete->parent->right = successor;
                }

                successor->parent = nodeToDelete->parent;
                // Menghapus Memori nodeToDelete
                delete nodeToDelete;
            }

            // Melakukan Update pada File Admin.dat
            UpdateFile();
            dis_delsuccess();
            gotoxyA(42,16);
            cout << "Admin with username " << username << " deleted successfully!" << endl;
        }
        else
        {
            // Kondisi Jika Tidak Terdapat Username
            dis_usrnotfound();
            gotoxyA(42,16);
            cout << "Admin with username " << username << " not found." << endl;
        }
    }

    // Fungsi untuk melakukan modifikasi Admin
    void modifyAdmin(string username)
    {
        // Proses Pencarian Admin dengan Username
        NodeAdmin *node = FindNode(username);
        // Kondisi Jika node keadaan Kosong
        if (node == nullptr)
        {
        	dis_usrnotfound();
            gotoxyA(42,16);
            cout << "Admin with username " << username << " not found." << endl;
            return;
        }

        // Inisialisasi Variabel
        string newUsername, newPassword;
        int newPosition;
		dis_modify();

        // Proses Memasukkan Modify
        gotoxyA(40, 16);
        cout << "Enter new username: ";
        cin >> newUsername;
		
		gotoxyA(40, 17);
        cout << "Enter new password: ";
        cin >> newPassword;

		gotoxyA(40, 18);
        cout << "Enter new position: ";
        cin >> newPosition;
        
        if(newPosition == 0) {
        	newPosition = 1;
        	// Proses Memeperbarui Node
	        node->username = newUsername;
	        node->password = newPassword;
	        node->position = newPosition;
	
	        // Melakukan Update File
	        UpdateFile();
	        dis_modsuccess();
	        gotoxyA(42,16);
	        cout << "Admin with username " << username << " modified successfully!" << endl;
		} else {
	        // Proses Memeperbarui Node
	        node->username = newUsername;
	        node->password = newPassword;
	        node->position = newPosition;
	
	        // Melakukan Update File
	        UpdateFile();
	        dis_modsuccess();
	        gotoxyA(42,16);
	        cout << "Admin with username " << username << " modified successfully!" << endl;			
		}
    }

    // ungsi menambahkan Player Baru
    void AddPlayerFromAdmin(string username, string password)
    {
        // Pengecekan apakah username sudah terbuat
        if (game.IsUsernameExist(username))
        {
            AlertAdmin("Username Sudah Terbuat\nBuat lagi!");
            return;
        }

        // Inisialisai node pada player
        Node newPlayer;
        newPlayer.username = username;
        newPlayer.password = password;
        newPlayer.poin = 0;

        // Menambahkan Player baru kegame memakai Vector
        game.players.push_back(newPlayer);
        // Melakukan Save Pada players.dat
        SavePlayerToFile(username, password, 0);
    }

private:
    // Fungsi untuk melkukan Save pada Player
    void SavePlayerToFile(string username, string password, int poin)
    {
        ofstream dataFile;
        dataFile.open("players.dat", ios::app);
        if (dataFile.is_open())
        {
            dataFile << username << "," << password << "," << poin << endl;
            AlertAdmin("Data pemain berhasil disimpan!");
        }
        else
        {
            AlertAdmin("Data Tidak Tersimpan!");
        }
    }

    // Fungsi menemukan Admin dengan mengembalikan semua nilai pada admin
    NodeAdmin *FindNode(string username)
    {
        // Memposisikan current pada root
        NodeAdmin *current = root;
        // Perulanggan sampai current nullptr
        while (current != nullptr)
        {
            // Ketika Menemukan current
            if (username == current->GetUsername())
            {
                // Mengembalikan Nilai current
                return current;
            }
            // Pengecekan Kekiri
            else if (username < current->GetUsername())
            {
                current = current->left;
            }
            // Pengecekan Kekanan
            else
            {
                current = current->right;
            }
        }

        return nullptr; // return nullptr
    }

    // Fungsi Update Tree Pada Admin
    void UpdateFile()
    {
        // Dalam Mode menulisa dan menghapus file
        ofstream adminFile("admin.dat", ios::out | ios::trunc);
        if (adminFile.is_open())
        {
            // Melakukan Penulisan terhadap Root dulu
            if (root != nullptr)
            {
                adminFile << root->GetUsername() << "," << root->GetPassword() << "," << root->GetPosition() << endl;
            }
            // Melakukan Penulisan terhadap Node kiri dan kanan
            UpdateFileHelper(root->left, adminFile);
            UpdateFileHelper(root->right, adminFile);
        }
        else
        {
            AlertAdmin("Error updating admin file.");
        }
        adminFile.close();
    }

    // Fungsi tambahan untuk membantu di Fungsi UpdateFile yang dipanggil secara rekunsif(Berulangan secara berurutan atau Memanggil dirinya sendiri)
    void UpdateFileHelper(NodeAdmin *node, ofstream &adminFile)
    {
        // Jika pada node nullprt maka return untuk kembali
        if (node == nullptr)
        {
            return;
        }

        // Menulis pada node kiri
        UpdateFileHelper(node->left, adminFile);
        // Menulis pada admin.dat
        adminFile << node->GetUsername() << "," << node->GetPassword() << "," << node->GetPosition() << endl;
        // Menulis pada node kanan
        UpdateFileHelper(node->right, adminFile);
    }

    // Berfungsi untuk Mencari pada Tree
    NodeAdmin *GetInorderSuccessor(NodeAdmin *node)
    {
        // Memposisikan current pada node
        NodeAdmin *current = node;
        // Melakukan Perulanggan
        while (current != nullptr && current->left != nullptr)
        {
            // Memindahkan current pada node kiri
            current = current->left;
        }
        // mengembalikan nilai current
        return current;
    }

    // Fungsi melakukan Save pada Admin.dat
    void SaveToFile(string username, string password, int position)
    {
        ofstream adminFile;
        // Mode append
        adminFile.open("admin.dat", ios::app);
        if (adminFile.is_open())
        {
            adminFile << username << "," << password << "," << position << endl;
        }
        else
        {
            AlertAdmin("Data Tidak Tersimpan!");
        }
        adminFile.close();
    }

    // Fungsi melakukan Load Data Admin
    bool LoadFromFile()
    {
        // Mode membaca
        ifstream adminFile("admin.dat");
        if (!adminFile.is_open())
        {
            AlertAdmin("Data Eror");
            return false;
        }

        string line;
        while (getline(adminFile, line))
        {
            // Objek stringstream bernama ss dibuat untuk memproses baris data line
            stringstream ss(line);
            // Inisialisasi Variabel
            string username, password, s_position;
            int position;
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, s_position);
            // Merubah String kedalam Int
            position = stoi(s_position);

            // Fungsi membuat admin baru lalu menambahkan dengan username. password dan position yang telah terload
            NodeAdmin *newNode = new NodeAdmin(username, password, position);

            // Kondisi memasukan Data baru kedalam tree
            if (root == nullptr) // Jika pada root kosong
            {
                root = newNode;
            }
            else
            {
                // Memposisikan Current pada posisi root
                NodeAdmin *current = root;
                // Melakukan inisialisasi parent menjadi 0
                NodeAdmin *parent = nullptr;

                // Kondisi berjalan sampai current nullptr
                while (current != nullptr)
                {
                    // Inisialisai parent menjadi current
                    parent = current;
                    // jika username < current
                    if (username < current->GetUsername())
                    {
                        // maka current akan dipindahkan ke kiri
                        current = current->left;
                    }
                    // sebaliknya
                    else
                    {
                        // maka current akan dipindahkan kenan
                        current = current->right;
                    }
                }

                // Kondisi jika username < parent
                if (username < parent->GetUsername())
                {
                    // maka Node baru akan disimpan pada parent kiri
                    parent->left = newNode;
                }
                else
                {
                    // Maka Node baru akan disimpan pada parent kanan
                    parent->right = newNode;
                }
            }
        }
        adminFile.close();
        return true;
    }
};

#endif
