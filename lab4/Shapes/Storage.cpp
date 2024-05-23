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
	// разобрать аргументы
	double x1, y1, x2, y2;
	uint32_t border_color;

	if (strm >> x1 >> y1 >> x2 >> y2 >> border_color)
	{
		// создать объект
		CLineSegment line({ x1, y1 }, { x2, y2 }, border_color);

		// добавить объект в вектор
		//m_shapes.push_back(std::make_unique<CLineSegment>(line));
		//m_shapes.push_back(new CLineSegment({ x1, y1 }, { x2, y2 }, border_color));
		 
		m_shapes.push_back(std::make_unique<CLineSegment>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, border_color));

		//auto line = std::make_unique<CLineSegment>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, border_color);
		//m_shapes.push_back(std::move(line));

		return true;
	}

	return false;
}

// triangle x1 y1 x2 y2 x3 y3 border_color fill_color
bool CStorage::Triangle(std::istream&) const
{
	return 0;
}

// rectangle x1 y1 width height border_color fill_color
bool CStorage::Rectangle(std::istream&) const
{
	return 0;
}

// circle x y radius border_color fill_color
bool CStorage::Circle(std::istream&) const
{
	return 0;
}
