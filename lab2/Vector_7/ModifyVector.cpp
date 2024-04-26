#include "ModifyVector.h"

void ModifyVector(std::vector<double>& numbers)
{
	VectorProcessing(numbers);
	// sort вынести в вывод
	std::sort(numbers.begin(), numbers.end());
}

// (+) в именах функций легко запутаться
void VectorProcessing(std::vector<double>& numbers)
{
	double positiveItemsSum = PositiveItemsSum(numbers);
	ChangeVectorItems(numbers, positiveItemsSum);
}

double PositiveItemsSum(const std::vector<double>& numbers)
{
	// (+) дать другое имя
	auto AddIfPositive = [](double sum, double item)
	{
		return item > 0.0 ? sum + item : sum;
	};

	return std::accumulate(numbers.begin(), numbers.end(), 0.0, AddIfPositive);
}

void ChangeVectorItems(std::vector<double>& numbers, double addendum)
{
	// (+) цикл заменить на transform
	std::vector<size_t> indices;
	std::vector<double> result;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		indices.push_back(i);
	}

	std::transform(
		indices.begin(),
		indices.end(),
		std::back_inserter(result),
		[&](size_t i) -> double {
			return i % 2 == 0
				? numbers[i] * 2.0
				: numbers[i] - addendum;
		});

	numbers = result;
}

void PrintVector(const std::vector<double>& numbers)
{
	copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout << std::setprecision(3) << std::fixed, " "));
}
