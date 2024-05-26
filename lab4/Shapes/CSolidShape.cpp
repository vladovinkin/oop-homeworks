#include "CSolidShape.h"

CSolidShape::CSolidShape(uint32_t outline_color, uint32_t fill_color)
	: m_outline_color(outline_color)
	, m_fill_color(fill_color)
{}

double CSolidShape::GetArea() const
{
	return 0;
}

double CSolidShape::GetPerimeter() const
{
	return 0;
}

std::string CSolidShape::ToString() const
{
	return "Solid shape";
}

uint32_t CSolidShape::GetOutlineColor() const
{
	return m_outline_color;
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fill_color;
}
