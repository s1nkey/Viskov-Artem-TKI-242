#include "../include/Task2.h"

namespace miit::algebra
{
	Task2::Task2(Matrix& matrix)
		: Exercise(matrix)
	{
	}

	Matrix& Task2::Solve()
	{
		result = OurMatrix;

		const int maximum = result.maximum();

		size_t column = 0;
		while (column < result.columnsCount())
		{
			bool containsMaximum = false;

			for (size_t row = 0; row < result.rowsCount(); ++row)
			{
				if (result(row, column) == maximum)
				{
					containsMaximum = true;
					break;
				}
			}

			if (containsMaximum)
			{
				result.insertZeroColumn(column);
				column += 2;
			}
			else
			{
				++column;
			}
		}

		return result;
	}
}
