#include "Warehouse.h"

#include <stdexcept>

namespace
{
    bool isValidDate(const std::string& date)
    {
        if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        {
            return false;
        }

        for (int i = 0; i < 10; ++i)
        {
            if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9'))
            {
                return false;
            }
        }

        const int year = std::stoi(date.substr(0, 4));
        const int month = std::stoi(date.substr(5, 2));
        const int day = std::stoi(date.substr(8, 2));
        if (year == 0 || month < 1 || month > 12 || day < 1)
        {
            return false;
        }

        const int daysInMonth[12] = {31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31};
        int maxDay = daysInMonth[month - 1];
        const bool leapYear = (year % 4 == 0 && year % 100 != 0) ||
                              year % 400 == 0;
        if (month == 2 && leapYear)
        {
            maxDay = 29;
        }
        return day <= maxDay;
    }
}

Warehouse::Warehouse(const std::string& name) : name(name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Название склада не задано");
    }
}

const std::string& Warehouse::getName() const { return name; }

void Warehouse::addProduct(const Product& product)
{
    for (const Product& existing : products)
    {
        if (existing.getId() == product.getId())
        {
            throw std::invalid_argument("Товар с таким ID уже есть");
        }
    }
    products.push_back(product);
}

void Warehouse::addStore(const Store& store)
{
    for (const Store& existing : stores)
    {
        if (existing.getId() == store.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    for (const WholesaleClient& existing : wholesaleClients)
    {
        if (existing.getId() == store.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    stores.push_back(store);
}

void Warehouse::addWholesaleClient(const WholesaleClient& client)
{
    for (const Store& existing : stores)
    {
        if (existing.getId() == client.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    for (const WholesaleClient& existing : wholesaleClients)
    {
        if (existing.getId() == client.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    wholesaleClients.push_back(client);
}

Product& Warehouse::findProduct(const int productId)
{
    for (Product& product : products)
    {
        if (product.getId() == productId)
        {
            return product;
        }
    }
    throw std::invalid_argument("Товар не найден");
}

const Product& Warehouse::getProduct(const int productId) const
{
    for (const Product& product : products)
    {
        if (product.getId() == productId)
        {
            return product;
        }
    }
    throw std::invalid_argument("Товар не найден");
}

const Store& Warehouse::getStore(const int storeId) const
{
    for (const Store& store : stores)
    {
        if (store.getId() == storeId)
        {
            return store;
        }
    }
    throw std::invalid_argument("Магазин не найден");
}

const WholesaleClient& Warehouse::getWholesaleClient(const int clientId) const
{
    for (const WholesaleClient& client : wholesaleClients)
    {
        if (client.getId() == clientId)
        {
            return client;
        }
    }
    throw std::invalid_argument("Оптовый клиент не найден");
}

const std::vector<Sale>& Warehouse::getAllSales() const
{
    return sales;
}

void Warehouse::receiveProduct(const int productId, const int quantity)
{
    findProduct(productId).addQuantity(quantity);
}

int Warehouse::addSale(const int clientId, const int productId,
                       const int quantity, const double discount,
                       const std::string& date)
{
    if (!isValidDate(date) || quantity <= 0)
    {
        throw std::invalid_argument("Неверная дата или количество");
    }

    Product& product = findProduct(productId);
    if (quantity > product.getQuantity())
    {
        throw std::runtime_error("Недостаточно товара на складе");
    }

    const double total = product.getPrice() * quantity *
                         (100.0 - discount) / 100.0;
    const int saleId = nextSaleId;
    sales.emplace_back(saleId, clientId, productId, quantity, date, total);
    product.removeQuantity(quantity);
    ++nextSaleId;
    return saleId;
}

int Warehouse::makeStoreOrder(const int storeId, const int productId,
                              const int packageCount, const std::string& date)
{
    const Store& store = getStore(storeId);
    if (packageCount <= 0)
    {
        throw std::invalid_argument("Число упаковок должно быть положительным");
    }
    const Product& product = getProduct(productId);
    if (packageCount > product.getQuantity() / product.getPackSize())
    {
        throw std::runtime_error("Недостаточно товара для упаковок");
    }
    const int quantity = packageCount * product.getPackSize();
    return addSale(storeId, productId, quantity, store.getDiscount(), date);
}

int Warehouse::makeWholesaleSale(const int clientId, const int productId,
                                 const int quantity, const std::string& date)
{
    const WholesaleClient& client = getWholesaleClient(clientId);
    return addSale(clientId, productId, quantity, client.getDiscount(), date);
}

std::vector<Product> Warehouse::getAvailableProducts() const
{
    std::vector<Product> result;
    for (const Product& product : products)
    {
        if (product.getQuantity() > 0)
        {
            result.push_back(product);
        }
    }
    return result;
}

std::vector<Sale> Warehouse::getStoreOrders(const int storeId) const
{
    getStore(storeId);
    std::vector<Sale> result;
    for (const Sale& sale : sales)
    {
        if (sale.getClientId() == storeId)
        {
            result.push_back(sale);
        }
    }
    return result;
}

std::vector<Product> Warehouse::getOrderedProductsForStore(const int storeId) const
{
    const std::vector<Sale> orders = getStoreOrders(storeId);
    std::vector<Product> result;
    for (const Sale& sale : orders)
    {
        bool alreadyAdded = false;
        for (const Product& product : result)
        {
            if (product.getId() == sale.getProductId())
            {
                alreadyAdded = true;
            }
        }
        if (!alreadyAdded)
        {
            result.push_back(getProduct(sale.getProductId()));
        }
    }
    return result;
}

std::vector<Sale> Warehouse::getSalesBetween(const std::string& startDate,
                                              const std::string& endDate) const
{
    if (!isValidDate(startDate) || !isValidDate(endDate) || startDate > endDate)
    {
        throw std::invalid_argument("Неверный период дат");
    }

    std::vector<Sale> result;
    for (const Sale& sale : sales)
    {
        if (sale.getDate() >= startDate && sale.getDate() <= endDate)
        {
            result.push_back(sale);
        }
    }
    return result;
}

std::vector<std::string> Warehouse::getClientsWithDiscount() const
{
    std::vector<std::string> result;
    for (const Store& store : stores)
    {
        if (store.getDiscount() > 0)
        {
            result.push_back(store.getInfo());
        }
    }
    for (const WholesaleClient& client : wholesaleClients)
    {
        if (client.getDiscount() > 0)
        {
            result.push_back(client.getInfo());
        }
    }
    return result;
}
