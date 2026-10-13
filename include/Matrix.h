#pragma once
#include "Generator.h"
#include <iostream>
#include <string>
#include <vector>

namespace miit::algebra
{
	/**
	 * @brief Класс для работы с целочисленной матрицей
	 */
	class Matrix
	{
	private:
		/**
		 * @brief Данные матрицы
		 */
		std::vector<std::vector<int>> data;

		/**
		 * @brief Выбросить исключение с указанным сообщением
		 * @param text Сообщение об ошибке
		 */
		void ERROR(const std::string& text) const;

	public:
		/**
		 * @brief Создать пустую матрицу
		 */
		Matrix();

		/**
		 * @brief Создать матрицу заданного размера
		 * @param rows Количество строк
		 * @param columns Количество столбцов
		 */
		Matrix(const int rows, const int columns);

		/**
		 * @brief Создать копию другой матрицы
		 * @param elements Матрица, которую нужно скопировать
		 */
		Matrix(const Matrix& elements) = default;

		/**
		 * @brief Создать матрицу, переместив данные из другого объекта
		 * @param elements Матрица, из которой нужно переместить данные
		 */
		Matrix(Matrix&& elements) noexcept = default;

		/**
		 * @brief Проверить матрицы на равенство
		 * @param other Матрица для сравнения
		 * @return true, если матрицы равны, иначе false
		 */
		bool operator == (const Matrix& other) const;

		/**
		 * @brief Проверить матрицы на неравенство
		 * @param other Матрица для сравнения
		 * @return true, если матрицы различаются, иначе false
		 */
		bool operator != (const Matrix& other) const;

		/**
		 * @brief Присвоить текущей матрице копию другой матрицы
		 * @param other Матрица, которую нужно скопировать
		 * @return Ссылка на текущую матрицу
		 */
		Matrix& operator = (const Matrix& other) = default;

		/**
		 * @brief Переместить данные другой матрицы в текущую
		 * @param other Матрица, из которой нужно переместить данные
		 * @return Ссылка на текущую матрицу
		 */
		Matrix& operator = (Matrix&& other) noexcept = default;

		/**
		 * @brief Получить строку матрицы по индексу
		 * @param row Индекс строки (отрицательный индекс отсчитывается с конца)
		 * @return Ссылка на выбранную строку матрицы
		 */
		std::vector<int>& operator [] (const int row);

		/**
		 * @brief Получить строку неизменяемой матрицы по индексу
		 * @param row Индекс строки (отрицательный индекс отсчитывается с конца)
		 * @return Константная ссылка на выбранную строку матрицы
		 */
		const std::vector<int>& operator [] (const int row) const;

		/**
		 * @brief Найти минимальное значение в матрице
		 * @return Ссылка на минимальное значение
		 */
		const int& minimum() const;

		/**
		 * @brief Найти максимальное значение в матрице
		 * @return Ссылка на максимальное значение
		 */
		const int& maximum() const;

		/**
		 * @brief Получить количество строк матрицы
		 * @return Количество строк
		 */
		size_t rowsCount() const;

		/**
		 * @brief Получить количество столбцов матрицы
		 * @return Количество столбцов
		 */
		size_t columnsCount() const;

		/**
		 * @brief Заполнить матрицу значениями из генератора
		 * @param generator Генератор значений
		 */
		void fill(const Generator& generator);

		/**
		 * @brief Вывести матрицу в поток
		 * @param output Поток для вывода
		 * @param matrix Матрица, которую нужно вывести
		 * @return Поток после вывода матрицы
		 */
		friend std::ostream& operator << (std::ostream& output, const Matrix& matrix);

		/**
		 * @brief Считать элементы матрицы из потока
		 * @param input Поток для чтения
		 * @param matrix Матрица, которую нужно заполнить
		 * @return Поток после чтения матрицы
		 */
		friend std::istream& operator >> (std::istream& input, Matrix& matrix);
	};
}
