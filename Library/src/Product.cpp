#include "Product.h"

#include <stdexcept>

Product::Product(const int id, const std::string& name,
                 const std::string& manufacturer, const double price,
                 const int quantity, const int packSize)
    : id(id), name(name), manufacturer(manufacturer), price(price),
      quantity(quantity), packSize(packSize)
{
    if (id <= 0 || name.empty() || manufacturer.empty() ||
        price < 0 || quantity < 0 || packSize <= 0)
    {
        throw std::invalid_argument("Неверные данные товара");
    }
}

int Product::getId() const { return id; }
const std::string& Product::getName() const { return name; }
const std::string& Product::getManufacturer() const { return manufacturer; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
int Product::getPackSize() const { return packSize; }

std::string Product::getInfo() const
{
    return name + " (" + manufacturer + "), цена: " +
           std::to_string(price) + ", остаток: " +
           std::to_string(quantity) + " шт.";
}

void Product::addQuantity(const int amount)
{
    if (amount <= 0)
    {
        throw std::invalid_argument("Количество должно быть положительным");
    }
    quantity += amount;
}

void Product::removeQuantity(const int amount)
{
    if (amount <= 0)
    {
        throw std::invalid_argument("Количество должно быть положительным");
    }
    if (amount > quantity)
    {
        throw std::runtime_error("Недостаточно товара на складе");
    }
    quantity -= amount;
}
