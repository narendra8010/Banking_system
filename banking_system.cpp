
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// Base Class
class BankAccount {
protected:
    int accountNumber;
    string holderName;
    double balance;

public:
    BankAccount(int accNo, string name, double initialBalance)
        : accountNumber(accNo),
          holderName(name),
          balance(initialBalance) {}

    virtual ~BankAccount() = default;

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    virtual string getAccountType() const = 0;

    virtual void displayAccount() const {
        cout << "\nAccount Number : " << accountNumber
             << "\nAccount Holder : " << holderName
             << "\nAccount Type   : " << getAccountType()
             << "\nBalance        : Rs. "
             << fixed << setprecision(2) << balance << '\n';
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }

        balance += amount;
        cout << "Deposit successful!\n";
        cout << "Updated Balance: Rs. "
             << fixed << setprecision(2) << balance << '\n';
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }

        balance -= amount;
        cout << "Withdrawal successful!\n";
        cout << "Updated Balance: Rs. "
             << fixed << setprecision(2) << balance << '\n';
    }
};

// Derived Class: Savings Account
class SavingsAccount : public BankAccount {
public:
    SavingsAccount(int accNo, string name, double initialBalance)
        : BankAccount(accNo, name, initialBalance) {}

    string getAccountType() const override {
        return "Savings";
    }

    void withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return;
        }

        // Maintain a minimum balance of Rs. 500
        if (balance - amount < 500) {
            cout << "Withdrawal denied! "
                 << "Minimum balance of Rs. 500 must be maintained.\n";
            return;
        }

        balance -= amount;
        cout << "Savings account withdrawal successful!\n";
        cout << "Updated Balance: Rs. "
             << fixed << setprecision(2) << balance << '\n';
    }
};

// Derived Class: Current Account
class CurrentAccount : public BankAccount {
public:
    CurrentAccount(int accNo, string name, double initialBalance)
        : BankAccount(accNo, name, initialBalance) {}

    string getAccountType() const override {
        return "Current";
    }

    // Uses the base class withdrawal rules.
};

// Banking System Class
class BankingSystem {
private:
    vector<unique_ptr<BankAccount>> accounts;
    int nextAccountNumber = 1001;

    BankAccount* findAccount(int accNo) {
        for (auto& account : accounts) {
            if (account->getAccountNumber() == accNo) {
                return account.get();
            }
        }

        return nullptr;
    }

    double readAmount(const string& message) {
        double amount;

        while (true) {
            cout << message;

            if (cin >> amount &&
                amount > 0 &&
                amount <= numeric_limits<double>::max()) {
                return amount;
            }

            cout << "Enter a valid positive amount.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    int readAccountNumber() {
        int accNo;

        while (true) {
            cout << "Enter Account Number: ";

            if (cin >> accNo && accNo > 0) {
                return accNo;
            }

            cout << "Enter a valid account number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

public:
    void createAccount() {
        string name;
        int type;
        double initialBalance;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Name cannot be empty!\n";
            return;
        }

        cout << "\nSelect Account Type:\n";
        cout << "1. Savings Account\n";
        cout << "2. Current Account\n";
        cout << "Enter choice: ";

        if (!(cin >> type) || (type != 1 && type != 2)) {
            cout << "Invalid account type!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        initialBalance = readAmount("Enter Initial Deposit: Rs. ");

        int accNo = nextAccountNumber++;

        if (type == 1) {
            if (initialBalance < 500) {
                cout << "Savings account requires an initial "
                     << "deposit of at least Rs. 500.\n";
                return;
            }

            accounts.push_back(
                make_unique<SavingsAccount>(
                    accNo, name, initialBalance
                )
            );
        } else {
            accounts.push_back(
                make_unique<CurrentAccount>(
                    accNo, name, initialBalance
                )
            );
        }

        cout << "\nAccount created successfully!\n";
        cout << "Your Account Number: " << accNo << '\n';
    }

    void depositMoney() {
        int accNo = readAccountNumber();
        BankAccount* account = findAccount(accNo);

        if (!account) {
            cout << "Account not found!\n";
            return;
        }

        double amount = readAmount("Enter Deposit Amount: Rs. ");
        account->deposit(amount);
    }

    void withdrawMoney() {
        int accNo = readAccountNumber();
        BankAccount* account = findAccount(accNo);

        if (!account) {
            cout << "Account not found!\n";
            return;
        }

        double amount = readAmount("Enter Withdrawal Amount: Rs. ");
        account->withdraw(amount);
    }

    void checkBalance() {
        int accNo = readAccountNumber();
        BankAccount* account = findAccount(accNo);

        if (!account) {
            cout << "Account not found!\n";
            return;
        }

        cout << "\nCurrent Balance: Rs. "
             << fixed << setprecision(2)
             << account->getBalance() << '\n';
    }

    void displayAllAccounts() const {
        if (accounts.empty()) {
            cout << "No accounts available.\n";
            return;
        }

        cout << "\n========== ALL BANK ACCOUNTS ==========\n";

        for (const auto& account : accounts) {
            account->displayAccount();
            cout << "---------------------------------------\n";
        }
    }

    void menu() {
        int choice;

        do {
            cout << "\n====================================\n";
            cout << "       BANKING MANAGEMENT SYSTEM\n";
            cout << "====================================\n";
            cout << "1. Create Account\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. Check Balance\n";
            cout << "5. Display All Accounts\n";
            cout << "6. Exit\n";
            cout << "====================================\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input! Enter a number.\n";
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                continue;
            }

            switch (choice) {
                case 1:
                    createAccount();
                    break;

                case 2:
                    depositMoney();
                    break;

                case 3:
                    withdrawMoney();
                    break;

                case 4:
                    checkBalance();
                    break;

                case 5:
                    displayAllAccounts();
                    break;

                case 6:
                    cout << "Thank you for using our banking system!\n";
                    break;

                default:
                    cout << "Invalid choice! Try again.\n";
            }

        } while (choice != 6);
    }
};

int main() {
    BankingSystem bank;
    bank.menu();

    return 0;
}