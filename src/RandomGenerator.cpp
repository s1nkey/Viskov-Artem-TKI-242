#include "../include/RandomGenerator.h"
#include <stdexcept>

namespace miit::algebra
{
	RandomGenerator::RandomGenerator(const int min, const int max)
		: generator(std::random_device{}())
	{
		if (min > max)
		{
			throw std::invalid_argument("Неверный диапазон");
		}

		distribution = std::uniform_int_distribution<int>(min, max);
	}

	int RandomGenerator::generate() const
	{
		return distribution(generator);
	}
}
