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
