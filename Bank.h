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

    Client* getClientByFio(const std::string& fio);

    void addClient(Client* client);

    void removeClientByFio(const std::string& fio);

    bool hasClientWithFio(const std::string& fio);

    void transferMoneyInnerClients(const std::string& from, const std::string& to, double value);

    void transferMoneyToAnotherBankClient(const std::string& from, Bank* anotherBank, const std::string& to, double value);
};

#endif //TASK2_BANK_H
