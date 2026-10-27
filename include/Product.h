#pragma once

#include <string>

// Товар: на складе учитывается поштучно, для магазинов собирается в упаковки.
class Product
{
private:
    int id;
    std::string name;
    std::string manufacturer;
    double price;
    int quantity;
    int packSize;

public:
    Product(const int id, const std::string& name,
            const std::string& manufacturer, const double price,
            const int quantity, const int packSize);

    int getId() const;
    const std::string& getName() const;
    const std::string& getManufacturer() const;
    double getPrice() const;
    int getQuantity() const;
    int getPackSize() const;
    std::string getInfo() const;

    void addQuantity(const int amount);
    void removeQuantity(const int amount);
};
