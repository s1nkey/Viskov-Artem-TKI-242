#include "Warehouse.h"

#include <gtest/gtest.h>
#include <stdexcept>

TEST(ProductTests, ConstructorAndStock)
{
    Product product(1, "Сахар", "Завод", 80, 100, 10);
    EXPECT_EQ("Сахар", product.getName());
    EXPECT_EQ(100, product.getQuantity());
    product.addQuantity(5);
    EXPECT_EQ(105, product.getQuantity());
    product.removeQuantity(20);
    EXPECT_EQ(85, product.getQuantity());
    EXPECT_THROW(product.removeQuantity(1000), std::runtime_error);
}

TEST(ProductTests, InvalidData)
{
    EXPECT_THROW(Product(0, "Сахар", "Завод", 80, 100, 10), std::invalid_argument);
    EXPECT_THROW(Product(1, "Сахар", "Завод", 80, -1, 10), std::invalid_argument);
    EXPECT_THROW(Product(1, "Сахар", "Завод", 80, 100, 0), std::invalid_argument);
}

TEST(ClientTests, Polymorphism)
{
    const Store store(1, "Продукты", 5, "ул. Мира");
    const WholesaleClient wholesale(2, "Оптовик", 10, "Анна");
    const Client& first = store;
    const Client& second = wholesale;
    EXPECT_NE(std::string::npos, first.getInfo().find("Магазин:"));
    EXPECT_NE(std::string::npos, second.getInfo().find("Оптовый клиент:"));
}

class WarehouseTests : public ::testing::Test
{
protected:
    Warehouse warehouse{"Склад"};

    void SetUp() override
    {
        warehouse.addProduct(Product(1, "Сахар", "Завод", 80, 100, 10));
        warehouse.addProduct(Product(2, "Мука", "Мельница", 50, 20, 5));
        warehouse.addProduct(Product(3, "Масло", "Завод", 150, 0, 6));
        warehouse.addStore(Store(1, "Продукты", 5, "ул. Мира"));
        warehouse.addStore(Store(2, "Без скидки", 0, "ул. Ленина"));
        warehouse.addWholesaleClient(WholesaleClient(3, "Опт", 10, "Анна"));
    }
};

TEST_F(WarehouseTests, AvailableProducts)
{
    EXPECT_EQ(2u, warehouse.getAvailableProducts().size());
    warehouse.receiveProduct(3, 12);
    EXPECT_EQ(3u, warehouse.getAvailableProducts().size());
}

TEST_F(WarehouseTests, StoreOrdersArePackages)
{
    warehouse.makeStoreOrder(1, 1, 2, "2026-10-20");
    EXPECT_EQ(80, warehouse.getProduct(1).getQuantity());
    EXPECT_EQ(20, warehouse.getStoreOrders(1).at(0).getQuantity());
    EXPECT_DOUBLE_EQ(1520.0, warehouse.getStoreOrders(1).at(0).getTotal());
}

TEST_F(WarehouseTests, WholesaleSalesArePieces)
{
    warehouse.makeWholesaleSale(3, 1, 12, "2026-10-21");
    EXPECT_EQ(88, warehouse.getProduct(1).getQuantity());
    EXPECT_DOUBLE_EQ(864.0, warehouse.getAllSales().at(0).getTotal());
}

TEST_F(WarehouseTests, OrderedProductsWithoutDuplicates)
{
    warehouse.makeStoreOrder(1, 1, 1, "2026-10-20");
    warehouse.makeStoreOrder(1, 1, 1, "2026-10-21");
    warehouse.makeStoreOrder(1, 2, 1, "2026-10-22");
    EXPECT_EQ(2u, warehouse.getOrderedProductsForStore(1).size());
    EXPECT_TRUE(warehouse.getOrderedProductsForStore(2).empty());
}

TEST_F(WarehouseTests, SalesBetweenDates)
{
    warehouse.makeStoreOrder(1, 1, 1, "2026-10-20");
    warehouse.makeWholesaleSale(3, 1, 1, "2026-10-21");
    warehouse.makeStoreOrder(1, 2, 1, "2026-10-25");
    EXPECT_EQ(2u, warehouse.getSalesBetween("2026-10-20", "2026-10-21").size());
    EXPECT_THROW(warehouse.getSalesBetween("2026-10-30", "2026-10-01"), std::invalid_argument);
}

TEST_F(WarehouseTests, DiscountClients)
{
    EXPECT_EQ(2u, warehouse.getClientsWithDiscount().size());
}

TEST_F(WarehouseTests, NotEnoughStock)
{
    EXPECT_THROW(warehouse.makeStoreOrder(1, 1, 50, "2026-10-20"), std::runtime_error);
    EXPECT_THROW(warehouse.makeWholesaleSale(3, 1, 101, "2026-10-20"), std::runtime_error);
    EXPECT_EQ(100, warehouse.getProduct(1).getQuantity());
    EXPECT_TRUE(warehouse.getAllSales().empty());
}

TEST_F(WarehouseTests, InvalidDateAndDuplicateIds)
{
    EXPECT_THROW(warehouse.makeWholesaleSale(3, 1, 1, "2026-02-29"), std::invalid_argument);
    EXPECT_THROW(warehouse.addProduct(Product(1, "Иной", "Завод", 1, 1, 1)), std::invalid_argument);
    EXPECT_THROW(warehouse.addStore(Store(3, "Другой", 0, "ул. Мира")), std::invalid_argument);
}
