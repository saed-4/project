#include <iostream>
#include <iomanip>
#include <limits>

// ---------------------------------------------------------------
// Account: base class. Demonstrates ENCAPSULATION.
// balance is protected (derived classes may use it directly),
// history/count are private (only Account itself, plus its
// declared friend, may touch them).
// ---------------------------------------------------------------
class Account {
private:
    double history[10];   // simple transaction log
    int count;

protected:
    double balance;        // accessible to derived classes, not to outside code

public:
    Account() : count(0), balance(0) {}

    double getBalance() const {
        return balance;
    }

    int getTransactionCount() const {
        return count;
    }

    // Records amount into the private history array (bounds-checked)
    void recordTransaction(double amount) {
        if (count < 10) {
            history[count] = amount;
            count++;
        }
    }

    void applyDeposit(double amount) {
        balance += amount;
        recordTransaction(amount);
    }

    void applyWithdrawal(double amount) {
        balance -= amount;
        recordTransaction(-amount);
    }

    // FRIEND FUNCTION: not a member of Account, but declared as a
    // friend so it can reach the private history[] and count directly.
    friend void printTransactionLog(const Account& acc);
};

// Friend function definition. Because it was declared "friend" inside
// Account, it can access acc.history and acc.count even though both
// are private.
void printTransactionLog(const Account& acc) {
    std::cout << "----- Transaction Log -----\n";
    if (acc.count == 0) {
        std::cout << "No transactions yet.\n";
        return;
    }
    for (int i = 0; i < acc.count; i++) {
        if (acc.history[i] >= 0) {
            std::cout << i + 1 << ". Deposit:    $"
                      << std::fixed << std::setprecision(2) << acc.history[i] << '\n';
        } else {
            std::cout << i + 1 << ". Withdrawal: $"
                      << std::fixed << std::setprecision(2) << -acc.history[i] << '\n';
        }
    }
}

// ---------------------------------------------------------------
// SavingsAccount: demonstrates simple INHERITANCE.
// It reuses everything from Account (balance, deposits, withdrawals,
// transaction log) and adds interest on top.
// ---------------------------------------------------------------
class SavingsAccount : public Account {
private:
    double interestRate;   // e.g. 0.05 = 5%

public:
    explicit SavingsAccount(double rate = 0.05) : Account(), interestRate(rate) {}

    double getInterestRate() const {
        return interestRate;
    }

    // Can use "balance" directly here because it is protected in Account,
    // not private -- that's what makes it reachable from a derived class.
    double applyInterest() {
        double interest = balance * interestRate;
        balance += interest;
        recordTransaction(interest);
        return interest;
    }
};

void showBalance(const Account& acc);
double deposit();
double withdraw(double balance);

int main() {
    SavingsAccount acc(0.05);   // a savings account with a 5% interest rate
    int choice = 0;

    do {
        std::cout << "******\n";
        std::cout << "Enter your choice:\n";
        std::cout << "******\n";
        std::cout << "1. Show Balance\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Apply Interest\n";
        std::cout << "5. View Transaction Log\n";
        std::cout << "6. Exit\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                showBalance(acc);
                break;
            case 2: {
                double amount = deposit();
                if (amount > 0) {
                    acc.applyDeposit(amount);
                }
                showBalance(acc);
                break;
            }
            case 3: {
                double amount = withdraw(acc.getBalance());
                if (amount > 0) {
                    acc.applyWithdrawal(amount);
                }
                showBalance(acc);
                break;
            }
            case 4: {
                double interest = acc.applyInterest();
                std::cout << "Interest applied: $"
                          << std::fixed << std::setprecision(2) << interest << '\n';
                showBalance(acc);
                break;
            }
            case 5:
                printTransactionLog(acc);
                break;
            case 6:
                std::cout << "Thanks for visiting!\n";
                break;
            default:
                std::cout << "Invalid choice\n";
        }
    } while (choice != 6);

    return 0;
}

// Works for an Account or anything derived from it (like SavingsAccount)
// because it only uses the public getBalance() -- no friend needed here.
void showBalance(const Account& acc) {
    std::cout << "Your balance is: $"
              << std::setprecision(2) << std::fixed << acc.getBalance() << '\n';
}

double deposit() {
    double amount = 0;
    std::cout << "Enter amount to be deposited: ";
    std::cin >> amount;
    if (amount > 0) {
        return amount;
    } else {
        std::cout << "That's not a valid amount:\n";
        return 0;
    }
}

double withdraw(double balance) {
    double amount = 0;
    std::cout << "Enter amount to be withdrawn: ";
    std::cin >> amount;
    if (amount > balance) {
        std::cout << "insufficient funds\n";
        return 0;
    } else if (amount < 0) {
        std::cout << "That's not a valid amount\n";
        return 0;
    } else {
        return amount;
    }
}