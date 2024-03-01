//
// Created by Maxim Dolzhenko on 01.03.2024.
//
#include "Account.h"
#include <iostream>

Account::Account(std::string number) :
        _balance{0},
        _number{number} {}

double Account::getBalance() {
    return _balance;
}

std::string Account::getNumber() {
    return _number;
}

void Account::addDeposit(double value) {
    if (value >= 0)
        _balance = _balance + value;
}

void Account::takeDeposit(double value) {
    if (_balance > value)
        _balance = _balance - value;
}
