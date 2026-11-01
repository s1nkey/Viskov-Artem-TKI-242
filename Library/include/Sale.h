#pragma once

#include "Client.h"
#include "Product.h"

#include <string>
#include <vector>

/**
 * @brief Запись об одной продаже одного вида товара
 */
class Sale
{
private:
    /**
     * @brief Уникальный идентификатор продажи
     */
    int id;
    /**
     * @brief Клиенты, участвующие в продаже
     */
    std::vector<Client> clients;
    /**
     * @brief Товары, участвующие в продаже
     */
    std::vector<Product> products;
    /**
     * @brief Количество проданных штук
     */
    int quantity;
    /**
     * @brief Дата продажи
     */
    std::string date;
    /**
     * @brief Итоговая сумма продажи с учётом скидки
     */
    double total;

public:
    /**
     * @brief Создать запись о продаже
     * @param id Положительный идентификатор продажи
     * @param client Клиент, участвующий в продаже
     * @param product Товар, участвующий в продаже
     * @param quantity Положительное число проданных штук
     * @param date Непустая строка даты продажи
     * @param total Неотрицательная сумма продажи
     */
    Sale(const int id, const Client& client, const Product& product,
         const int quantity, const std::string& date, const double total);
    /**
     * @brief Получить данные клиента продажи
     * @return Ссылка на клиента
     */
    const Client& getClient() const;
    /**
     * @brief Получить данные товара продажи
     * @return Ссылка на товар
     */
    const Product& getProduct() const;
    /**
     * @brief Получить клиентов продажи
     * @return Ссылка на вектор клиентов
     */
    const std::vector<Client>& getClients() const;
    /**
     * @brief Получить товары продажи
     * @return Ссылка на вектор товаров
     */
    const std::vector<Product>& getProducts() const;

    /**
     * @brief Получить идентификатор продажи
     * @return Идентификатор продажи
     */
    int getId() const;
    /**
     * @brief Получить идентификатор клиента
     * @return Идентификатор клиента
     */
    int getClientId() const;
    /**
     * @brief Получить идентификатор товара
     * @return Идентификатор товара
     */
    int getProductId() const;
    /**
     * @brief Получить количество проданного товара
     * @return Количество штук
     */
    int getQuantity() const;
    /**
     * @brief Получить дату продажи
     * @return Ссылка на строку даты
     */
    const std::string& getDate() const;
    /**
     * @brief Получить итоговую сумму продажи
     * @return Сумма с учётом скидки
     */
    double getTotal() const;
    /**
     * @brief Получить краткое описание продажи
     * @return Строка с номером, датой, товаром, количеством и суммой
     */
    std::string getInfo() const;
};
