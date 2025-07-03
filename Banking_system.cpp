#include "Banking_system.h"

// String conversion
template <typename T>
string toString(const T& value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

// Visual Functions
void setColor(int text, int bg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg << 4) | text);
}

void clearScreen() {
    system("cls");
    setColor(TEXT_COLOR, BG_COLOR);
}
void printHeader(const string &title) {
    clearScreen();
    setColor(HEADER_COLOR, BG_COLOR);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    cout << string(width, '=') << endl;
    printCentered(title);
    cout << string(width, '=') << endl << endl;
    setColor(TEXT_COLOR, BG_COLOR);
}
void printCentered(const string &text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int padding = (width - text.length()) / 2;
    cout << setw(padding + text.length()) << text << endl;
}

void printHorizontalLine(char left, char mid, char right, char fill, int total_width) {
    cout << left << setfill(fill) << setw(total_width - 2) << fill << right << setfill(' ') << endl;
}

void printTableHeader(const vector<string> &headers, const vector<int> &widths) {
    int total_width = 1;
    for (size_t i = 0; i < widths.size(); i++) {
        total_width += widths[i] + 3;
    }

    setColor(TABLE_BORDER, BG_COLOR);
    printHorizontalLine(218, 194, 191, 196, total_width);

    cout << char(179);
    setColor(TABLE_HEADER, BG_COLOR);
    for (size_t i = 0; i < headers.size(); i++) {
        cout << " " << left << setw(widths[i]) << headers[i] << " ";
        setColor(TABLE_BORDER, BG_COLOR);
        cout << (i < headers.size()-1 ? char(179) : char(179));
    }
    cout << endl;

    printHorizontalLine(195, 197, 180, 196, total_width);
}

void printTableRow(const vector<string> &data, const vector<int> &widths) {
    setColor(TABLE_BORDER, BG_COLOR);
    cout << char(179);
    setColor(TABLE_ROW, BG_COLOR);

    for (size_t i = 0; i < data.size(); i++) {
        cout << " " << left << setw(widths[i]) << data[i] << " ";
        setColor(TABLE_BORDER, BG_COLOR);
        cout << (i < data.size()-1 ? char(179) : char(179));
    }
    cout << endl;
}

void pressAnyKey() {
    setColor(MENU_COLOR, BG_COLOR);
    cout << "\n\tPress any key to continue...";
    setColor(TEXT_COLOR, BG_COLOR);
    _getch();
}

// Account Functions
void Account::create_account() {
    printHeader("CREATE NEW ACCOUNT");

    setColor(INPUT_COLOR, BG_COLOR);
    cout << "\n\t" << left << setw(30) << "Enter Account No. : ";
    cin >> acno;
    cout << "\t" << setw(30) << "Enter Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\t" << setw(30) << "Enter Account Type (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\t" << setw(30) << "Enter Initial Amount : ";
    cout << "\n\t" << setw(30) << "(>=500 for Saving, >=1000 for Current) : ";
    cin >> deposit;

    setColor(SUCCESS_COLOR, BG_COLOR);
    cout << "\n\n\tAccount Created Successfully!";
    setColor(TEXT_COLOR, BG_COLOR);
}

void Account::show_account() const {
    vector<string> headers;
    headers.push_back("Field");
    headers.push_back("Value");

    vector<int> widths;
    widths.push_back(25);
    widths.push_back(30);

    printTableHeader(headers, widths);

    vector<vector<string> > rows;
    {
        vector<string> row1;
        row1.push_back("Account No.");
        row1.push_back(toString(acno));
        rows.push_back(row1);

        vector<string> row2;
        row2.push_back("Account Holder Name");
        row2.push_back(name);
        rows.push_back(row2);

        vector<string> row3;
        row3.push_back("Type of Account");
        row3.push_back(string(1, type));
        rows.push_back(row3);

        vector<string> row4;
        row4.push_back("Balance Amount");
        row4.push_back(toString(deposit));
        rows.push_back(row4);
    }

    for (size_t i = 0; i < rows.size(); i++) {
        printTableRow(rows[i], widths);
    }

    setColor(TABLE_BORDER, BG_COLOR);
    printHorizontalLine(192, 193, 217, 196, 58);
}

void Account::modify() {
    cout << "\n\tEnter New Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\tEnter New Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\tEnter New Balance Amount : ";
    cin >> deposit;
}

void Account::dep(int amt) {
    deposit += amt;
}

void Account::draw(int amt) {
    deposit -= amt;
}

void Account::report() const {
    cout << left << setw(10) << acno
         << setw(20) << name
         << setw(10) << type
         << setw(15) << deposit << endl;
}

// Account Operations
void write_account() {
    Account ac;
    ofstream outFile;
    outFile.open("Banking_accounted.dat", ios::app | ios::binary);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));
    outFile.close();
    pressAnyKey();
}

void display_all() {
    printHeader("ALL ACCOUNT HOLDERS");

    Account ac;
    ifstream inFile;
    inFile.open("Banking_accounted.dat", ios::binary);

    if(!inFile) {
        setColor(ERROR_COLOR, BG_COLOR);
        cout << "\n\tFile could not be opened!";
        setColor(TEXT_COLOR, BG_COLOR);
        pressAnyKey();
        return;
    }

    vector<string> headers;
    headers.push_back("A/C No.");
    headers.push_back("Name");
    headers.push_back("Type");
    headers.push_back("Balance");

    vector<int> widths;
    widths.push_back(10);
    widths.push_back(25);
    widths.push_back(10);
    widths.push_back(15);

    printTableHeader(headers, widths);

    setColor(TABLE_ROW, BG_COLOR);
    while(inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account))) {
        vector<string> row;
        row.push_back(toString(ac.retacno()));
        row.push_back(ac.getname()); // Using getter method
        row.push_back(string(1, ac.rettype()));
        row.push_back(toString(ac.retdeposit()));
        printTableRow(row, widths);
    }

    setColor(TABLE_BORDER, BG_COLOR);
    printHorizontalLine(192, 193, 217, 196, 64);
    inFile.close();
    pressAnyKey();
}

void display_sp(int n) {
    Account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("Banking_accounted.dat", ios::binary);

    if(!inFile) {
        setColor(ERROR_COLOR, BG_COLOR);
        cout << "\n\tFile could not be opened!";
        setColor(TEXT_COLOR, BG_COLOR);
        pressAnyKey();
        return;
    }

    printHeader("ACCOUNT DETAILS");

    while(inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account))) {
        if(ac.retacno() == n) {
            setColor(MENU_COLOR, BG_COLOR);
            ac.show_account();
            flag = true;
            break;
        }
    }
    inFile.close();

    if(!flag) {
        setColor(ERROR_COLOR, BG_COLOR);
        cout << "\n\tAccount number does not exist";
        setColor(TEXT_COLOR, BG_COLOR);
    }
    pressAnyKey();
}

void modify_account(int n) {
    bool found = false;
    Account ac;
    fstream File;

    File.open("Banking_accounted.dat", ios::binary | ios::in | ios::out);
    if(!File) {
        setColor(ERROR_COLOR, BG_COLOR);
        cout << "\n\tFile could not be opened!";
        setColor(TEXT_COLOR, BG_COLOR);
        pressAnyKey();
        return;
    }

    printHeader("MODIFY ACCOUNT");

    while(!File.eof() && !found) {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Account));
        if(ac.retacno() == n) {
            setColor(MENU_COLOR, BG_COLOR);
            ac.show_account();
            cout << "\n\tEnter New Details:\n";
            setColor(INPUT_COLOR, BG_COLOR);
            ac.modify();

            int pos = (-1) * static_cast<int>(sizeof(Account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(Account));

            setColor(SUCCESS_COLOR, BG_COLOR);
            cout << "\n\tRecord Updated!";
            found = true;
        }
    }
    File.close();

    if(!found) {
        setColor(ERROR_COLOR, BG_COLOR);
        cout << "\n\tRecord Not Found!";
    }
    setColor(TEXT_COLOR, BG_COLOR);
    pressAnyKey();
}

void delete_account(int n) {
    Account ac;
    ifstream inFile;
    ofstream outFile;

    inFile.open("Banking_accounted.dat", ios::binary);
    if(!inFile) {
        setColor(ERROR_COLOR, BG_COLOR);
        cout << "\n\tFile could not be opened!";
        setColor(TEXT_COLOR, BG_COLOR);
        pressAnyKey();
        return;
    }

    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);

    while(inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account))) {
        if(ac.retacno() != n) {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));
        }
    }

    inFile.close();
    outFile.close();
    remove("Banking_accounted.dat");
    rename("Temp.dat", "Banking_accounted.dat");

    setColor(SUCCESS_COLOR, BG_COLOR);
    cout << "\n\tRecord Deleted!";
    setColor(TEXT_COLOR, BG_COLOR);
    pressAnyKey();
}

void deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    Account ac;
    fstream File;

    File.open("Banking_accounted.dat", ios::binary | ios::in | ios::out);
    if(!File) {
        setColor(ERROR_COLOR, BG_COLOR);
        cout << "\n\tFile could not be opened!";
        setColor(TEXT_COLOR, BG_COLOR);
        pressAnyKey();
        return;
    }

    printHeader(option == 1 ? "DEPOSIT AMOUNT" : "WITHDRAW AMOUNT");

    while(!File.eof() && !found) {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Account));
        if(ac.retacno() == n) {
            setColor(MENU_COLOR, BG_COLOR);
            ac.show_account();

            setColor(INPUT_COLOR, BG_COLOR);
            if(option == 1) {
                cout << "\n\tEnter Amount to Deposit: ";
                cin >> amt;
                ac.dep(amt);
            } else {
                cout << "\n\tEnter Amount to Withdraw: ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C')) {
                    setColor(ERROR_COLOR, BG_COLOR);
                    cout << "\n\tInsufficient Balance!";
                    setColor(TEXT_COLOR, BG_COLOR);
                    File.close();
                    pressAnyKey();
                    return;
                } else {
                    ac.draw(amt);
                }
            }

            int pos = (-1) * static_cast<int>(sizeof(Account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(Account));

            setColor(SUCCESS_COLOR, BG_COLOR);
            cout << "\n\tTransaction Successful!";
            found = true;
        }
    }
    File.close();

    if(!found) {
        setColor(ERROR_COLOR, BG_COLOR);
        cout << "\n\tAccount Not Found!";
    }
    setColor(TEXT_COLOR, BG_COLOR);
    pressAnyKey();
}

void intro() {
    setColor(HEADER_COLOR, BG_COLOR);
    clearScreen();

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    cout << string(width, '=') << endl;
    printCentered("WELCOME TO MIT BANKING SYSTEM");
    cout << string(width, '=') << endl << endl;

    setColor(MENU_COLOR, BG_COLOR);
    printCentered("Developed by: Esrael Teferi");
    printCentered("Mekelle Institute of Technology");

    setColor(TEXT_COLOR, BG_COLOR);
    cout << "\n\n\n";
    printCentered("Press any key to continue...");
    _getch();
}

void displayMainMenu() {
    printHeader("MAIN MENU");

    vector<string> menuItems;
    menuItems.push_back("1. NEW ACCOUNT");
    menuItems.push_back("2. DEPOSIT AMOUNT");
    menuItems.push_back("3. WITHDRAW AMOUNT");
    menuItems.push_back("4. BALANCE ENQUIRY");
    menuItems.push_back("5. ALL ACCOUNT HOLDER LIST");
    menuItems.push_back("6. CLOSE AN ACCOUNT");
    menuItems.push_back("7. MODIFY AN ACCOUNT");
    menuItems.push_back("8. EXIT");

    setColor(MENU_COLOR, BG_COLOR);
    for (size_t i = 0; i < menuItems.size(); i++) {
        cout << "\n\t" << menuItems[i];
    }

    setColor(INPUT_COLOR, BG_COLOR);
    cout << "\n\n\tEnter Your Choice (1-8): ";
}
