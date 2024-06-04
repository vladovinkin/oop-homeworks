#pragma once

#include "ISolidShape.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape(uint32_t outline_color, uint32_t fill_color);
	// не нужно делать реализацию для того, чтобы было
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
private:
	uint32_t m_outline_color, m_fill_color;
};
