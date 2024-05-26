#pragma once

#include "stdafx.h"

struct CPoint
{
	double x, y;
};

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
	virtual ~IShape() = default;
};
