#include "../include/Task2.h"

namespace miit::algebra
{
	Task2::Task2(Matrix& matrix)
		: Exercise(matrix)
	{
	}

	bool Task2::columnContains(const Matrix& matrix, const size_t column, const int value) const
	{
		for (size_t row = 0; row < matrix.rowsCount(); ++row)
		{
			if (matrix[static_cast<int>(row)][column] == value)
			{
				return true;
			}
		}

		return false;
	}

	Matrix& Task2::Solve()
	{
		const int maximum = OurMatrix.maximum();
		const size_t rows = OurMatrix.rowsCount();
		const size_t columns = OurMatrix.columnsCount();

		size_t maximumColumns = 0;
		for (size_t column = 0; column < columns; ++column)
		{
			if (columnContains(OurMatrix, column, maximum))
			{
				++maximumColumns;
			}
		}

		result = Matrix(static_cast<int>(rows), static_cast<int>(columns + maximumColumns));

		size_t target = 0;
		for (size_t column = 0; column < columns; ++column)
		{
			for (size_t row = 0; row < rows; ++row)
			{
				result[static_cast<int>(row)][target] = OurMatrix[static_cast<int>(row)][column];
			}
			++target;

			if (columnContains(OurMatrix, column, maximum))
			{
				// Столбец из нулей уже создан конструктором Matrix, пропускаем его
				++target;
			}
		}

		return result;
	}
}
