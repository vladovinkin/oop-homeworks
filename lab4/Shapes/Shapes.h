#pragma once

#include <string>

struct CPoint
{
	double x, y;
};

class IShape
{
public:
	IShape(uint32_t outline_color);
	virtual double GetArea() const;
	virtual double GetPerimeter() const;
	virtual std::string ToString() const;
	virtual uint32_t GetOutlineColor() const;
private:
	uint32_t m_outline_color;
};

class ISolidShape : public IShape
{
public:
	ISolidShape(uint32_t outline_color, uint32_t fill_color);
	virtual uint32_t GetFillColor() const;
private:
	uint32_t m_fill_color;
};

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint &, const CPoint &, uint32_t outline_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
	CPoint m_point_start, m_point_end;
};

class CTriangle : public ISolidShape
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

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint&, double width, double height, uint32_t outline_color, uint32_t fill_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
private:
	CPoint m_left_top;
	double m_width, m_height;
};

class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint& center, double radius, uint32_t outline_color, uint32_t fill_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
private:
	CPoint m_center;
	double m_radius;
};
