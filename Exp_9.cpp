#include <iostream>
#include <exception>
#include <string>

using namespace std;

// Base Custom Exception Class
class BankException : public exception {
protected:
    string message;
public:
    BankException(string msg) {
        message = msg;
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Derived Exception 1: Negative or zero amount
class InvalidAmountException : public BankException {
public:
    InvalidAmountException()
        : BankException("Error: Transaction amount must be greater than zero.") {}
};

// Derived Exception 2: Balance too low
class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance for this withdrawal.") {}
};

// Derived Exception 3: Exceeds single withdrawal limit
class LimitExceededException : public BankException {
public:
    LimitExceededException()
        : BankException("Error: Withdrawal exceeds single-transaction limit of 10000.") {}
};

class BankAccount {
public:
    string holderName;
    double balance;

    BankAccount(string name, double initialBalance) {
        holderName = name;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        balance += amount;
        cout << "Deposited: " << amount << " | Current Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        if (amount > 10000) {
            throw LimitExceededException();
        }
        if (amount > balance) {
            throw InsufficientFundsException();
        }
        balance -= amount;
        cout << "Withdrawn: " << amount << " | Current Balance: " << balance << endl;
    }
};

int main() {
    BankAccount acc("Krishna", 8000.0);

    // 1. Valid transaction
    try {
        acc.deposit(2000.0);
        acc.withdraw(3000.0);
    }
    catch (const BankException& e) {
        cout << e.what() << endl;
    }

    // 2. Catching InvalidAmountException
    try {
        acc.deposit(-500.0);
    }
    catch (const InvalidAmountException& e) {
        cout << "Caught Specific -> " << e.what() << endl;
    }

    // 3. Catching LimitExceededException
    try {
        acc.withdraw(12000.0);
    }
    catch (const LimitExceededException& e) {
        cout << "Caught Specific -> " << e.what() << endl;
    }

    // 4. Catching InsufficientFundsException
    try {
        acc.withdraw(9000.0);
    }
    catch (const InsufficientFundsException& e) {
        cout << "Caught Specific -> " << e.what() << endl;
    }

    return 0;
}
