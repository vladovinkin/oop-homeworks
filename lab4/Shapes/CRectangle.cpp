#include "CRectangle.h"

CRectangle::CRectangle(const CPoint&, double width, double height, uint32_t outline_color, uint32_t fill_color)
	: CSolidShape(outline_color, fill_color)
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
	return CSolidShape::GetOutlineColor();
}

uint32_t CRectangle::GetFillColor() const
{
	return CSolidShape::GetFillColor();
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
