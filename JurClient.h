//
// Created by Maxim Dolzhenko on 01.03.2024.
//

#ifndef TASK2_JURCLIENT_H
#define TASK2_JURCLIENT_H

#include "Client.h"


class JurClient : public Client {
public:
    JurClient(Account *account, std::string basicString);

    void transferMoneyToAnotherBankClient(double value, JurClient *another, int bankFromPercent, int bankToPercent);

    bool canSendMoneyToAnotherBankClient(Client* target) override;
};

#endif //TASK2_JURCLIENT_H
