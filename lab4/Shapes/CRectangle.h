#pragma once

#include "CSolidShape.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint&, double width, double height, uint32_t outline_color, uint32_t fill_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
private:
	CPoint m_left_top;
	double m_width, m_height;
};
