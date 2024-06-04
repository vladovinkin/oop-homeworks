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
		{"exit", [this](istream& strm) {
			return Exit(strm);
		} },
		})
{
}

int CController::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	if (action.length())
	{
		auto it = m_actionMap.find(action);
		if (it != m_actionMap.end())
		{
			return it->second(strm);
		}
		return ResponseUnknownCommand;
	}

	return ResponseEnd;
}

// line x1 y1 x2 y2 border_color
int CController::Line(std::istream& strm)
{
	double x1, y1, x2, y2;
	uint32_t border_color;

	if (strm >> x1 >> y1 >> x2 >> y2 >> std::hex >> border_color)
	{
		std::shared_ptr<IShape> line = std::make_shared<CLineSegment>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, border_color);
		store.AddShape(line);
		return ResponseOk;
	}
	return ResponseInvalidArguments;
}

// triangle x1 y1 x2 y2 x3 y3 border_color fill_color
int CController::Triangle(std::istream& strm)
{
	double x1, y1, x2, y2, x3, y3;
	uint32_t border_color, fill_color;

	if (strm >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> std::hex >> border_color >> std::hex >> fill_color)
	{
		std::shared_ptr<IShape> triangle = std::make_shared<CTriangle>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, CPoint{ x3, y3 }, border_color, fill_color);
		store.AddShape(triangle);
		return ResponseOk;
	}
	return ResponseInvalidArguments;
}

// rectangle x1 y1 width height border_color fill_color
int CController::Rectangle(std::istream& strm)
{
	double x, y, width, height;
	uint32_t border_color, fill_color;

	if (strm >> x >> y >> width >> height >> std::hex >> border_color >> std::hex >> fill_color)
	{
		std::shared_ptr<IShape> rect = std::make_shared<CRectangle>(CPoint{ x, y }, width, height, border_color, fill_color);
		store.AddShape(rect);
		return ResponseOk;
	}
	return ResponseInvalidArguments;
}

// circle x y radius border_color fill_color
int CController::Circle(std::istream& strm)
{
	double x, y, radius;
	uint32_t border_color, fill_color;

	if (strm >> x >> y >> radius >> std::hex >> border_color >> std::hex >> fill_color)
	{
		std::shared_ptr<IShape> circle = std::make_shared<CCircle>(CPoint{ x, y }, radius, border_color, fill_color);
		store.AddShape(circle);
		return ResponseOk;
	}
	return ResponseInvalidArguments;
}

int CController::Exit(std::istream& strm)
{
	m_output << '\n';
	return ResponseEnd;
}

void CController::PutShapeInfoToOutput(std::shared_ptr<IShape> shape) const
{
	// посмотреть как сделан пример с объёмными телами (в папке labs)
	m_output << "Area: " << std::fixed << std::setprecision(2) << shape->GetArea() << '\n';
	m_output << "Perimeter: " << std::fixed << std::setprecision(2) << shape->GetPerimeter() << '\n';
	m_output << "Outline color: #" << std::hex << shape->GetOutlineColor() << '\n';
	m_output << shape->ToString() << '\n';
	m_output << '\n';
}

void CController::PrintResult() const
{
	if (store.GetSize())
	{
		std::shared_ptr<IShape> shapeWithMaxArea = store.GetShapeWithMaxArea();
		std::shared_ptr<IShape> shapeWithMinPerimeter = store.GetShapeWithMinPerimeter();

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
