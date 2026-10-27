#pragma once

#include <string>

// Одна строка продажи (один вид товара).
class Sale
{
private:
    int id;
    int clientId;
    int productId;
    int quantity;
    std::string date;
    double total;

public:
    Sale(const int id, const int clientId, const int productId,
         const int quantity, const std::string& date, const double total);

    int getId() const;
    int getClientId() const;
    int getProductId() const;
    int getQuantity() const;
    const std::string& getDate() const;
    double getTotal() const;
    std::string getInfo() const;
};
