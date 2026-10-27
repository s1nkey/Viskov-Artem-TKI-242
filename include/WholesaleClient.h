#pragma once

#include "Client.h"
#include <string>

// Оптовый покупатель получает товар поштучно.
class WholesaleClient : public Client
{
private:
    std::string contactPerson;

public:
    WholesaleClient(const int id, const std::string& name,
                    const double discount, const std::string& contactPerson);

    const std::string& getContactPerson() const;
    std::string getInfo() const override;
};
