//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#ifndef TASK2_BANK_H
#define TASK2_BANK_H

#include "map"
#include "string"
#include "Client.h"
#include "JurClient.h"

class Bank {
private:
    std::map<std::string, Client*> _clients;
    double _balance;
public:
    Bank();

    virtual std::string getName() const { return "Bank"; };

    std::map<std::string, Client*> getClients() const { return _clients; }

    virtual int getComissionPercent() const { return 0; };

    Client* getClientByFio(std::string fio);

    void addClient(Client* client);

    void removeClientByFio(std::string fio);

    bool hasClientWithFio(std::string fio);

    void transferMoneyInnerClients(std::string from, std::string to, double value);

    void transferMoneyToAnotherBankClient(std::string from, Bank* anotherBank, std::string to, double value);
};

#endif //TASK2_BANK_H
