#pragma once

#include <string>

// Общий базовый класс для клиентов склада.
class Client
{
private:
    int id;
    std::string name;
    double discount;

public:
    Client(const int id, const std::string& name, const double discount);
    virtual ~Client() = default;

    int getId() const;
    const std::string& getName() const;
    double getDiscount() const;
    virtual std::string getInfo() const;
};
