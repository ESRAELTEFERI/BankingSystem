#include "Bank.h"

// String conversion for C++98
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

void display_all() {
    printHeader("ALL ACCOUNT HOLDERS");

    Account ac;
    ifstream inFile("Banking_accounted.dat", ios::binary);

    if (!inFile) {
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
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        vector<string> row;
        row.push_back(toString(ac.retacno()));
        row.push_back(ac.getName()); // Using the getter method
        row.push_back(string(1, ac.rettype()));
        row.push_back(toString(ac.retdeposit()));
        printTableRow(row, widths);
    }

    setColor(TABLE_BORDER, BG_COLOR);
    printHorizontalLine(192, 193, 217, 196, 64);
    inFile.close();
    pressAnyKey();
}
void intro() {
    clearScreen();
    setColor(HEADER_COLOR, BG_COLOR);

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
