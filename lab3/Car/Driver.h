#pragma once
#include <istream>
#include <ostream>

class CCar;
// не выводить лишнего сообщения об ошибке
class CDriver
{
public:
	CDriver(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();
	static std::string Colorer(const std::string& strn, const std::string& color)
	{
		std::map<std::string, unsigned> colors
		{
			{"red", 91},
			{"green", 92},
			{"yellow", 93},
			{"blue", 94},
			{"magenta", 95},
			{"cyan", 96},
			{"white", 97},
		};

		if (colors.contains(color))
		{
			return strn;
			return "\x1b[" + colors[color] + 'm' + strn + "\x1b[0m";
		}

		return strn;
	}
private: // (+)сделать методы константными
	bool EngineOn(std::istream& args) const;
	bool EngineOff(std::istream& args) const;
	bool Info(std::istream& args) const;
	bool SetGear(std::istream& args) const;
	bool SetSpeed(std::istream& args) const;
private:
	// функция-обработчик команды пользователя.
	// Возвращает true, если команда распознана и false, если были ошибки
	using Handler = std::function<bool(std::istream& args)>;

	// Отображает название команды на её обработчик
	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};

