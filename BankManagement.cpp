#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Account Class
class Account {
    int accNo;
    string name;
    int pin;
    double balance;

public:
    void create() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Set 4-digit PIN: ";
        cin >> pin;

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void show() const {
        cout << "\nAccount No : " << accNo;
        cout << "\nName       : " << name;
        cout << "\nBalance    : " << balance << endl;
    }

    int getAccNo() const {
        return accNo;
    }

    bool verifyPin(int p) const {
        return pin == p;
    }

    void deposit(double amt) {
        balance += amt;
    }

    bool withdraw(double amt) {
        if (amt > balance)
            return false;
        balance -= amt;
        return true;
    }

    void writeToFile(ofstream &out) const {
        out << accNo << endl;
        out << name << endl;
        out << pin << endl;
        out << balance << endl;
    }

    void readFromFile(ifstream &in) {
        in >> accNo;
        in.ignore();
        getline(in, name);
        in >> pin;
        in >> balance;
    }
};

//Bank Class
class Bank {
    vector<Account> accounts;
    string fileName = "accounts.txt";

public:
    void loadData() {
        ifstream in(fileName);
        if (!in)
            return;

        while (in.peek() != EOF) {
            Account acc;
            acc.readFromFile(in);
            accounts.push_back(acc);
        }
        in.close();
    }

    void saveData() {
        ofstream out(fileName);
        for (int i = 0; i < accounts.size(); i++) {
            accounts[i].writeToFile(out);
        }
        out.close();
    }

    void openAccount() {
        Account acc;
        acc.create();
        accounts.push_back(acc);
        saveData();
        cout << "\nAccount created successfully!\n";
    }

    void displayAccount() {
        int accNo, pin;
        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cout << "Enter PIN: ";
        cin >> pin;

        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccNo() == accNo &&
                accounts[i].verifyPin(pin)) {
                accounts[i].show();
                return;
            }
        }
        cout << "\nInvalid account number or PIN!\n";
    }

    void depositMoney() {
        int accNo;
        double amt;

        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cout << "Enter Amount to Deposit: ";
        cin >> amt;

        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccNo() == accNo) {
                accounts[i].deposit(amt);
                saveData();
                cout << "\nAmount deposited successfully!\n";
                return;
            }
        }
        cout << "\nAccount not found!\n";
    }

    void withdrawMoney() {
        int accNo, pin;
        double amt;

        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cout << "Enter PIN: ";
        cin >> pin;
        cout << "Enter Amount to Withdraw: ";
        cin >> amt;

        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccNo() == accNo &&
                accounts[i].verifyPin(pin)) {

                if (accounts[i].withdraw(amt)) {
                    saveData();
                    cout << "\nPlease collect your cash.\n";
                } else {
                    cout << "\nInsufficient balance!\n";
                }
                return;
            }
        }
        cout << "\nInvalid account number or PIN!\n";
    }

    void deleteAccount() {
        int accNo, pin;

        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cout << "Enter PIN: ";
        cin >> pin;

        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccNo() == accNo &&
                accounts[i].verifyPin(pin)) {

                accounts.erase(accounts.begin() + i);
                saveData();
                cout << "\nAccount deleted successfully!\n";
                return;
            }
        }
        cout << "\nInvalid account number or PIN!\n";
    }
};

/* -------- Main Function -------- */
int main() {
    Bank bank;
    bank.loadData();

    int choice;
    do {
        cout << "\n====== BANK MANAGEMENT SYSTEM ======\n";
        cout << "1. Open New Account\n";
        cout << "2. View Account Details\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Delete Account\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.openAccount(); break;
            case 2: bank.displayAccount(); break;
            case 3: bank.depositMoney(); break;
            case 4: bank.withdrawMoney(); break;
            case 5: bank.deleteAccount(); break;
            case 6: cout << "\nThank you for using the system.\n"; break;
            default: cout << "\nInvalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}

