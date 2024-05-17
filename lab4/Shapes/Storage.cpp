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
			   return Line(strm);
		} },
		{"rectangle", [this](istream& strm) {
			   return Line(strm);
		} },
		{"circle", [this](istream& strm) {
			   return Line(strm);
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
bool CStorage::Line(std::istream&) const
{
	// разобрать аргументы
	// создать объект
	// добавить объект в вектор
	return 0;
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
