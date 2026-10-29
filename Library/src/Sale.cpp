#include "Sale.h"

#include <stdexcept>

Sale::Sale(const int id, const int clientId, const int productId,
           const int quantity, const std::string& date, const double total)
    : id(id), clientId(clientId), productId(productId),
      quantity(quantity), date(date), total(total)
{
    if (id <= 0 || clientId <= 0 || productId <= 0 ||
        quantity <= 0 || date.empty() || total < 0)
    {
        throw std::invalid_argument("Неверные данные продажи");
    }
}

int Sale::getId() const { return id; }
int Sale::getClientId() const { return clientId; }
int Sale::getProductId() const { return productId; }
int Sale::getQuantity() const { return quantity; }
const std::string& Sale::getDate() const { return date; }
double Sale::getTotal() const { return total; }

std::string Sale::getInfo() const
{
    return "Продажа №" + std::to_string(id) + " от " + date +
           ", товар №" + std::to_string(productId) +
           ", количество: " + std::to_string(quantity) +
           ", сумма: " + std::to_string(total);
}
