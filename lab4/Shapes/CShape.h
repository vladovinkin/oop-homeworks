#pragma once

#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(uint32_t outline_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
private:
	uint32_t m_outline_color;
};
