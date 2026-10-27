#pragma once

#include "Client.h"
#include <string>

// Магазин заказывает товар упаковками.
class Store : public Client
{
private:
    std::string address;

public:
    Store(const int id, const std::string& name, const double discount,
          const std::string& address);

    const std::string& getAddress() const;
    std::string getInfo() const override;
};
