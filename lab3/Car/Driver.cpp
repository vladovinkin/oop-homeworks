#include "stdafx.h"
#include "Driver.h"
#include "Car.h"

using namespace std;
using namespace std::placeholders;

CDriver::CDriver(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "EngineOn", [this](istream& strm) {
			   return EngineOn(strm);
		   } },
		  { "EngineOff", bind(&CDriver::EngineOff, this, std::placeholders::_1) },
		  { "Info", bind(&CDriver::Info, this, _1) },
		  { "SetGear", bind(&CDriver::SetGear, this, _1) },
		  { "SetSpeed", bind(&CDriver::SetSpeed, this, _1) },
		})
{
}

bool CDriver::HandleCommand()
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

bool CDriver::EngineOn(std::istream&) const
{
	if (m_car.IsTurnedOn())
	{
		m_output << "Engine is" << CDriver::Colorer("already turned on", "yellow") << '\n';
		return true;
	}
	else
	{
		if (m_car.TurnOnEngine())
		{
			m_output << "Engine is" << CDriver::Colorer("turned on", "yellow") << '\n';
			return true;
		}
	}
	m_output << CDriver::Colorer("Unable to turn on the engine", "red") << '\n';
	return false;
}

bool CDriver::EngineOff(std::istream&) const
{
	if (!m_car.IsTurnedOn())
	{
		m_output << "Engine is" << CDriver::Colorer("already turned off", "yellow") << '\n';
		return true;
	}
	else
	{
		if (m_car.TurnOffEngine())
		{
			m_output << "Engine is" << CDriver::Colorer("turned off", "yellow") << '\n';
			return true;
		}
	}
	m_output << CDriver::Colorer("Unable to turn off the engine", "red") << '\n';
	return false;
}

bool CDriver::SetGear(std::istream &strm) const
{
	int arg;

	strm >> arg;

	if (m_car.SetGear(arg))
	{ // (+) сделать код более читаемым
		m_output << "Gear set to" << CDriver::Colorer(to_string(arg), "yellow") << '\n';
		return true;
	}
	else
	{
		m_output << CDriver::Colorer("Unable to set gear " + to_string(arg), "red") << '\n';
	}
	return false;
}

bool CDriver::SetSpeed(std::istream& strm) const
{
	int arg;

	strm >> arg;

	if (m_car.SetSpeed(arg))
	{
		m_output << "Now speed is" << CDriver::Colorer(to_string(arg), "yellow") << '\n';
		return true;
	}
	else
	{
		m_output << CDriver::Colorer("Unable to set speed to " + to_string(arg), "red") << '\n';
	}
	return false;
}

bool CDriver::Info(std::istream&) const
{
	Direction dir = m_car.GetDirection();

	m_output << (m_car.IsTurnedOn()
		? "Engine is " + CDriver::Colorer("turned on", "green")
		: "Engine is " + CDriver::Colorer("turned off", "red")) + "\n"
	+ "Current gear: " + CDriver::Colorer(to_string(m_car.GetGear()), "yellow") + "\n"
	+ "Current speed: " + CDriver::Colorer(to_string(m_car.GetSpeed()), "green") + "\n"
	+ "Direction: " + CDriver::Colorer((dir == Direction::FORWARD
		? "forward"
		: (dir == Direction::BACKWARD
			? "backward"
			: "stay still")), "cyan")
	+ "\n";

	return true;
}
