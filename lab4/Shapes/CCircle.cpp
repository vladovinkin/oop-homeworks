#include "CCircle.h"

CCircle::CCircle(const CPoint& center, double radius, uint32_t outline_color, uint32_t fill_color)
	: CSolidShape(outline_color, fill_color)
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
	std::stringstream stream;
	CPoint center = GetCenter();

	stream << "Shape type: circle\n" 
		<< "Center point: x = " << std::fixed << std::setprecision(2) << center.x 
		<< "; y = " << std::fixed << std::setprecision(2) << center.y << '\n'
		<< "Radius: " << std::fixed << std::setprecision(2) << GetRadius() << '\n'
		<< "Fill color: #" << std::hex << GetFillColor();

	return stream.str();
}

uint32_t CCircle::GetOutlineColor() const
{
	return CSolidShape::GetOutlineColor();
}

uint32_t CCircle::GetFillColor() const
{
	return CSolidShape::GetFillColor();
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
