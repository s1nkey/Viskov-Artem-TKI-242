#include "../include/Matrix.h"
#include <stdexcept>

namespace miit::algebra
{
	void Matrix::ERROR(const std::string& text) const
	{
		throw std::invalid_argument(text);
	}

	Matrix::Matrix()
	{
	}

	Matrix::Matrix(const int rows, const int columns)
	{
		if (rows <= 0 || columns <= 0)
		{
			ERROR("Неверные размеры матрицы");
		}

		data.resize(static_cast<size_t>(rows), std::vector<int>(static_cast<size_t>(columns), 0));
	}

	bool Matrix::operator == (const Matrix& other) const
	{
		return data == other.data;
	}

	bool Matrix::operator != (const Matrix& other) const
	{
		return !(*this == other);
	}

	std::vector<int>& Matrix::operator [] (const int row)
	{
		return const_cast<std::vector<int>&>(static_cast<const Matrix&>(*this)[row]);
	}

	const std::vector<int>& Matrix::operator [] (const int row) const
	{
		const int rowsTotal = static_cast<int>(data.size());
		const int actualRow = row < 0 ? rowsTotal + row : row;

		if (actualRow < 0 || actualRow >= rowsTotal)
		{
			ERROR("Выход за пределы матрицы");
		}

		return data[static_cast<size_t>(actualRow)];
	}

	const int& Matrix::minimum() const
	{
		if (data.empty() || data[0].empty())
		{
			ERROR("Матрица пустая");
		}

		size_t minRow = 0;
		size_t minColumn = 0;

		for (size_t i = 0; i < data.size(); ++i)
		{
			for (size_t j = 0; j < data[i].size(); ++j)
			{
				if (data[i][j] < data[minRow][minColumn])
				{
					minRow = i;
					minColumn = j;
				}
			}
		}

		return data[minRow][minColumn];
	}

	const int& Matrix::maximum() const
	{
		if (data.empty() || data[0].empty())
		{
			ERROR("Матрица пустая");
		}

		size_t maxRow = 0;
		size_t maxColumn = 0;

		for (size_t i = 0; i < data.size(); ++i)
		{
			for (size_t j = 0; j < data[i].size(); ++j)
			{
				if (data[i][j] > data[maxRow][maxColumn])
				{
					maxRow = i;
					maxColumn = j;
				}
			}
		}

		return data[maxRow][maxColumn];
	}

	size_t Matrix::rowsCount() const
	{
		return data.size();
	}

	size_t Matrix::columnsCount() const
	{
		return data.empty() ? 0 : data[0].size();
	}

	void Matrix::fill(const Generator& generator)
	{
		for (std::vector<int>& row : data)
		{
			for (int& value : row)
			{
				value = generator.generate();
			}
		}
	}

	std::ostream& operator << (std::ostream& output, const Matrix& matrix)
	{
		for (const std::vector<int>& row : matrix.data)
		{
			for (size_t j = 0; j < row.size(); ++j)
			{
				output << row[j];
				if (j + 1 < row.size())
				{
					output << '\t';
				}
			}
			output << '\n';
		}

		return output;
	}

	std::istream& operator >> (std::istream& input, Matrix& matrix)
	{
		for (std::vector<int>& row : matrix.data)
		{
			for (int& value : row)
			{
				input >> value;
			}
		}

		return input;
	}
}
