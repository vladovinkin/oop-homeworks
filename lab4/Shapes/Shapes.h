#pragma once

#include <string>

struct CPoint
{
	double x, y;
};

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
	virtual ~IShape() = default;
	// (+) в интерфейсах не должно быть данных и реализации методов
};

class CShape : public IShape
{
public:
	CShape(uint32_t outline_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
private:
	uint32_t m_outline_color;
};

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

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};

class CSolidShape : public ISolidShape
{
public:
	CSolidShape(uint32_t outline_color, uint32_t fill_color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
private:
	uint32_t m_outline_color, m_fill_color;
};

class CTriangle : public CSolidShape
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

class CRectangle : public CSolidShape
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

class CCircle : public CSolidShape
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
