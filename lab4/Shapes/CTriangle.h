#pragma once

#include "CSolidShape.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(const CPoint&, const CPoint&, const CPoint&, uint32_t outline_color, uint32_t fill_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
};
