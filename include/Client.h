#pragma once

#include <string>

/**
 * @brief Базовый класс клиента склада
 */
class Client
{
private:
    /**
     * @brief Уникальный идентификатор клиента
     */
    int id;
    /**
     * @brief Название клиента
     */
    std::string name;
    /**
     * @brief Скидка клиента в процентах
     */
    double discount;

public:
    /**
     * @brief Создать клиента
     * @param id Идентификатор клиента
     * @param name Название клиента
     * @param discount Скидка от 0 до 100 процентов
     */
    Client(const int id, const std::string& name, const double discount);
    /**
     * @brief Виртуальный деструктор базового класса
     */
    virtual ~Client() = default;

    /**
     * @brief Получить идентификатор клиента
     * @return Идентификатор клиента
     */
    int getId() const;
    /**
     * @brief Получить название клиента
     * @return Ссылка на название клиента
     */
    const std::string& getName() const;
    /**
     * @brief Получить скидку клиента
     * @return Размер скидки в процентах
     */
    double getDiscount() const;
    /**
     * @brief Получить краткую информацию о клиенте
     * @return Название и размер скидки
     */
    virtual std::string getInfo() const;
};
