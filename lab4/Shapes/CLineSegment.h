#pragma once

#include "CShape.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(const CPoint& point_start, const CPoint& point_end, uint32_t outline_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
	CPoint m_point_start, m_point_end;
};
