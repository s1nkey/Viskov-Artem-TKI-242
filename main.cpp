#include "Warehouse.h"

#include <functional>
#include <iostream>
#include <vector>

/**
 * @brief Работа системы складского учёта
 * @return 0 при успешном завершении программы
 */
int main()
{
    Warehouse warehouse("Центральный склад");
    warehouse.addProduct(Product(1, "Сахар", "Сахарный завод", 80, 100, 10));
    warehouse.addProduct(Product(2, "Мука", "Мельница", 60, 80, 5));
    warehouse.addProduct(Product(3, "Масло", "Молочный завод", 150, 30, 6));

    const Store store(1, "Магазин Продукты", 5, "ул. Ленина, 10");
    const Store secondStore(2, "Магазин Рядом", 0, "ул. Мира, 5");
    const WholesaleClient buyer(3, "ОптТорг", 10, "Иван Петров");
    warehouse.addStore(store);
    warehouse.addStore(secondStore);
    warehouse.addWholesaleClient(buyer);

    const std::vector<std::reference_wrapper<const Client>> clients =
    {
        std::cref(store), std::cref(secondStore), std::cref(buyer)
    };

    std::cout << "Клиенты склада:\n";
    for (const Client& client : clients)
    {
        std::cout << client.getInfo() << '\n';
    }

    warehouse.makeStoreOrder(1, 1, 2, "2026-10-20");
    warehouse.makeStoreOrder(1, 2, 3, "2026-10-21");
    warehouse.makeWholesaleSale(3, 1, 12, "2026-10-22");
    warehouse.receiveProduct(2, 20);

    std::cout << "\n1. Ассортимент на складе:\n";
    for (const Product& product : warehouse.getAvailableProducts())
    {
        std::cout << product.getInfo() << '\n';
    }

    std::cout << "\n2. Ассортимент, заказанный магазином Продукты:\n";
    for (const Product& product : warehouse.getOrderedProductsForStore(1))
    {
        std::cout << product.getName() << '\n';
    }

    std::cout << "\n3. Продажи за 20.10.2026 - 21.10.2026:\n";
    for (const Sale& sale : warehouse.getSalesBetween("2026-10-20", "2026-10-21"))
    {
        std::cout << sale.getInfo() << '\n';
    }

    std::cout << "\n4. Клиенты со скидкой:\n";
    for (const std::string& info : warehouse.getClientsWithDiscount())
    {
        std::cout << info << '\n';
    }

    return 0;
}
