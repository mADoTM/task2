//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#ifndef TASK2_ACCOUNT_H
#define TASK2_ACCOUNT_H

#include <string>

class Account {
private:
    double _balance;
    std::string _number;
public:
    Account(std::string number);

    void addDeposit(double value);

    void takeDeposit(double value);

    double getBalance();

    std::string getNumber();
};

#endif // TASK2_ACCOUNT_H


