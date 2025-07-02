#include "Banking_system.h"

void Banking_system::intro() {
    cout << "\n\n\n\t  BANKING SYSTEM";
    cout << "\n\n\n\tBY: Esrael Teferi";
    cout << "\n\n\n\tPress Enter to continue...";
    cin.get();
}

void Banking_system::write_account() {
    cout << "\n\n\tFunction to create a new account.\n";
    // dummy implementation for now
}

void Banking_system::display_all() {
    cout << "\n\n\tFunction to display all accounts.\n";
}

void Banking_system::display_sp(int acc_no) {
    cout << "\n\n\tFunction to display account " << acc_no << "\n";
}

void Banking_system::modify_account(int acc_no) {
    cout << "\n\n\tFunction to modify account " << acc_no << "\n";
}

void Banking_system::delete_account(int acc_no) {
    cout << "\n\n\tFunction to delete account " << acc_no << "\n";
}

void Banking_system::deposite_withdraw(int acc_no, int option) {
    if(option == 1)
        cout << "\n\n\tDepositing to account " << acc_no << "\n";
    else
        cout << "\n\n\tWithdrawing from account " << acc_no << "\n";
}
