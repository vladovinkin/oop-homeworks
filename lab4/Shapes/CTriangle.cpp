#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, uint32_t outline_color, uint32_t fill_color)
	: CSolidShape(outline_color, fill_color)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{}

double CTriangle::GetArea() const
{
	double perimeter1 = std::sqrt(std::pow(m_vertex1.x - m_vertex2.x, 2.0) + std::pow(m_vertex1.y - m_vertex2.y, 2.0));
	double perimeter2 = std::sqrt(std::pow(m_vertex2.x - m_vertex3.x, 2.0) + std::pow(m_vertex2.y - m_vertex3.y, 2.0));
	double perimeter3 = std::sqrt(std::pow(m_vertex3.x - m_vertex1.x, 2.0) + std::pow(m_vertex3.y - m_vertex1.y, 2.0));

	double perimeterHalf = 0.5 * (perimeter1 + perimeter2 + perimeter3);

	return std::sqrt(perimeterHalf * (perimeterHalf - perimeter1) * (perimeterHalf - perimeter2) * (perimeterHalf - perimeter3));
}

double CTriangle::GetPerimeter() const
{
	return std::sqrt(std::pow(m_vertex1.x - m_vertex2.x, 2.0) + std::pow(m_vertex1.y - m_vertex2.y, 2.0))
		+ std::sqrt(std::pow(m_vertex2.x - m_vertex3.x, 2.0) + std::pow(m_vertex2.y - m_vertex3.y, 2.0))
		+ std::sqrt(std::pow(m_vertex3.x - m_vertex1.x, 2.0) + std::pow(m_vertex3.y - m_vertex1.y, 2.0));
}

std::string CTriangle::ToString() const
{
	return "Triangle shape";
}

uint32_t CTriangle::GetOutlineColor() const
{
	return CSolidShape::GetOutlineColor();
}

uint32_t CTriangle::GetFillColor() const
{
	return CSolidShape::GetFillColor();
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
