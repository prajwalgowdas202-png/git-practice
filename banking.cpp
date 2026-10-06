#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Account {
private:
    int accountNumber;
    string name;
    double balance;

public:
    Account() {
        accountNumber = 0;
        name = "";
        balance = 0;
    }

    Account(int accNo, string n, double bal) {
        accountNumber = accNo;
        name = n;
        balance = bal;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    string getName() {
        return name;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully.\n";
        } else {
            cout << "Invalid amount.\n";
        }
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount.\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }

        balance -= amount;
        cout << "Amount withdrawn successfully.\n";
        return true;
    }

    void display() {
        cout << "\n-----------------------------\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << name << endl;
        cout << "Balance        : Rs. " << fixed << setprecision(2)
             << balance << endl;
        cout << "-----------------------------\n";
    }

    void saveToFile() {
        ofstream file("accounts.txt", ios::app);

        file << accountNumber << "|"
             << name << "|"
             << balance << endl;

        file.close();
    }
};

void createAccount() {
    int accNo;
    string name;
    double initialDeposit;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cin.ignore();

    cout << "Enter Account Holder Name: ";
    getline(cin, name);

    cout << "Enter Initial Deposit: ";
    cin >> initialDeposit;

    if (initialDeposit < 0) {
        cout << "Invalid deposit.\n";
        return;
    }

    Account account(accNo, name, initialDeposit);
    account.saveToFile();

    cout << "\nAccount created successfully!\n";
}

void searchAccount() {
    int accNo;
    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file("accounts.txt");

    int number;
    string name;
    double balance;
    bool found = false;

    string line;

    while (getline(file, line)) {

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);

        number = stoi(line.substr(0, p1));
        name = line.substr(p1 + 1, p2 - p1 - 1);
        balance = stod(line.substr(p2 + 1));

        if (number == accNo) {
            Account account(number, name, balance);
            account.display();

            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Account not found.\n";
    }
}

void showAllAccounts() {
    ifstream file("accounts.txt");

    int number;
    string name;
    double balance;
    bool empty = true;

    string line;

    cout << "\n====== ALL ACCOUNTS ======\n";

    while (getline(file, line)) {

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);

        number = stoi(line.substr(0, p1));
        name = line.substr(p1 + 1, p2 - p1 - 1);
        balance = stod(line.substr(p2 + 1));

        Account account(number, name, balance);
        account.display();

        empty = false;
    }

    file.close();

    if (empty) {
        cout << "No accounts found.\n";
    }
}

int main() {

    int choice;

    while (true) {

        cout << "\n================================\n";
        cout << "       EASYBANK MANAGEMENT\n";
        cout << "================================\n";
        cout << "1. Create Account\n";
        cout << "2. Search Account\n";
        cout << "3. Show All Accounts\n";
        cout << "4. Exit\n";
        cout << "================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                createAccount();
                break;

            case 2:
                searchAccount();
                break;

            case 3:
                showAllAccounts();
                break;

            case 4:
                cout << "Thank you for using EasyBank!\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}