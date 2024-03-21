//
// Created by Maxim Dolzhenko on 01.03.2024.
//
#include "Client.h"

#include <utility>


Client::Client(Account* account, std::string fio)
    : _account(std::move(account)), _fio(std::move(fio))
{}

void Client::transferMoneyToAnotherClientInBank(double value, Client* another, int bankPercent) {
    getAccount()->takeDeposit(value * (1 + 0.01 * bankPercent));
    another->getAccount()->addDeposit(value);
}

Account* Client::getAccount() {
    return _account;
}

Client::~Client() {
    delete _account;
}
