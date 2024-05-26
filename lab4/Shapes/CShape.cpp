#include "CShape.h"

CShape::CShape(uint32_t outline_color)
	: m_outline_color(outline_color)
{}

double CShape::GetArea() const
{
	return 0;
}

double CShape::GetPerimeter() const
{
	return 0;
}

std::string CShape::ToString() const
{
	return "Shape";
}

uint32_t CShape::GetOutlineColor() const
{
	return m_outline_color;
}
