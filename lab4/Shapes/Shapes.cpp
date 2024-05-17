#include "stdafx.h"
#include "Shapes.h"

IShape::IShape(uint32_t outline_color)
	: m_outline_color(outline_color)
{}

double IShape::GetArea() const
{
	return 0.0;
}

double IShape::GetPerimeter() const
{
	return 0.0;
}

uint32_t IShape::GetOutlineColor() const
{
	return m_outline_color;
}


ISolidShape::ISolidShape(uint32_t outline_color, uint32_t fill_color)
	: IShape(outline_color)
	, m_fill_color(fill_color)
{ }

uint32_t ISolidShape::GetFillColor() const
{
	return m_fill_color;
}

std::string IShape::ToString() const
{
	return "Solid shape";
}

CLineSegment::CLineSegment(const CPoint& point_start, const CPoint& point_end, uint32_t outline_color)
	: IShape(outline_color)
	, m_point_start(point_start)
	, m_point_end(point_end)
{}

double CLineSegment::GetArea() const
{
	return IShape::GetArea();
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
	return IShape::GetOutlineColor();
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_point_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_point_end;
}

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, uint32_t outline_color, uint32_t fill_color)
	: ISolidShape(outline_color, fill_color)
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
	return IShape::GetOutlineColor();
}

uint32_t CTriangle::GetFillColor() const
{
	return ISolidShape::GetFillColor();
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

CRectangle::CRectangle(const CPoint&, double width, double height, uint32_t outline_color, uint32_t fill_color)
	: ISolidShape(outline_color, fill_color)
	, m_width(width)
	, m_height(height)
{}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2.0;
}

std::string CRectangle::ToString() const
{
	return "Rectangle shape";
}

uint32_t CRectangle::GetOutlineColor() const
{
	return IShape::GetOutlineColor();
}

uint32_t CRectangle::GetFillColor() const
{
	return ISolidShape::GetFillColor();
}

CPoint CRectangle::GetLeftTop() const
{
	return m_left_top;
}

CPoint CRectangle::GetRightBottom() const
{
	return
	{
		m_left_top.x + m_width,
		m_left_top.y + m_height
	};
}

double CRectangle::GetWidth() const
{
	return m_width;
}


double CRectangle::GetHeight() const
{
	return m_height;
}

CCircle::CCircle(const CPoint& center, double radius, uint32_t outline_color, uint32_t fill_color)
	: ISolidShape(outline_color, fill_color)
	, m_center(center)
	, m_radius(radius)
{}

double CCircle::GetArea() const
{
	return std::numbers::pi * std::pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2.0 * std::numbers::pi * m_radius;
}

std::string CCircle::ToString() const
{
	return "Circle shape";
}

uint32_t CCircle::GetOutlineColor() const
{
	return IShape::GetOutlineColor();
}

uint32_t CCircle::GetFillColor() const
{
	return ISolidShape::GetFillColor();
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
