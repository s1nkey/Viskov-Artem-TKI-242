#include "Sale.h"

#include <stdexcept>

Sale::Sale(const int id, const Client& client, const Product& product,
           const int quantity, const std::string& date, const double total)
    : id(id), clients{client}, products{product},
      quantity(quantity), date(date), total(total)
{
    if (id <= 0 || client.getId() <= 0 || product.getId() <= 0 ||
        quantity <= 0 || date.empty() || total < 0)
    {
        throw std::invalid_argument("Неверные данные продажи");
    }
}

int Sale::getId() const { return id; }
const Client& Sale::getClient() const { return clients.front(); }
const Product& Sale::getProduct() const { return products.front(); }
const std::vector<Client>& Sale::getClients() const { return clients; }
const std::vector<Product>& Sale::getProducts() const { return products; }
int Sale::getClientId() const { return getClient().getId(); }
int Sale::getProductId() const { return getProduct().getId(); }
int Sale::getQuantity() const { return quantity; }
const std::string& Sale::getDate() const { return date; }
double Sale::getTotal() const { return total; }

std::string Sale::getInfo() const
{
    return "Продажа №" + std::to_string(id) + " от " + date +
           ", товар №" + std::to_string(getProductId()) +
           ", количество: " + std::to_string(quantity) +
           ", сумма: " + std::to_string(total);
}
