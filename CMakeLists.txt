cmake_minimum_required(VERSION 3.16)
project(WarehouseAccounting LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(WarehouseLibrary STATIC
    Library/src/Product.cpp
    Library/src/Client.cpp
    Library/src/Store.cpp
    Library/src/WholesaleClient.cpp
    Library/src/Sale.cpp
    Library/src/Warehouse.cpp
)
target_include_directories(WarehouseLibrary PUBLIC Library/include)

add_executable(WarehouseConsole main.cpp)
target_link_libraries(WarehouseConsole PRIVATE WarehouseLibrary)

option(BUILD_TESTS "Build GoogleTest tests" ON)
if(BUILD_TESTS)
    find_package(GTest QUIET)
    if(NOT GTest_FOUND)
        include(FetchContent)
        FetchContent_Declare(googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    enable_testing()
    add_executable(WarehouseGoogleTests GoogleTests/WarehouseGoogleTests.cpp)
    target_link_libraries(WarehouseGoogleTests PRIVATE WarehouseLibrary GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(WarehouseGoogleTests)
endif()
