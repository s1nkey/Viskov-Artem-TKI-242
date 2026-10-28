#pragma once

#include "Product.h"
#include "Sale.h"
#include "Store.h"
#include "WholesaleClient.h"

#include <string>
#include <vector>

/**
 * @brief Склад: поступления товаров, заказы магазинов, оптовые продажи и скидки
 */
class Warehouse
{
private:
    /**
     * @brief Наименование склада
     */
    std::string name;
    /**
     * @brief Товары на складе
     */
    std::vector<Product> products;
    /**
     * @brief Магазины — клиенты склада
     */
    std::vector<Store> stores;
    /**
     * @brief Оптовые клиенты склада
     */
    std::vector<WholesaleClient> wholesaleClients;
    /**
     * @brief История продаж и заказов
     */
    std::vector<Sale> sales;
    /**
     * @brief Идентификатор следующей продажи
     */
    int nextSaleId = 1;

    /**
     * @brief Найти товар для изменения его остатка
     * @param productId Идентификатор товара
     * @return Ссылка на товар
     */
    Product& findProduct(const int productId);
    /**
     * @brief Записать продажу со скидкой и уменьшить остаток товара
     * @param clientId Идентификатор клиента
     * @param productId Идентификатор товара
     * @param quantity Число продаваемых штук
     * @param discount Скидка клиента в процентах
     * @param date Дата продажи в формате ГГГГ-ММ-ДД
     * @return Идентификатор добавленной продажи
     */
    int addSale(const int clientId, const int productId,
                const int quantity, const double discount,
                const std::string& date);

public:
    /**
     * @brief Создать склад.
     * @param name Наименование склада
     */
    explicit Warehouse(const std::string& name);

    /**
     * @brief Получить название склада
     * @return Ссылка на название
     */
    const std::string& getName() const;
    /**
     * @brief Добавить товар на склад.
     * @param product Товар для добавления
     */
    void addProduct(const Product& product);
    /**
     * @brief Добавить магазин в список клиентов
     * @param store Магазин для добавления
     */
    void addStore(const Store& store);
    /**
     * @brief Добавить оптового клиента
     * @param client Клиент для добавления
     */
    void addWholesaleClient(const WholesaleClient& client);

    /**
     * @brief Найти товар по идентификатору
     * @param productId Идентификатор товара
     * @return Ссылка на найденный товар
     */
    const Product& getProduct(const int productId) const;
    /**
     * @brief Найти магазин по идентификатору
     * @param storeId Идентификатор магазина
     * @return Ссылка на найденный магазин
     */
    const Store& getStore(const int storeId) const;
    /**
     * @brief Найти оптового клиента по идентификатору
     * @param clientId Идентификатор клиента
     * @return Ссылка на найденного клиента
     */
    const WholesaleClient& getWholesaleClient(const int clientId) const;
    /**
     * @brief Получить историю всех продаж
     * @return Ссылка на список продаж
     */
    const std::vector<Sale>& getAllSales() const;

    /**
     * @brief Принять партию товара на склад
     * @param productId Идентификатор товара
     * @param quantity Число поступивших штук
     */
    void receiveProduct(const int productId, const int quantity);

    /**
     * @brief Оформить заказ магазина с отпуском товара упаковками
     * @param storeId Идентификатор магазина
     * @param productId Идентификатор товара
     * @param packageCount Количество упаковок (не штук)
     * @param date Дата заказа в формате ГГГГ-ММ-ДД
     * @return Идентификатор созданной продажи
     */
    int makeStoreOrder(const int storeId, const int productId,
                       const int packageCount, const std::string& date);

    /**
     * @brief Оформить оптовую продажу товара поштучно
     * @param clientId Идентификатор оптового клиента
     * @param productId Идентификатор товара
     * @param quantity Число продаваемых штук
     * @param date Дата продажи в формате ГГГГ-ММ-ДД
     * @return Идентификатор созданной продажи
     */
    int makeWholesaleSale(const int clientId, const int productId,
                          const int quantity, const std::string& date);

    /**
     * @brief Получить ассортимент товаров в наличии
     * @return Список товаров с положительным остатком
     */
    std::vector<Product> getAvailableProducts() const;
    /**
     * @brief Получить записи заказов выбранного магазина
     * @param storeId Идентификатор магазина
     * @return Список продаж выбранному магазину
     */
    std::vector<Sale> getStoreOrders(const int storeId) const;
    /**
     * @brief Получить ассортимент товаров, которые заказывал магазин
     * @param storeId Идентификатор магазина
     * @return Список товаров без повторов, независимо от их текущего остатка
     */
    std::vector<Product> getOrderedProductsForStore(const int storeId) const;
    /**
     * @brief Получить продажи за указанный период включительно
     * @param startDate Начальная дата в формате ГГГГ-ММ-ДД
     * @param endDate Конечная дата в формате ГГГГ-ММ-ДД
     * @return Список продаж за указанный период
     */
    std::vector<Sale> getSalesBetween(const std::string& startDate,
                                     const std::string& endDate) const;
    /**
     * @brief Получить список клиентов с ненулевой скидкой
     * @return Строки с информацией о магазинах и оптовых клиентах со скидкой
     */
    std::vector<std::string> getClientsWithDiscount() const;
};
