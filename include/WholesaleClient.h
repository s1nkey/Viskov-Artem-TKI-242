#pragma once

#include "Client.h"
#include <string>

/**
 * @brief Оптовый покупатель, приобретающий товар поштучно
 */
class WholesaleClient : public Client
{
private:
    /**
     * @brief Имя контактного лица клиента
     */
    std::string contactPerson;

public:
    /**
     * @brief Создать оптового покупателя
     * @param id Положительный идентификатор клиента
     * @param name Наименование клиента
     * @param discount Скидка в процентах
     * @param contactPerson Имя контактного лица
     */
    WholesaleClient(const int id, const std::string& name,
                    const double discount, const std::string& contactPerson);

    /**
     * @brief Получить контактное лицо клиента
     * @return Ссылка на имя контактного лица
     */
    const std::string& getContactPerson() const;
    /**
     * @brief Получить информацию об оптовом клиенте
     * @return Наименование, скидка и контактное лицо
     */
    std::string getInfo() const override;
};
