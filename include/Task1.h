#pragma once
#include "Exercise.h"

namespace miit::algebra
{
	/**
	 * @brief Реализация первого задания варианта 5
	 */
	class Task1 : public Exercise
	{
	private:
		/**
		 * @brief Матрица с результатом первого задания
		 */
		Matrix result;

	public:
		/**
		 * @brief Создать объект первого задания варианта 5
		 * @param matrix Матрица, над которой будет выполняться задание
		 */
		explicit Task1(Matrix& matrix);

		/**
		 * @brief Заменить максимальный элемент каждой строки на противоположный по знаку
		 * @return Матрица после выполнения первого задания
		 */
		Matrix& Solve() override;
	};
}
