#include <cstdlib>
#include <iostream>
#include <memory>
#include "../include/Matrix.h"
#include "../include/Generator.h"
#include "../include/RandomGenerator.h"
#include "../include/IStreamGenerator.h"
#include "../include/ConstantGenerator.h"
#include "../include/ZeroGenerator.h"
#include "../include/Task1.h"
#include "../include/Task2.h"
#include <windows.h>

using namespace miit::algebra;

/**
 * @brief Варианты выбора способа заполнения матрицы
 */
enum MyEnum
{
	ONE = 1, TWO, THREE, FOUR,
};

/**
 * @brief Выбрать генератор для заполнения матрицы
 */
std::unique_ptr<Generator> chooseGenerator();

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	try
	{
		int rows = 0;
		int columns = 0;

		std::cout << "Введите число строк n: ";
		std::cin >> rows;
		std::cout << "Введите число столбцов m: ";
		std::cin >> columns;

		Matrix matrix(rows, columns);
		auto generator = chooseGenerator();
		matrix.fill(*generator);

		std::cout << "\nИсходная матрица:\n" << matrix;

		Task1 task1(matrix);
		Matrix result1 = task1.Solve();
		std::cout << "\nПосле задания 1\n" << result1;

		Task2 task2(matrix);
		Matrix result2 = task2.Solve();

		std::cout << "\nПосле задания 2\n";
		if (result2.rowsCount() == 0 || result2.columnsCount() == 0)
		{
			std::cout << "Матрица пустая\n";
		}
		else
		{
			std::cout << result2;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Ошибка: " << e.what() << std::endl;
	}

	return 0;
}

std::unique_ptr<Generator> chooseGenerator()
{
	int choice = 0;
	std::cout << "Как заполнить матрицу?\n"
		<< ONE << " - случайными числами\n"
		<< TWO << " - вводом с клавиатуры\n"
		<< THREE << " - одним конкретным числом\n"
		<< FOUR << " - нулями\n"
		<< "Ваш выбор: ";

	std::cin >> choice;

	switch (choice)
	{
		case ONE:
		{
			int min = 0;
			int max = 0;

			std::cout << "Введите минимум: ";
			std::cin >> min;

			std::cout << "Введите максимум: ";
			std::cin >> max;

			if (min > max)
			{
				throw std::invalid_argument("Неверный диапазон");
			}

			return std::make_unique<RandomGenerator>(min, max);
		}

		case TWO:
			return std::make_unique<IStreamGenerator>(std::cin);

		case THREE:
		{
			int value = 0;
			std::cout << "Введите число: ";
			std::cin >> value;

			return std::make_unique<ConstantGenerator>(value);
		}

		case FOUR:
			return std::make_unique<ZeroGenerator>();

		default:
			throw std::invalid_argument("Неверный выбор");
	}
}
