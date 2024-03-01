//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#include "Bank.h"

class GazpromBank : public Bank {
public:
    std::string getName() const { return "Gazprom"; };
    int getComissionPercent() const { return 5; }
};