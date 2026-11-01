#pragma once

#include <string>
#include <vector>

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
    static int nextId;
    static std::vector<int> activeIds;
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
     * @param discount Скидка
     */
    Client(const int id, const std::string& name, const double discount);
    /**
     * @brief Создать клиента с автоматическим ID
     * @param name Название клиента
     * @param discount Скидка
     */
    Client(const std::string& name, const double discount);
    /**
     * @brief Скопировать клиента с сохранением ID
     * @param other Исходный клиент
     */
    Client(const Client& other);
    /**
     * @brief Присвоить данные клиента с сохранением ID
     * @param other Исходный клиент
     * @return Ссылка на текущего клиента
     */
    Client& operator=(const Client& other);
    /**
     * @brief Уничтожить экземпляр клиента
     */
    virtual ~Client();

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
