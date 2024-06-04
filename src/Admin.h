#ifndef ADMIN_H
#define ADMIN_H

#include "game.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

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

        NodeAdmin(string username, string password, int position) : username(username), password(password), position(position), left(nullptr), right(nullptr) {}

        string GetUsername() const
        {
            return username;
        }

        string GetPassword() const
        {
            return password;
        }

        int GetPosition() const
        {
            return position;
        }
    };
    NodeAdmin *root;
    bool isAdminLoggedIn;

public:
    Admin() : root(nullptr), isAdminLoggedIn(false)
    {
        LoadFromFile();
    }

    NodeAdmin *GetRoot() const
    { // Fungsi untuk access root node
        return root;
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
            cout << "Data pemain berhasil disimpan!" << endl;
        }
        else
        {
            cout << "Data Tidak Tersimpan!" << endl;
        }
    }

    // Fungsi menemukan Admin dengan mengembalikan semua nilai pada admin
    NodeAdmin *FindNode(string username)
    {
        NodeAdmin *current = root;
        while (current != nullptr)
        {
            if (username == current->GetUsername())
            {
                return current;
            }
            else if (username < current->GetUsername())
            {
                current = current->left;
            }
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
        // Dalam Mode Memotong
        ofstream adminFile("admin.dat", ios::out | ios::trunc);
        if (adminFile.is_open())
        {
            if (root != nullptr)
            {
                adminFile << root->GetUsername() << "," << root->GetPassword() << "," << root->GetPosition() << endl;
            }
            // Pada fungsi ini membantu untuk melakukan save pada kiri dan kanan
            UpdateFileHelper(root->left, adminFile);
            UpdateFileHelper(root->right, adminFile);
        }
        else
        {
            cout << "Error updating admin file." << endl;
        }
        adminFile.close();
    }

    // Fungsi tambahan untuk membantu di Fungsi UpdateFile
    void UpdateFileHelper(NodeAdmin *node, ofstream &adminFile)
    {
        if (node == nullptr)
        {
            return;
        }

        // Dia membaca dari kiri terlebih dahulu lalu mulai membaca dari kanan
        // preOrder
        UpdateFileHelper(node->left, adminFile);
        adminFile << node->GetUsername() << "," << node->GetPassword() << "," << node->GetPosition() << endl;
        UpdateFileHelper(node->right, adminFile);
    }

    NodeAdmin *GetInorderSuccessor(NodeAdmin *node)
    {
        NodeAdmin *current = node;
        while (current != nullptr && current->left != nullptr)
        {
            current = current->left;
        }
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
            cout << "Data Tidak Tersimpan!" << endl;
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
            cout << "Data Eror" << endl;
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

                while (current != nullptr)
                {
                    // Inisialisai parent menjadi current
                    parent = current;
                    if (username < current->GetUsername())
                    {
                        current = current->left;
                    }
                    else
                    {
                        current = current->right;
                    }
                }
                if (username < parent->GetUsername())
                {
                    parent->left = newNode;
                }
                else
                {
                    parent->right = newNode;
                }
            }
        }
        adminFile.close();
        return true;
    }
};
#endif