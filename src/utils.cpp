#include <iostream>
#include <algorithm>
#include <conio.h>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "../include/utils.hpp"

using namespace std;

// validates given string if it only has letters and numbers
bool validInput(string str) {
  for(char a : str) {
    if (!isalnum(a)) {
      return false;
    }
  } 
  return true;
}

// makes string uppercase
string uppercase(string str) {
  transform(str.begin(), str.end(), str.begin(), ::toupper);
  return str;
}

// makes string lowercase
string lowercase(string str) {
   transform(str.begin(), str.end(), str.begin(), ::tolower);
   return str;
}


// hides input text from the user
string hiddenInput() {
    string str;
    char ch;

    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!str.empty()) {
                str.pop_back();
                std::cout << "\b \b";
            }
        } else {
            str += ch;
            cout << '*'; // only showing * to the user
        }
    }

    return str;
}

// hash a password
string hashPassword(const string& password) {
    hash<string> h;
    size_t hashed = h(password);
    stringstream ss;
    ss << hashed;
    return ss.str();
}

// Reads the .env file line by line and concatenates all lines
// Returns a single string suitable for Database constructor
std::string loadDbConnectionString() {
    std::ifstream file(".env");
    if (!file.is_open()) {
        std::cerr << "Could not open .env file\n";
        return "";
    }

    std::string line;
    std::string conn;
    while (std::getline(file, line)) {
        conn += line + " ";
    }
    return conn;
}