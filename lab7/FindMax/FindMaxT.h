#pragma once
#include <vector>
#include <iterator>

template < typename T >
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (!arr.empty())
	{
		auto tempMax = arr.begin();
		for (auto elem{ ++arr.begin() }; elem != arr.end(); elem++)
		{
			tempMax = *elem > *tempMax ? elem : tempMax;
		}
		maxValue = *tempMax;
		return true;
	}
	return false;
}

template <>
bool FindMax<const char*>(std::vector<const char*> const& arr, const char*& maxValue)
{
	const char* tempMax = "";
	if (!arr.empty())
	{
		auto tempMax = arr.begin();
		for (auto elem{ ++arr.begin() }; elem != arr.end(); elem++)
		{
			tempMax = strcmp(*elem, *tempMax) != -1 ? elem : tempMax;
		}
		maxValue = *tempMax;
		return true;
	}
	return false;
}
