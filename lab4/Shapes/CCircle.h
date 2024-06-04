#pragma once

#include "CSolidShape.h"
// разобраться в публичном наследовании
class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint& center, double radius, uint32_t outline_color, uint32_t fill_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
private:
	CPoint m_center;
	double m_radius;
};
