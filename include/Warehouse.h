#pragma once

#include "Product.h"
#include "Sale.h"
#include "Store.h"
#include "WholesaleClient.h"

#include <string>
#include <vector>

// Склад: приход товара, заказы магазинов, оптовые продажи и скидки.
class Warehouse
{
private:
    std::string name;
    std::vector<Product> products;
    std::vector<Store> stores;
    std::vector<WholesaleClient> wholesaleClients;
    std::vector<Sale> sales;
    int nextSaleId = 1;

    Product& findProduct(const int productId);
    int addSale(const int clientId, const int productId,
                const int quantity, const double discount,
                const std::string& date);

public:
    explicit Warehouse(const std::string& name);

    const std::string& getName() const;
    void addProduct(const Product& product);
    void addStore(const Store& store);
    void addWholesaleClient(const WholesaleClient& client);

    const Product& getProduct(const int productId) const;
    const Store& getStore(const int storeId) const;
    const WholesaleClient& getWholesaleClient(const int clientId) const;
    const std::vector<Sale>& getAllSales() const;

    void receiveProduct(const int productId, const int quantity);

    // Заказ магазина: число упаковок, а не отдельных штук.
    int makeStoreOrder(const int storeId, const int productId,
                       const int packageCount, const std::string& date);

    // Опт: количество отдельных штук.
    int makeWholesaleSale(const int clientId, const int productId,
                          const int quantity, const std::string& date);

    std::vector<Product> getAvailableProducts() const;
    std::vector<Sale> getStoreOrders(const int storeId) const;
    std::vector<Product> getOrderedProductsForStore(const int storeId) const;
    std::vector<Sale> getSalesBetween(const std::string& startDate,
                                     const std::string& endDate) const;
    std::vector<std::string> getClientsWithDiscount() const;
};
