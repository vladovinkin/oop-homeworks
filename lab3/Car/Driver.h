#pragma once
#include <istream>
#include <ostream>

constexpr int Red = 91;
constexpr int Green = 92;
constexpr int Yellow = 93;
constexpr int Blue = 94;
constexpr int Magenta = 95;
constexpr int Cyan = 96;
constexpr int White = 97;

class CCar;
// (+) �� �������� ������� ��������� �� ������
class CDriver
{
public:
	CDriver(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();
	static std::string Colorer(const std::string& strn, int color)
	{
		return "\x1b[" + std::to_string(color) + 'm' + strn + "\x1b[0m";
	}
private: // (+)������� ������ ������������
	bool EngineOn(std::istream& args) const;
	bool EngineOff(std::istream& args) const;
	bool Info(std::istream& args) const;
	bool SetGear(std::istream& args) const;
	bool SetSpeed(std::istream& args) const;
private:
	// �������-���������� ������� ������������.
	// ���������� true, ���� ������� ���������� � false, ���� ���� ������
	using Handler = std::function<bool(std::istream& args)>;

	// ���������� �������� ������� �� � ����������
	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};

