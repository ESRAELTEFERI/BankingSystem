#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<windows.h>
#include<vector>
#include<conio.h>
#include<sstream>
using namespace std;

// Color Constants
const int BG_COLOR = 1;         // Blue background
const int HEADER_COLOR = 14;    // Yellow
const int MENU_COLOR = 11;      // Light cyan
const int INPUT_COLOR = 10;     // Light green
const int ERROR_COLOR = 12;     // Light red
const int SUCCESS_COLOR = 10;   // Light green
const int TEXT_COLOR = 15;      // Bright white
const int TABLE_HEADER = 3;     // Cyan
const int TABLE_BORDER = 6;     // Yellow
const int TABLE_ROW = 7;        // White

class Account {
private:
    int acno;
    char name[50];
    int deposit;
    char type;

public:
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
    const char* getName() const { return name; } // Added getter
};

// Visual Functions
void setColor(int text, int bg=BG_COLOR);
void printHeader(const string &title);
void printCentered(const string &text);
void printTableHeader(const vector<string> &headers, const vector<int> &widths);
void printTableRow(const vector<string> &data, const vector<int> &widths);
void printHorizontalLine(char left, char mid, char right, char fill, int total_width);
void pressAnyKey();
void clearScreen();

// String conversion for C++98
template <typename T>
string toString(const T& value);

// Account Operations
void write_account();
void display_all();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void deposit_withdraw(int, int);
void intro();
void displayMainMenu();

#endif
