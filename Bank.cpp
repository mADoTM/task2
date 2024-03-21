//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#include "Bank.h"
#include "JurClient.h"
#include "iostream"

using namespace std;

Bank::Bank() :
        _balance(0) {}

bool Bank::hasClientWithFio(const std::string& fio) {
    return _clients.find(fio) != _clients.end();
}

void Bank::addClient(Client* client) {
    _clients.insert(make_pair(client->getFio(), client));
}

Client* Bank::getClientByFio(const std::string& fio) {
    return _clients.find(fio)->second;
}

void Bank::transferMoneyInnerClients(const std::string& from, const std::string& to, double value) {
    if (!hasClientWithFio(from) || !hasClientWithFio(to))
        return;

    Client* fromClient = getClientByFio(from);
    Client* toClient = getClientByFio(to);

    _balance += value * (1 - 0.01 * getComissionPercent());

    fromClient->transferMoneyToAnotherClientInBank(value, toClient, getComissionPercent());
}

void Bank::transferMoneyToAnotherBankClient(const std::string& from, Bank* anotherBank, const std::string& to, double value) {
    if (!hasClientWithFio(from) || !anotherBank->hasClientWithFio(to))
        return;

    Client* clientF =  getClientByFio(from);
    Client* clientT = anotherBank->getClientByFio(to);

    if(clientF->canSendMoneyToAnotherBankClient(clientT)) {
        double commission = value * (1 - 0.01 * getComissionPercent());
        _balance += commission;
        clientF->transferMoneyToAnotherClientInBank(value, clientT, getComissionPercent());
    } else {
        throw std::invalid_argument("Transaction is cancelled. You've selected an account with no access to transfer from outer bank");
    }
}

void Bank::removeClientByFio(const std::string& fio) {
    if(hasClientWithFio(fio)) {
        _clients.erase(fio);
        cout << "Client successfully deleted from bank: " << getName() << endl;
    }
    else {
        cout << "Client not found in bank - " << getName() << endl;
    }
}

Bank::~Bank() {
    for (auto & client : _clients) {
        delete client.second;
    }
}
