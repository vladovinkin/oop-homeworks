#include "stdafx.h"
#include "Storage.h"
#include "Shapes.h"

using namespace std;
using namespace std::placeholders;

CStorage::CStorage(std::istream& input, std::ostream& output)
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

bool CStorage::HandleCommand()
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
bool CStorage::Line(std::istream& strm)
{
	double x1, y1, x2, y2;
	uint32_t border_color;

	if (strm >> x1 >> y1 >> x2 >> y2 >> border_color)
	{
		m_shapes.push_back(std::make_unique<CLineSegment>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, border_color));
		return true;
	}
	return false;
}

// triangle x1 y1 x2 y2 x3 y3 border_color fill_color
bool CStorage::Triangle(std::istream& strm)
{
	double x1, y1, x2, y2, x3, y3;
	uint32_t border_color, fill_color;

	if (strm >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> border_color >> fill_color)
	{
		m_shapes.push_back(std::make_unique<CTriangle>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, CPoint{ x3, y3 }, border_color, fill_color));
		return true;
	}
	return false;
}

// rectangle x1 y1 width height border_color fill_color
bool CStorage::Rectangle(std::istream& strm)
{
	double x, y, width, height;
	uint32_t border_color, fill_color;

	if (strm >> x >> y >> width >> height >> border_color >> fill_color)
	{
		m_shapes.push_back(std::make_unique<CRectangle>(CPoint{ x, y }, width, height, border_color, fill_color));
		return true;
	}
	return false;
}

// circle x y radius border_color fill_color
bool CStorage::Circle(std::istream& strm)
{
	double x, y, radius;
	uint32_t border_color, fill_color;

	if (strm >> x >> y >> radius >> border_color >> fill_color)
	{
		m_shapes.push_back(std::make_unique<CCircle>(CPoint{ x, y }, radius, border_color, fill_color));
		return true;
	}
	return false;
}

void CStorage::PrintShapes() const
{
	for (const auto& shape : m_shapes)
	{
		m_output << shape->ToString() << '\n';
	}
}
