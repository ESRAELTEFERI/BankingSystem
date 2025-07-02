#include "Banking_system.h"

int main() {
    Banking_system bank;
    bank.intro(); // Show welcome screen

    int choice;
    int num;

    do {
        cout << "\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8): ";
        cin >> choice;

        switch(choice) {
            case 1:
                bank.write_account();
                break;
            case 2:
                cout << "\n\n\tEnter The Account No.: ";
                cin >> num;
                bank.deposite_withdraw(num, 1);
                break;
            case 3:
                cout << "\n\n\tEnter The Account No.: ";
                cin >> num;
                bank.deposite_withdraw(num, 2);
                break;
            case 4:
                cout << "\n\n\tEnter The Account No.: ";
                cin >> num;
                bank.display_sp(num);
                break;
            case 5:
                bank.display_all();
                break;
            case 6:
                cout << "\n\n\tEnter The Account No.: ";
                cin >> num;
                bank.delete_account(num);
                break;
            case 7:
                cout << "\n\n\tEnter The Account No.: ";
                cin >> num;
                bank.modify_account(num);
                break;
            case 8:
                cout << "\n\n\tThanks for using our banking system!\n";
                break;
            default:
                cout << "\aInvalid Option! Try again.";
        }

    } while (choice != 8);

    return 0;
}
