#pragma once
#include <vector>
#include <iterator>

template < typename T >
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	T tempMax;
	if (arr.size())
	{
		for (auto elem{ arr.begin() }; elem != arr.end(); elem++)
		{
			tempMax = (elem == arr.begin() || *elem > tempMax) ? *elem : tempMax;
		}
		maxValue = tempMax;
		return true;
	}
	return false;
}

template <>
bool FindMax<const char*>(std::vector<const char*> const& arr, const char*& maxValue)
{
	const char* tempMax = "";
	if (arr.size())
	{
		for (auto elem{ arr.begin() }; elem != arr.end(); elem++)
		{
			tempMax = (elem == arr.begin() || strcmp(*elem, tempMax) != -1) ? *elem : tempMax;
		}
		maxValue = tempMax;
		return true;
	}
	return false;
}
