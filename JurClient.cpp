//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#include "JurClient.h"


void JurClient::transferMoneyToAnotherBankClient(double value, JurClient *another, int bankFromPercent, int bankToPercent) {
    withDraw(value * (1 - 0.01 * bankFromPercent));
    another->addDeposit(value * (1 - 0.01 * bankToPercent));
}

JurClient::JurClient(Account* account, std::string basicString) : Client(account, basicString) {
}

bool JurClient::canSendMoneyToAnotherBankClient(Client *target) {
    auto jurTo = dynamic_cast<JurClient*>(target);
    return jurTo;
}
