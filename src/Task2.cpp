#pragma once
#include "Exercise.h"

namespace miit::algebra
{
	/**
	 * @brief Реализация второго задания варианта 5
	 */
	class Task2 : public Exercise
	{
	private:
		/**
		 * @brief Матрица с результатом второго задания
		 */
		Matrix result;

		/**
		 * @brief Проверить, содержит ли столбец указанное значение
		 * @param matrix Матрица для проверки
		 * @param column Индекс столбца
		 * @param value Искомое значение
		 * @return true, если значение есть в столбце, иначе false
		 */
		bool columnContains(const Matrix& matrix, const size_t column, const int value) const;

	public:
		/**
		 * @brief Создать объект второго задания варианта 5
		 * @param matrix Матрица, над которой будет выполняться задание
		 */
		explicit Task2(Matrix& matrix);

		/**
		 * @brief Вставить после каждого столбца, содержащего максимальный элемент матрицы, столбец из нулей
		 * @return Матрица после выполнения второго задания
		 */
		Matrix& Solve() override;
	};
}
