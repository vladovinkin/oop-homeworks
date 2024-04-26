#pragma once
#include <istream>
#include <ostream>

class CCar;
// �� �������� ������� ��������� �� ������
class CDriver
{
public:
	CDriver(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

	// ����������� �� �������������� ����������� � ���, ��� �� �� ������ ������������� �������� ������������
	 //CDriver& operator=(const CDriver &) = delete;
private: // ������� ������ ������������
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool Info(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);
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

