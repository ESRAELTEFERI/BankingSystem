#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Banking_system {
public:
    void write_account();
    void display_all();
    void display_sp(int);
    void modify_account(int);
    void delete_account(int);
    void deposite_withdraw(int, int);
    void intro();

private:
    int acno;
    char name[50];
    int deposit;
    char type;
};

#endif // BANKING_SYSTEM_H
