#include <iostream>    
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h> 
#include <limits>

using namespace std;

double balance = 0.0;
string accountHolderName = "";
string pinCode = "";
const string fileName = "bank_data.txt";

// Hide PIN Input
string inputHiddenPIN(const string &prompt) {
    string pin = "";
    char ch;
    cout << prompt;
    while (true) {
        ch = _getch();
        if (ch == '\r') break; // Enter pressed
        if (ch == '\b' && !pin.empty()) { // Handle backspace
            cout << "\b \b";
            pin.pop_back();
        } else if (isdigit(ch) && pin.size() < 4) {
            pin.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return pin;
}

// Save Data
void saveToFile() {
    ofstream file(fileName);
    if (file.is_open()) {
        file << accountHolderName << endl;
        file << pinCode << endl;
        file << balance << endl;
        file.close();
    }
}

// Load Data
bool loadFromFile() {
    ifstream file(fileName);
    if (file.is_open()) {
        getline(file, accountHolderName);
        getline(file, pinCode);
        file >> balance;
        file.close();
        return true;
    }
    return false;
}

// Reset Account
void resetAccount() {
    ofstream file(fileName, ios::trunc);
    file.close();
    accountHolderName = "";
    pinCode = "";
    balance = 0.0;
    cout << "\nAll Account Data Cleared! Please Set Up a New Account.\n";
}

// Account Setup
void setUpAccount() {
    cout << "\n===== Account Setup =====\n";
    cout << "\nEnter Account Holder Name : ";
    cin.ignore();
    getline(cin, accountHolderName);

    if (!accountHolderName.empty())
    accountHolderName[0] = toupper(accountHolderName[0]);

    while (true) {
        pinCode = inputHiddenPIN("Set a 4-digit PIN: ");
        if (pinCode.length() == 4)
            break;
        cout << "Invalid PIN Length! Please Enter Exactly 4 Digits.\n";
    }

    balance = 0.0;
    saveToFile();
    cout << "\nWohoo :> Account Created Successfully!\n";
}

// Verify PIN
bool verifyPin() {
    string enteredPin = inputHiddenPIN("Enter your 4-digit PIN to Continue: ");
    if (enteredPin == pinCode) return true;
    cout << "Incorrect PIN :( Access Denied.\n";
    return false;
}

// Show Main Menu
void showMenu() {
    cout << "\n---------------------------\n";
    cout << "        BANK MENU          \n";
    cout << "---------------------------\n";
    cout << "Account Holder : " << accountHolderName << endl;
    cout << "---------------------------\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Reset Account\n";
    cout << "5. Exit\n";
    cout << "\nChoose an Option (1-5) : ";
}

// Banking Operations
void checkBalance() {
    cout << "\nYour Current Balance is : $" << fixed << setprecision(2) << balance << endl;
}

void depositMoney() {
    double amount;
    cout << "\nEnter Amount to Deposit : $";
    cin >> amount;
    if (amount <= 0)
        cout << "\nInvalid Amount!\n";
    else {
        balance += amount;
        cout << "$" << amount << " Deposited Successfully :> \n";
        checkBalance();
        saveToFile();
    }
}

void withdrawMoney() {
    double amount;
    cout << "\nEnter Amount to Withdraw : $";
    cin >> amount;
    if (amount <= 0)
        cout << "\nInvalid Amount!\n";
    else if (amount > balance)
        cout << "\nInsufficient Balance!\n";
    else {
        balance -= amount;
        cout << "$" << amount << " Withdrawn Successfully!\n";
        checkBalance();
        saveToFile();
    }
}

// Main Function
int main() {
    cout << "\n===== Welcome to Secure Banking System =====\n\n";

    bool dataLoaded = loadFromFile();

    if (!dataLoaded || accountHolderName.empty() || pinCode.empty()) {
        cout << "OOPS! No Account Found :( Let's Set Up Your Account First.\n";
        setUpAccount();
    }

    cout << "\nPlease Verify your PIN to Continue :> \n\n";
    if (!verifyPin()) return 0;

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: checkBalance(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: resetAccount(); setUpAccount(); break;
            case 5: cout << "\nThank You for Banking with Us!\n"; break;
            default: cout << "Invalid Choice! Try Again.\n";
        }
        cout << endl;
    } while (choice != 5);

    return 0;
}
