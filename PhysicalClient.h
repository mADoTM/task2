//
// Created by Maxim Dolzhenko on 01.03.2024.
//
#include "Client.h"

class PhysicalClient: public Client {
public:
    PhysicalClient(Account* account, std::string basicString);
};

