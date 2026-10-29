#include "Client.h"

#include <stdexcept>

Client::Client(const int id, const std::string& name, const double discount)
    : id(id), name(name), discount(discount)
{
    if (id <= 0 || name.empty() || discount < 0 || discount > 100)
    {
        throw std::invalid_argument("Неверные данные клиента");
    }
}

int Client::getId() const { return id; }
const std::string& Client::getName() const { return name; }
double Client::getDiscount() const { return discount; }

std::string Client::getInfo() const
{
    return name + ", скидка: " + std::to_string(discount) + "%";
}
