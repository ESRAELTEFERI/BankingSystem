#include "Bank.h"

int main() {
    // Set console properties
    system("title MIT Banking System");
    system("mode con: cols=90 lines=30");
    setColor(TEXT_COLOR, BG_COLOR);
    clearScreen();

    intro();

    char ch;
    int num;

    do {
        displayMainMenu();
        cin >> ch;

        switch(ch) {
            case '1':
                write_account();
                break;
            case '2':
                printHeader("DEPOSIT AMOUNT");
                setColor(INPUT_COLOR, BG_COLOR);
                cout << "\n\tEnter Account No. : ";
                cin >> num;
                deposit_withdraw(num, 1);
                break;
            case '3':
                printHeader("WITHDRAW AMOUNT");
                setColor(INPUT_COLOR, BG_COLOR);
                cout << "\n\tEnter Account No. : ";
                cin >> num;
                deposit_withdraw(num, 2);
                break;
            case '4':
                printHeader("BALANCE ENQUIRY");
                setColor(INPUT_COLOR, BG_COLOR);
                cout << "\n\tEnter Account No. : ";
                cin >> num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                printHeader("CLOSE ACCOUNT");
                setColor(INPUT_COLOR, BG_COLOR);
                cout << "\n\tEnter Account No. : ";
                cin >> num;
                delete_account(num);
                break;
            case '7':
                printHeader("MODIFY ACCOUNT");
                setColor(INPUT_COLOR, BG_COLOR);
                cout << "\n\tEnter Account No. : ";
                cin >> num;
                modify_account(num);
                break;
            case '8':
                printHeader("THANK YOU");
                setColor(MENU_COLOR, BG_COLOR);
                printCentered("Thanks for using MIT Banking System");
                printCentered("Have a nice day!");
                setColor(HEADER_COLOR, BG_COLOR);
                cout << string(90, '=') << endl;
                setColor(TEXT_COLOR, BG_COLOR);
                cout << "\n\n";
                break;
            default:
                setColor(ERROR_COLOR, BG_COLOR);
                cout << "\a\n\tInvalid Option! Please try again...";
                setColor(TEXT_COLOR, BG_COLOR);
                pressAnyKey();
        }
    } while(ch != '8');

    return 0;
}
