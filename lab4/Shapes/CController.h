#pragma once
#include <istream>
#include <ostream>
#include <vector>
#include <functional>
#include <map>
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

class CController
{
public:
	CController(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintResult() const;
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

	std::shared_ptr<IShape> GetShapeWithMaxArea() const;
	std::shared_ptr<IShape> GetShapeWithMinPerimeter() const;

	void PutShapeInfoToOutput(std::shared_ptr<IShape> shape) const;

	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
