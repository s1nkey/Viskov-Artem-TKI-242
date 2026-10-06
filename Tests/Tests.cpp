#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include "Matrix.h"
#include "ConstantGenerator.h"
#include "ZeroGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

TEST(ConstantGeneratorTests, ReturnsSpecifiedValue)
{
	const ConstantGenerator generator(7);

	EXPECT_EQ(generator.generate(), 7);
	EXPECT_EQ(generator.generate(), 7);
}

TEST(ZeroGeneratorTests, ReturnsZero)
{
	const ZeroGenerator generator;

	EXPECT_EQ(generator.generate(), 0);
}

TEST(IStreamGeneratorTests, ReadsValuesFromStream)
{
	std::istringstream input("12 -5");
	const IStreamGenerator generator(input);

	EXPECT_EQ(generator.generate(), 12);
	EXPECT_EQ(generator.generate(), -5);
}

TEST(RandomGeneratorTests, GeneratesValuesInsideRange)
{
	const RandomGenerator generator(1, 10);

	for (size_t i = 0; i < 50; ++i)
	{
		const int value = generator.generate();

		EXPECT_GE(value, 1);
		EXPECT_LE(value, 10);
	}
}

TEST(RandomGeneratorTests, ThrowsOnWrongRange)
{
	EXPECT_THROW(RandomGenerator(10, 1), std::invalid_argument);
}

TEST(MatrixTests, DefaultConstructorCreatesEmptyMatrix)
{
	const Matrix matrix;

	EXPECT_EQ(matrix.rowsCount(), static_cast<size_t>(0));
	EXPECT_EQ(matrix.columnsCount(), static_cast<size_t>(0));
}

TEST(MatrixTests, ConstructorSetsSizeAndFillsWithZeroes)
{
	const Matrix matrix(2, 3);

	EXPECT_EQ(matrix.rowsCount(), static_cast<size_t>(2));
	EXPECT_EQ(matrix.columnsCount(), static_cast<size_t>(3));
	EXPECT_EQ(matrix(0, 0), 0);
	EXPECT_EQ(matrix(1, 2), 0);
}

TEST(MatrixTests, ConstructorThrowsOnWrongSize)
{
	EXPECT_THROW(Matrix(0, 3), std::invalid_argument);
	EXPECT_THROW(Matrix(-1, 2), std::invalid_argument);
}

TEST(MatrixTests, CopyConstructorCreatesIndependentCopy)
{
	Matrix matrix(1, 2);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;

	Matrix copy(matrix);
	copy(0, 0) = 100;

	EXPECT_EQ(matrix(0, 0), 1);
	EXPECT_EQ(copy(0, 1), 2);
}

TEST(MatrixTests, AssignmentCopiesValues)
{
	Matrix matrix(1, 2);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	Matrix copy;
	copy = matrix;

	EXPECT_EQ(copy(0, 0), 1);
	EXPECT_EQ(copy(0, 1), 2);
}

TEST(MatrixTests, ComparesMatrices)
{
	Matrix left(1, 2);
	left(0, 0) = 1;
	left(0, 1) = 2;

	Matrix right(1, 2);
	right(0, 0) = 1;
	right(0, 1) = 2;

	EXPECT_TRUE(left == right);

	right(0, 1) = 3;

	EXPECT_TRUE(left != right);
}

TEST(MatrixTests, IndexOperatorThrowsWhenOutOfRange)
{
	Matrix matrix(2, 2);

	EXPECT_THROW(matrix(2, 0), std::invalid_argument);
	EXPECT_THROW(matrix(0, 2), std::invalid_argument);
}

TEST(MatrixTests, IndexOperatorSupportsNegativeIndexes)
{
	Matrix matrix(2, 2);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	matrix(1, 0) = 3;
	matrix(1, 1) = 4;

	EXPECT_EQ(matrix(-1, -1), 4);
	EXPECT_EQ(matrix(-2, -2), 1);
	EXPECT_THROW(matrix(-3, 0), std::invalid_argument);
	EXPECT_THROW(matrix(0, -3), std::invalid_argument);
}

TEST(MatrixTests, FindsMinimumAndMaximum)
{
	Matrix matrix(2, 2);
	matrix(0, 0) = -7;
	matrix(0, 1) = 2;
	matrix(1, 0) = 3;
	matrix(1, 1) = 9;

	EXPECT_EQ(matrix.minimum(), -7);
	EXPECT_EQ(matrix.maximum(), 9);
}

TEST(MatrixTests, MinimumThrowsOnEmptyMatrix)
{
	const Matrix matrix;

	EXPECT_THROW(matrix.minimum(), std::invalid_argument);
	EXPECT_THROW(matrix.maximum(), std::invalid_argument);
}

TEST(MatrixTests, FillsMatrixWithGenerator)
{
	Matrix matrix(2, 2);
	const ConstantGenerator generator(5);

	matrix.fill(generator);

	EXPECT_EQ(matrix(0, 0), 5);
	EXPECT_EQ(matrix(0, 1), 5);
	EXPECT_EQ(matrix(1, 0), 5);
	EXPECT_EQ(matrix(1, 1), 5);
}

TEST(MatrixTests, InsertsZeroColumn)
{
	Matrix matrix(2, 3);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	matrix(0, 2) = 3;
	matrix(1, 0) = 4;
	matrix(1, 1) = 5;
	matrix(1, 2) = 6;

	matrix.insertZeroColumn(1);

	EXPECT_EQ(matrix.columnsCount(), static_cast<size_t>(4));
	EXPECT_EQ(matrix(0, 0), 1);
	EXPECT_EQ(matrix(0, 1), 2);
	EXPECT_EQ(matrix(0, 2), 0);
	EXPECT_EQ(matrix(0, 3), 3);
	EXPECT_EQ(matrix(1, 2), 0);
}

TEST(MatrixTests, InsertZeroColumnThrowsOnWrongIndex)
{
	Matrix matrix(2, 2);

	EXPECT_THROW(matrix.insertZeroColumn(2), std::invalid_argument);
}

TEST(MatrixTests, WritesMatrixToStream)
{
	Matrix matrix(2, 2);
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	matrix(1, 0) = 3;
	matrix(1, 1) = 4;

	std::ostringstream output;
	output << matrix;

	EXPECT_EQ(output.str(), "1\t2\n3\t4\n");
}

TEST(MatrixTests, ReadsMatrixFromStream)
{
	Matrix matrix(1, 2);
	std::istringstream input("8 9");

	input >> matrix;

	EXPECT_EQ(matrix(0, 0), 8);
	EXPECT_EQ(matrix(0, 1), 9);
}

TEST(Task1Tests, ReplacesMaximumInEachRowWithOppositeSign)
{
	Matrix matrix(2, 3);
	matrix(0, 0) = -1;
	matrix(0, 1) = 7;
	matrix(0, 2) = 2;
	matrix(1, 0) = 7;
	matrix(1, 1) = 6;
	matrix(1, 2) = -4;

	Task1 task(matrix);

	Matrix& result = task.Solve();

	EXPECT_EQ(result(0, 0), -1);
	EXPECT_EQ(result(0, 1), -7);
	EXPECT_EQ(result(0, 2), 2);
	EXPECT_EQ(result(1, 0), -7);
	EXPECT_EQ(result(1, 1), 6);
	EXPECT_EQ(result(1, 2), -4);
}

TEST(Task2Tests, InsertsZeroColumnAfterColumnsWithMaximum)
{
	Matrix matrix(2, 3);
	matrix(0, 0) = 5;
	matrix(0, 1) = 2;
	matrix(0, 2) = 5;
	matrix(1, 0) = 1;
	matrix(1, 1) = 5;
	matrix(1, 2) = 3;

	Task2 task(matrix);

	Matrix& result = task.Solve();

	EXPECT_EQ(result.columnsCount(), static_cast<size_t>(6));

	EXPECT_EQ(result(0, 0), 5);
	EXPECT_EQ(result(0, 1), 0);
	EXPECT_EQ(result(0, 2), 2);
	EXPECT_EQ(result(0, 3), 0);
	EXPECT_EQ(result(0, 4), 5);
	EXPECT_EQ(result(0, 5), 0);

	EXPECT_EQ(result(1, 0), 1);
	EXPECT_EQ(result(1, 1), 0);
	EXPECT_EQ(result(1, 2), 5);
	EXPECT_EQ(result(1, 3), 0);
	EXPECT_EQ(result(1, 4), 3);
	EXPECT_EQ(result(1, 5), 0);
}

TEST(Task2Tests, InsertsColumnAfterEveryColumnContainingGlobalMaximum)
{
	Matrix matrix(2, 4);
	matrix(0, 0) = 1;
	matrix(0, 1) = 8;
	matrix(0, 2) = 3;
	matrix(0, 3) = 8;
	matrix(1, 0) = 4;
	matrix(1, 1) = 2;
	matrix(1, 2) = 8;
	matrix(1, 3) = 5;

	Task2 task(matrix);

	Matrix& result = task.Solve();

	EXPECT_EQ(result.columnsCount(), static_cast<size_t>(7));
	EXPECT_EQ(result(0, 0), 1);
	EXPECT_EQ(result(0, 1), 8);
	EXPECT_EQ(result(0, 2), 0);
	EXPECT_EQ(result(0, 3), 3);
	EXPECT_EQ(result(0, 4), 0);
	EXPECT_EQ(result(0, 5), 8);
	EXPECT_EQ(result(0, 6), 0);
}
