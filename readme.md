# Banking Management System

A menu-driven command-line banking application written in **C++**. It demonstrates object-oriented programming concepts such as inheritance, polymorphism and abstract classes, and lets you create Savings and Current accounts, deposit and withdraw money, check balances and view all accounts.

## Features

- **Create account**: open a Savings or Current account with an auto-generated account number (starting from 1001)
- **Deposit money**: add funds to an existing account
- **Withdraw money**: withdraw funds, following the rules of the account type
- **Check balance**: view the current balance of an account
- **Display all accounts**: list every account with its number, holder name, type and balance
- **Input validation**: invalid menu choices, amounts, account numbers and empty names are handled gracefully

## Account Types and Rules

| Account Type | Initial Deposit | Withdrawal Rule |
|--------------|-----------------|-----------------|
| Savings | Minimum Rs. 500 | A minimum balance of Rs. 500 must be maintained after every withdrawal |
| Current | Any positive amount | Can withdraw up to the available balance |

## OOP Concepts Used

- **Abstraction**: `BankAccount` is an abstract base class with the pure virtual function `getAccountType()`
- **Inheritance**: `SavingsAccount` and `CurrentAccount` derive from `BankAccount`
- **Polymorphism**: `withdraw()` is overridden in `SavingsAccount`, and `getAccountType()` is overridden in both derived classes
- **Encapsulation**: account data is kept in protected members and accessed through methods
- **Smart pointers**: accounts are stored as `vector<unique_ptr<BankAccount>>` for automatic memory management
- **Virtual destructor**: ensures derived objects are cleaned up correctly

## Class Overview

```
BankAccount (abstract)
├── SavingsAccount
└── CurrentAccount

BankingSystem   → manages the collection of accounts and the main menu
```

| Class | Responsibility |
|-------|----------------|
| `BankAccount` | Holds account number, holder name and balance; provides deposit, withdraw and display |
| `SavingsAccount` | Savings account with a Rs. 500 minimum balance rule |
| `CurrentAccount` | Current account using the standard withdrawal rules |
| `BankingSystem` | Creates accounts, finds accounts, handles user input and runs the menu loop |

## Getting Started

### Prerequisites

- A C++ compiler with C++14 or later support (for example `g++`)

### Clone the repository

```bash
git clone https://github.com/narendra8010/Banking_system.git
cd Banking_system
```

### Compile

```bash
g++ -std=c++14 main.cpp -o banking_system
```

> Replace `main.cpp` with the name of your source file if it is different.

### Run

```bash
./banking_system
```

On Windows:

```bash
banking_system.exe
```

## Usage

When the program starts, the following menu is displayed:

```
====================================
       BANKING MANAGEMENT SYSTEM
====================================
1. Create Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Display All Accounts
6. Exit
====================================
Enter your choice:
```

| Option | Action |
|--------|--------|
| 1 | Enter the holder name, choose Savings or Current, and make an initial deposit |
| 2 | Enter an account number and the amount to deposit |
| 3 | Enter an account number and the amount to withdraw |
| 4 | Enter an account number to see its balance |
| 5 | Print the details of all accounts |
| 6 | Exit the program |

### Sample Session

```
Enter your choice: 1
Enter Account Holder Name: Rahul Sharma

Select Account Type:
1. Savings Account
2. Current Account
Enter choice: 1
Enter Initial Deposit: Rs. 5000

Account created successfully!
Your Account Number: 1001
```

```
Enter your choice: 3
Enter Account Number: 1001
Enter Withdrawal Amount: Rs. 4800
Withdrawal denied! Minimum balance of Rs. 500 must be maintained.
```

## Project Structure

```
Banking_system/
├── main.cpp      # Complete source code
└── README.md
```

## Author

**narendra8010** · [GitHub Profile](https://github.com/narendra8010)
