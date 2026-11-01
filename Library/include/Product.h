#pragma once

#include <string>
#include <vector>

/**
 * @brief Товар на складе с учётом остатков в штуках и размера упаковки
 */
class Product
{
private:
    /**
     * @brief Уникальный идентификатор товара
     */
    int id;
    static int nextId;
    static std::vector<int> activeIds;
    /**
     * @brief Наименование товара
     */
    std::string name;
    /**
     * @brief Наименование производителя
     */
    std::string manufacturer;
    /**
     * @brief Цена одной штуки товара
     */
    double price;
    /**
     * @brief Остаток товара в штуках
     */
    int quantity;
    /**
     * @brief Количество штук в одной упаковке для магазина
     */
    int packSize;

public:
    /**
     * @brief Создать товар
     * @param id Индентификатор товара
     * @param name Наименование товара
     * @param manufacturer Производитель товара
     * @param price Цена одной штуки
     * @param quantity Начальный остаток в штуках
     * @param packSize Количество штук в упаковке
     */
    Product(const int id, const std::string& name,
            const std::string& manufacturer, const double price,
            const int quantity, const int packSize);
    /**
     * @brief Создать товар с автоматическим ID
     * @param name Наименование товара
     * @param manufacturer Производитель товара
     * @param price Цена одной штуки
     * @param quantity Начальный остаток
     * @param packSize Количество штук в упаковке
     */
    Product(const std::string& name, const std::string& manufacturer,
            const double price, const int quantity, const int packSize);
    /**
     * @brief Скопировать товар с сохранением ID
     * @param other Исходный товар
     */
    Product(const Product& other);
    /**
     * @brief Присвоить данные товара с сохранением ID
     * @param other Исходный товар
     * @return Ссылка на текущий товар
     */
    Product& operator=(const Product& other);
    /**
     * @brief Уничтожить экземпляр товара
     */
    ~Product();

    /**
     * @brief Получить идентификатор товара
     * @return Идентификатор товара
     */
    int getId() const;
    /**
     * @brief Получить наименование товара
     * @return Ссылка на наименование товара
     */
    const std::string& getName() const;
    /**
     * @brief Получить производителя товара
     * @return Ссылка на наименование производителя
     */
    const std::string& getManufacturer() const;
    /**
     * @brief Получить цену одной штуки товара
     * @return Цена товара
     */
    double getPrice() const;
    /**
     * @brief Получить остаток товара
     * @return Количество штук на складе
     */
    int getQuantity() const;
    /**
     * @brief Получить размер упаковки
     * @return Количество штук в одной упаковке
     */
    int getPackSize() const;
    /**
     * @brief Получить строку с информацией о товаре
     * @return Наименование, производитель, цена и остаток
     */
    std::string getInfo() const;

    /**
     * @brief Увеличить остаток товара
     * @param amount Количество поступивших штук
     */
    void addQuantity(const int amount);
    /**
     * @brief Уменьшить остаток товара
     * @param amount Количество отгруженных штук
     */
    void removeQuantity(const int amount);
};
