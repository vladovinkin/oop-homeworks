#pragma once
#include <istream>
#include <ostream>
#include <vector>
#include <functional>
#include <map>
#include "Shapes.h"

class CStorage
{
public:
	CStorage(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintShapes() const;
private:
	bool Line(std::istream& args);
	bool Triangle(std::istream& args);
	bool Rectangle(std::istream& args);
	bool Circle(std::istream& args);
private:
	// функция-обработчик команды пользователя.
	// Возвращает true, если команда распознана и false, если были ошибки
	using Handler = std::function<bool(std::istream& args)>;

	// Отображает название команды на её обработчик
	using ActionMap = std::map<std::string, Handler>;

	std::vector<std::unique_ptr<IShape>> m_shapes;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};