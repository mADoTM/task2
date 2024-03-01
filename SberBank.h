//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#include "Bank.h"

class SberBank: public Bank {
public:
    std::string getName() const { return "Sber"; };
    int getComissionPercent() const { return 10; }
};