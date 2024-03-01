#include "GazpromBank.h"
#include "SberBank.h"
#include "Account.h"
#include "PhysicalClient.h"
#include "Client.h"
#include <iostream>
#include <clocale>
#include <vector>
#include <map>

using namespace std;

map<std::string, Bank *> banks = {{GazpromBank().getName(), new GazpromBank},
                                  {SberBank().getName(),    new SberBank}};

void transferMoneyOuter() {
    std::string bankNameFrom, fioFrom, fioTo, bankNameTo;
    double value;
    cout << "Enter the bank name from: " << endl;
    cin >> bankNameFrom;

    if (banks.find(bankNameFrom) == banks.end()) {
        cout << "You entered wrong bank name" << endl;
        return;
    }

    cout << "What's name of your user FROM? " << endl;
    cin >> fioFrom;

    cout << "Enter the bank name to: " << endl;
    cin >> bankNameTo;

    if (banks.find(bankNameTo) == banks.end()) {
        cout << "You entered wrong bank name" << endl;
        return;
    }


    cout << "What's name of your user TO? " << endl;
    cin >> fioTo;

    cout << "How many money do u want to send? " << endl;
    cin >> value;

    if (!banks.find(bankNameFrom)->second->hasClientWithFio(fioFrom)
        && !banks.find(bankNameTo)->second->hasClientWithFio(fioTo)) {
        cout << "Not found users in banks" << endl;
        return;
    }


    banks.find(bankNameFrom)->second->transferMoneyToAnotherBankClient(
            fioFrom,
            banks.find(bankNameTo)->second,
            fioTo,
            value);
}

void addMoneyToAccount() {
    std::string bankName, fio;
    double value;
    cout << "Enter the bank name: " << endl;
    cin >> bankName;

    if (banks.find(bankName) == banks.end()) {
        cout << "You entered wrong bank name" << endl;
        return;
    }

    cout << "What's name of your user? " << endl;
    cin >> fio;

    cout << "How many money do u wanna add to account? " << endl;
    cin >> value;

    if (!banks.find(bankName)->second->hasClientWithFio(fio)) {
        cout << "Not found users in bank" << endl;
        return;
    }

    banks.find(bankName)->second->getClientByFio(fio)->addDeposit(value);
    cout << "Current balance of ur user - "
         << banks.find(bankName)->second->getClientByFio(fio)->getAccount()->getBalance() << endl;
}

void withdrawAccount() {
    std::string bankName, fio;
    double value;
    cout << "Enter the bank name: " << endl;
    cin >> bankName;

    if (banks.find(bankName) == banks.end()) {
        cout << "You entered wrong bank name" << endl;
        return;
    }

    cout << "What's name of your user? " << endl;
    cin >> fio;

    cout << "How many money do u wanna take from account? " << endl;
    cin >> value;

    if (!banks.find(bankName)->second->hasClientWithFio(fio)) {
        cout << "Not found users in bank" << endl;
        return;
    }

    banks.find(bankName)->second->getClientByFio(fio)->withDraw(value);
    cout << "Current balance of ur user - "
         << banks.find(bankName)->second->getClientByFio(fio)->getAccount()->getBalance() << endl;
}

void transferMoneyInner() {
    std::string bankName, fioFrom, fioTo;
    double value;
    cout << "Enter the bank name: " << endl;
    cin >> bankName;

    if (banks.find(bankName) == banks.end()) {
        cout << "You entered wrong bank name" << endl;
        return;
    }

    cout << "What's name of your user FROM? " << endl;
    cin >> fioFrom;

    cout << "What's name of your user TO? " << endl;
    cin >> fioTo;

    cout << "How many money do u want to send? " << endl;
    cin >> value;

    if (!banks.find(bankName)->second->hasClientWithFio(fioFrom)
        && !banks.find(bankName)->second->hasClientWithFio(fioTo)) {
        cout << "Not found users in bank" << endl;
        return;
    }

    banks.find(bankName)->second->transferMoneyInnerClients(fioFrom, fioTo, value);
}

void removeUserFromBank() {
    std::string bankName, fio, accNumber;
    cout << "Enter the bank name: " << endl;
    cin >> bankName;

    if (banks.find(bankName) == banks.end()) {
        cout << "You entered wrong bank name" << endl;
        return;
    }

    cout << "What's name of your user? " << endl;
    cin >> fio;

    banks.find(bankName)->second->removeClientByFio(fio);
}

void addUserToBank() {
    std::string bankName, isJur, fio, accNumber;
    cout << "Enter the bank name: " << endl;
    cin >> bankName;

    if (banks.find(bankName) == banks.end()) {
        cout << "You entered wrong bank name" << endl;
        return;
    }

    cout << "Do you want to create a jur account? [y/n]: " << endl;
    cin >> isJur;
    cout << "What's name of your user? " << endl;
    cin >> fio;
    cout << "What's account number do u wanna set to ur account? " << endl;
    cin >> accNumber;

    Account *account = new Account(accNumber);

    if (isJur == "y" || isJur == "Y") {
        JurClient* client = new JurClient(account, fio);
        cout << "Jur client" << endl;
        banks.find(bankName)->second->addClient(client);
    } else {
        PhysicalClient* client = new PhysicalClient(account, fio);
        cout << "Physical client" << endl;
        banks.find(bankName)->second->addClient(client);
    }

    cout << "Client successfully added to bank" << endl;
}

void printAllBanksUsers() {
    std::string bankName;
    cout << "Enter the bank name: " << endl;
    cin >> bankName;

    if (banks.find(bankName) == banks.end()) {
        cout << "You entered wrong bank name" << endl;
        return;
    }

    map<std::string, Client*> clients = banks.find(bankName)->second->getClients();

    if (clients.empty()) {
        cout << bankName << " has not any clients yet(" << endl;
        return;
    }

    int count = 1;

    for (auto it = clients.begin(); it != clients.end(); ++it) {
        cout << "Client #" << count << " : " << it->second->getFio() << " . Bank account number - "
             << it->second->getAccount()->getNumber() << " Balance - " << it->second->getAccount()->getBalance()
             << std::endl;
        count++;
    }

}

void printAllBanks() {
    int count = 1;
    cout << "~~~~~~~~~~~~~~BANK LIST~~~~~~~~~~~~~~~~" << endl;
    for (auto it = banks.begin(); it != banks.end(); ++it) {
        cout << "Bank #" << count << " : " << it->second->getName() << ". Bank commission is - "
             << it->second->getComissionPercent() << std::endl;
        count++;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void printMainMenu() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1. List all banks" << endl;
    cout << "2. List of bank users" << endl;
    cout << "3. Add user to bank" << endl;
    cout << "4. Remove user from bank" << endl;
    cout << "5. Add money to account" << endl;
    cout << "6. Withdraw user" << endl;
    cout << "7. Transfer money between accounts in one bank" << endl;
    cout << "8. Transfer money between accounts in different banks (only for jur accounts)" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string input;

    while (true) {
        printMainMenu();
        std::cout << "Enter number of command or exit to stop the program" << endl;
        std::cin >> input;

        if (input == "exit") {
            break;
        }
        if (input == "1") {
            printAllBanks();
        }
        if (input == "2") {
            printAllBanksUsers();
        }
        if (input == "3") {
            addUserToBank();
        }
        if (input == "4") {
            removeUserFromBank();
        }
        if (input == "5") {
            addMoneyToAccount();
        }
        if (input == "6") {
            withdrawAccount();
        }
        if (input == "7") {
            transferMoneyInner();
        }
        if (input == "8") {
            transferMoneyOuter();
        }
    }


    return 0;
}
