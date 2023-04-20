#include "Utils.h"

#include <random>

int Utils::randomNumber()
{
	int number{ 0 };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 2);

	number = distrib(gen);

	return number;
}
