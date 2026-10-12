#include "../include/Task1.h"

namespace miit::algebra
{
	Task1::Task1(Matrix& matrix)
		: Exercise(matrix)
	{
	}

	Matrix& Task1::Solve()
	{
		result = OurMatrix;

		for (size_t i = 0; i < result.rowsCount(); ++i)
		{
			std::vector<int>& row = result[static_cast<int>(i)];
			size_t maxColumn = 0;

			for (size_t j = 1; j < result.columnsCount(); ++j)
			{
				if (row[j] > row[maxColumn])
				{
					maxColumn = j;
				}
			}

			row[maxColumn] = -row[maxColumn];
		}

		return result;
	}
}
