#include "ModifyVector.h"

auto StringToVector(const std::string& line)
{
	std::vector<double> numbers;

	if (!line.empty())
	{
		std::istringstream lineStream(line);
		double item;

		while (!lineStream.eof())
		{
			if (!(lineStream >> item)) {
				throw std::runtime_error("Incorrect data type for matrix element in input file");
			}

			if (lineStream.bad())
			{
				throw std::runtime_error("Failed to read data from input line");
			}

			numbers.push_back(item);
		}
	}

	return numbers;
}

double PositiveItemsSum(const std::vector<double>& numbers)
{
	auto NonNegativeValue = [](double sum, double item)
	{
		return item > 0.0 ? sum + item : sum;
	};

	return std::accumulate(numbers.begin(), numbers.end(), 0.0, NonNegativeValue);
}

void VectorModifyFunction(std::vector<double>& numbers, double addendum)
{
	bool isEvenItem = true;
	for (auto& item : numbers)
	{
		item = isEvenItem
			? item * 2.0
			: item - addendum;
		isEvenItem = !isEvenItem;
	}
}

void VectorModify(std::vector<double>& numbers)
{
	double positiveItemsSum = PositiveItemsSum(numbers);
	VectorModifyFunction(numbers, positiveItemsSum);
}

auto VectorToString(const std::vector<double>& numbers)
{
	std::stringstream result;

	if (!numbers.empty()) {
		for (auto i = 0; i < numbers.size(); i++)
		{
			result << std::setprecision(3) << std::fixed 
				<< numbers[i] << (i < numbers.size() - 1 ? " " : "");
		}
	}

	return result.str();
}

std::string ModifyVector(const std::string& line)
{
	std::vector<double> numbers = StringToVector(line);
	VectorModify(numbers);
	std::sort(numbers.begin(), numbers.end());
	return VectorToString(numbers);
}