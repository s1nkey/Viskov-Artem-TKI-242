#pragma once

#include <string>

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
     * @brief Идентификатор клиента
     */
    int clientId;
    /**
     * @brief Идентификатор проданного товара
     */
    int productId;
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
     * @param clientId Положительный идентификатор клиента
     * @param productId Положительный идентификатор товара
     * @param quantity Положительное число проданных штук
     * @param date Непустая строка даты продажи
     * @param total Неотрицательная сумма продажи
     */
    Sale(const int id, const int clientId, const int productId,
         const int quantity, const std::string& date, const double total);

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
