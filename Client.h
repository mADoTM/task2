//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#ifndef TASK2_CLIENT_H
#define TASK2_CLIENT_H

#include "Account.h"

class Client {
private:
    Account* _account;
    std::string _fio;
public:
    Client(Account* account, std::string fio);

    void transferMoneyToAnotherClientInBank(double value, Client* another, int bankPercent);

    virtual void addDeposit(double value) { _account->addDeposit(value); }

    void withDraw(double value) { _account->takeDeposit(value); }

    Account* getAccount();

    std::string getFio() { return _fio; }
};

#endif //TASK2_CLIENT_H

