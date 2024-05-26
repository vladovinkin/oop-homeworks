#include "stdafx.h"
#include "CController.h"

using namespace std;
using namespace std::placeholders;

CController::CController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		{"line", [this](istream& strm) {
			return Line(strm);
		} },
		{"triangle", [this](istream& strm) {
			return Triangle(strm);
		} },
		{"rectangle", [this](istream& strm) {
			return Rectangle(strm);
		} },
		{"circle", [this](istream& strm) {
			return Circle(strm);
		} },
		})
{
}

bool CController::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

// line x1 y1 x2 y2 border_color
bool CController::Line(std::istream& strm)
{
	double x1, y1, x2, y2;
	uint32_t border_color;

	if (strm >> x1 >> y1 >> x2 >> y2 >> std::hex >> border_color)
	{
		m_shapes.push_back(std::make_shared<CLineSegment>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, border_color));
		return true;
	}
	return false;
}

// triangle x1 y1 x2 y2 x3 y3 border_color fill_color
bool CController::Triangle(std::istream& strm)
{
	double x1, y1, x2, y2, x3, y3;
	uint32_t border_color, fill_color;

	if (strm >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> std::hex >> border_color >> std::hex >> fill_color)
	{
		m_shapes.push_back(std::make_shared<CTriangle>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, CPoint{ x3, y3 }, border_color, fill_color));
		return true;
	}
	return false;
}

// rectangle x1 y1 width height border_color fill_color
bool CController::Rectangle(std::istream& strm)
{
	double x, y, width, height;
	uint32_t border_color, fill_color;

	if (strm >> x >> y >> width >> height >> std::hex >> border_color >> std::hex >> fill_color)
	{
		m_shapes.push_back(std::make_shared<CRectangle>(CPoint{ x, y }, width, height, border_color, fill_color));
		return true;
	}
	return false;
}

// circle x y radius border_color fill_color
bool CController::Circle(std::istream& strm)
{
	double x, y, radius;
	uint32_t border_color, fill_color;

	if (strm >> x >> y >> radius >> std::hex >> border_color >> std::hex >> fill_color)
	{
		m_shapes.push_back(std::make_shared<CCircle>(CPoint{ x, y }, radius, border_color, fill_color));
		return true;
	}
	return false;
}

void CController::PutShapeInfoToOutput(std::shared_ptr<IShape> shape) const
{
	m_output << "Area: " << std::fixed << std::setprecision(2) << shape->GetArea() << '\n';
	m_output << "Perimeter: " << std::fixed << std::setprecision(2) << shape->GetPerimeter() << '\n';
	m_output << "Outline color: #" << std::hex << shape->GetOutlineColor() << '\n';
	m_output << shape->ToString() << '\n';
	m_output << '\n';
}

void CController::PrintResult() const
{
	if (m_shapes.size())
	{
		std::shared_ptr<IShape> shapeWithMaxArea = GetShapeWithMaxArea();
		std::shared_ptr<IShape> shapeWithMinPerimeter = GetShapeWithMinPerimeter();

		m_output << "## Shape with maximum area:\n";
		PutShapeInfoToOutput(shapeWithMaxArea);

		m_output << "## Shape with minimum perimeter:\n";
		PutShapeInfoToOutput(shapeWithMinPerimeter);
	}
	else
	{
		m_output << "Не было введено ни одного объекта\n";
	}
}

std::shared_ptr<IShape> CController::GetShapeWithMaxArea() const
{
	std::shared_ptr<IShape> resultShape;
	double maxArea = -1.0;

	for (const auto& shape : m_shapes)
	{
		double shapeArea = shape->GetArea();
		if (maxArea < 0.0 || shapeArea > maxArea)
		{
			resultShape = shape;
			maxArea = shapeArea;
		}
	}

	return resultShape;
}

std::shared_ptr<IShape> CController::GetShapeWithMinPerimeter() const
{
	std::shared_ptr<IShape> resultShape;
	double minPerimeter = -1.0;

	for (const auto& shape : m_shapes)
	{
		double shapePerimeter = shape->GetPerimeter();
		if (minPerimeter < 0.0 || shapePerimeter < minPerimeter)
		{
			resultShape = shape;
			minPerimeter = shapePerimeter;
		}
	}

	return resultShape;
}
