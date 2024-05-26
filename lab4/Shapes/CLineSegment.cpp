#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& point_start, const CPoint& point_end, uint32_t outline_color)
	: CShape(outline_color)
	, m_point_start(point_start)
	, m_point_end(point_end)
{}

double CLineSegment::GetArea() const
{
	return CShape::GetArea();
}

double CLineSegment::GetPerimeter() const
{
	return std::sqrt(std::pow(m_point_end.x - m_point_start.x, 2.0) + std::pow(m_point_end.y - m_point_start.y, 2.0));
}

std::string CLineSegment::ToString() const
{
	return "Line segment";
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_point_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_point_end;
}
