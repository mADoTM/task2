//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#include "Bank.h"
#include "JurClient.h"
#include "iostream"

using namespace std;

Bank::Bank() :
        _balance(0) {}

bool Bank::hasClientWithFio(std::string fio) {
    return _clients.find(fio) != _clients.end();
}

void Bank::addClient(Client* client) {
    _clients.insert(make_pair(client->getFio(), client));
}

Client* Bank::getClientByFio(std::string fio) {
    return _clients.find(fio)->second;
}

void Bank::transferMoneyInnerClients(std::string from, std::string to, double value) {
    if (!hasClientWithFio(from) || !hasClientWithFio(to))
        return;

    Client* fromClient = getClientByFio(from);
    Client* toClient = getClientByFio(to);

    _balance += value * (1 - 0.01 * getComissionPercent());

    fromClient->transferMoneyToAnotherClientInBank(value, toClient, getComissionPercent());
}

void Bank::transferMoneyToAnotherBankClient(std::string from, Bank* anotherBank, std::string to, double value) {
    if (!hasClientWithFio(from) || !anotherBank->hasClientWithFio(to))
        return;

    Client* clientF =  getClientByFio(from);
    Client* clientT = anotherBank->getClientByFio(to);

    JurClient* jurFrom = dynamic_cast<JurClient*>(clientF);
    JurClient* jurTo = dynamic_cast<JurClient*>(clientT);

    if(jurFrom && jurTo) {
        _balance += value * (1 - 0.01 * getComissionPercent());
        jurFrom->transferMoneyToAnotherBankClient(value, jurTo, getComissionPercent(), anotherBank->getComissionPercent());
    } else {
        std::cout << "You have selected not a jur accounts" << endl;
    }
}

void Bank::removeClientByFio(std::string fio) {
    if(hasClientWithFio(fio)) {
        _clients.erase(fio);
        cout << "Client successfully deleted from bank: " << getName() << endl;
    }
    else {
        cout << "Client not found in bank - " << getName() << endl;
    }
}
