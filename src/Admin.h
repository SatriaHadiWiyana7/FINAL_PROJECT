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
        LoadFromFile(); // Load data on object creation
    }

    NodeAdmin *GetRoot() const
    { // Fungsi untuk access root node
        return root;
    }
};
#endif