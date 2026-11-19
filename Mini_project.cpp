#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Base Class (Encapsulation + Runtime Polymorphism)
class Account {
public:
    int accNo;
    string name;
    double balance;

    Account(int no, string n, double bal) {
        accNo = no;
        name = n;
        balance = bal;
    }

    virtual void display() {
        cout << "Acc No: " << accNo << " | Name: " << name << " | Balance: " << balance << endl;
    }

    virtual string getType() {
        return "General";
    }

    virtual ~Account() {}
};

// Derived Class 1: Savings Account (Inheritance + Method Overriding)
class SavingsAccount : public Account {
public:
    double interestRate;

    SavingsAccount(int no, string n, double bal, double rate)
        : Account(no, n, bal) {
        interestRate = rate;
    }

    void display() override {
        cout << "[Savings] Acc No: " << accNo
             << " | Name: " << name
             << " | Balance: " << balance
             << " | Interest: " << interestRate << "%" << endl;
    }

    string getType() override {
        return "Savings";
    }
};

// Derived Class 2: Current Account (Inheritance + Method Overriding)
class CurrentAccount : public Account {
public:
    double overdraftLimit;

    CurrentAccount(int no, string n, double bal, double limit)
        : Account(no, n, bal) {
        overdraftLimit = limit;
    }

    void display() override {
        cout << "[Current] Acc No: " << accNo
             << " | Name: " << name
             << " | Balance: " << balance
             << " | Overdraft Limit: " << overdraftLimit << endl;
    }

    string getType() override {
        return "Current";
    }
};

int main() {
    // STL vector storing base class pointers for runtime polymorphism
    vector<Account*> accounts;
    int choice;

    while (true) {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Create Savings Account" << endl;
        cout << "2. Create Current Account" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Display All Accounts" << endl;
        cout << "6. Save Records to File (CSV)" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int no;
            string name;
            double bal, rate;
            cout << "Enter Account No: ";
            cin >> no;
            cout << "Enter Name (one word): ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Interest Rate (%): ";
            cin >> rate;

            accounts.push_back(new SavingsAccount(no, name, bal, rate));
            cout << "Savings Account created!" << endl;
        }
        else if (choice == 2) {
            int no;
            string name;
            double bal, limit;
            cout << "Enter Account No: ";
            cin >> no;
            cout << "Enter Name (one word): ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Overdraft Limit: ";
            cin >> limit;

            accounts.push_back(new CurrentAccount(no, name, bal, limit));
            cout << "Current Account created!" << endl;
        }
        else if (choice == 3) {
            int no;
            double amount;
            cout << "Enter Account No: ";
            cin >> no;
            cout << "Enter Deposit Amount: ";
            cin >> amount;

            try {
                if (amount <= 0) {
                    throw "Error: Deposit amount must be greater than zero!";
                }

                bool found = false;
                for (int i = 0; i < accounts.size(); i++) {
                    if (accounts[i]->accNo == no) {
                        accounts[i]->balance += amount;
                        cout << "Deposited successfully! New Balance: " << accounts[i]->balance << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Account not found!" << endl;
                }
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        }
        else if (choice == 4) {
            int no;
            double amount;
            cout << "Enter Account No: ";
            cin >> no;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            try {
                if (amount <= 0) {
                    throw "Error: Withdrawal amount must be positive!";
                }

                bool found = false;
                for (int i = 0; i < accounts.size(); i++) {
                    if (accounts[i]->accNo == no) {
                        found = true;
                        if (amount > accounts[i]->balance) {
                            throw "Error: Insufficient Balance!";
                        }
                        accounts[i]->balance -= amount;
                        cout << "Withdrawn successfully! New Balance: " << accounts[i]->balance << endl;
                        break;
                    }
                }
                if (!found) {
                    cout << "Account not found!" << endl;
                }
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        }
        else if (choice == 5) {
            if (accounts.empty()) {
                cout << "No accounts available." << endl;
            } else {
                cout << "\n--- Account Details ---" << endl;
                for (int i = 0; i < accounts.size(); i++) {
                    accounts[i]->display(); // Calls derived display() at runtime
                }
            }
        }
        else if (choice == 6) {
            ofstream file("bank_records.csv");
            file << "Type,AccountNo,Name,Balance\n";
            for (int i = 0; i < accounts.size(); i++) {
                file << accounts[i]->getType() << ","
                     << accounts[i]->accNo << ","
                     << accounts[i]->name << ","
                     << accounts[i]->balance << "\n";
            }
            file.close();
            cout << "All records saved to bank_records.csv!" << endl;
        }
        else if (choice == 7) {
            // Free dynamically allocated memory
            for (int i = 0; i < accounts.size(); i++) {
                delete accounts[i];
            }
            cout << "Exiting program..." << endl;
            break;
        }
        else {
            cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}
