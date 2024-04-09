#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Account {
    int accNumber;
    string accHolder;
    double balance;
};

void createAccount() {
    ofstream outfile("data.txt", ios::app);
    if (!outfile) {
        cerr << "Error opening file." << endl;
        return;
    }

    Account newAccount;
    cout << "Enter account number: ";
    cin >> newAccount.accNumber;
    cin.ignore(); // Clear the input buffer
    cout << "Enter account holder name: ";
    getline(cin, newAccount.accHolder);
    cout << "Enter initial balance: ";
    cin >> newAccount.balance;

    outfile << newAccount.accNumber << " " << newAccount.accHolder << " " << newAccount.balance << endl;
    outfile.close();
}

void deposit() {
    ifstream infile("data.txt");
    ofstream outfile("temp.txt");
    if (!infile || !outfile) {
        cerr << "Error opening files." << endl;
        return;
    }

    int accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;
    cout << "Enter deposit amount: ";
    cin >> amount;

    Account acc;
    bool found = false;
    while (infile >> acc.accNumber >> acc.accHolder >> acc.balance) {
        if (acc.accNumber == accNum) {
            found = true;
            acc.balance += amount;
        }
        outfile << acc.accNumber << " " << acc.accHolder << " " << acc.balance << endl;
    }

    infile.close();
    outfile.close();

    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (!found) {
        cout << "Account not found." << endl;
    } else {
        cout << "Deposit successful." << endl;
    }
}

void withdraw() {
    ifstream infile("data.txt");
    ofstream outfile("temp.txt");
    if (!infile || !outfile) {
        cerr << "Error opening files." << endl;
        return;
    }

    int accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;
    cout << "Enter withdrawal amount: ";
    cin >> amount;

    Account acc;
    bool found = false;
    while (infile >> acc.accNumber >> acc.accHolder >> acc.balance) {
        if (acc.accNumber == accNum) {
            found = true;
            if (amount > acc.balance) {
                cout << "Insufficient funds." << endl;
            } else {
                acc.balance -= amount;
            }
        }
        outfile << acc.accNumber << " " << acc.accHolder << " " << acc.balance << endl;
    }

    infile.close();
    outfile.close();

    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (!found) {
        cout << "Account not found." << endl;
    } else {
        cout << "Withdrawal successful." << endl;
    }
}

void transfer() {
    ifstream infile("data.txt");
    ofstream outfile("temp.txt");
    if (!infile || !outfile) {
        cerr << "Error opening files." << endl;
        return;
    }

    int sourceAcc, destAcc;
    double amount;
    cout << "Enter source account number: ";
    cin >> sourceAcc;
    cout << "Enter destination account number: ";
    cin >> destAcc;
    cout << "Enter transfer amount: ";
    cin >> amount;

    Account acc;
    bool sourceFound = false;
    bool destFound = false;
    while (infile >> acc.accNumber >> acc.accHolder >> acc.balance) {
        if (acc.accNumber == sourceAcc) {
            sourceFound = true;
            if (amount > acc.balance) {
                cout << "Insufficient funds in source account." << endl;
                return;
            } else {
                acc.balance -= amount;
            }
        } else if (acc.accNumber == destAcc) {
            destFound = true;
            acc.balance += amount;
        }
        outfile << acc.accNumber << " " << acc.accHolder << " " << acc.balance << endl;
    }

    infile.close();
    outfile.close();

    if (!sourceFound) {
        cout << "Source account not found." << endl;
    } else if (!destFound) {
        cout << "Destination account not found." << endl;
    } else {
        remove("data.txt");
        rename("temp.txt", "data.txt");
        cout << "Transfer successful." << endl;
    }
}

void displayBalance(int accNumberToFind) {
    ifstream infile("data.txt");
    if (!infile) {
        cerr << "Error opening file." << endl;
        return;
    }

    Account acc;
    bool found = false;
    while (infile >> acc.accNumber >> acc.accHolder >> acc.balance) {
        if (acc.accNumber == accNumberToFind) {
            found = true;
            cout << "Account Holder: " << acc.accHolder << endl;
            cout << "Balance: " << acc.balance << endl;
            break;
        }
    }

    infile.close();

    if (!found) {
        cout << "Account not found." << endl;
    }
}

void displayMenu() {
    cout << "Bank Management System Menu" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Funds" << endl;
    cout << "3. Withdraw Funds" << endl;
    cout << "4. Transfer Funds" << endl;
    cout << "5. Display Balance" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                transfer();
                break;
            case 5: {
                int accNum;
                cout << "Enter account number to display balance: ";
                cin >> accNum;
                displayBalance(accNum);
                break;
            }
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}