#pragma once

#include "Client.h"
#include <string>

/**
 * @brief Магазин — клиент склада, заказывающий товар упаковками
 */
class Store : public Client
{
private:
    /**
     * @brief Адрес магазина
     */
    std::string address;

public:
    /**
     * @brief Создать магазин
     * @param id Положительный идентификатор магазина
     * @param name Наименование магазина
     * @param discount Скидка в процентах от 0 до 100
     * @param address Адрес магазина
     */
    Store(const int id, const std::string& name, const double discount,
          const std::string& address);

    /**
     * @brief Получить адрес магазина
     * @return Ссылка на адрес
     */
    const std::string& getAddress() const;
    /**
     * @brief Получить информацию о магазине
     * @return Наименование, скидка и адрес магазина
     */
    std::string getInfo() const override;
};
