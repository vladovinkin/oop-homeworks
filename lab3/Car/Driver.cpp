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

bool CDriver::EngineOn(std::istream& /*args*/)
{
	if (m_car.IsTurnedOn())
	{
		m_output << "Engine is \x1b[93malready turned on\x1b[0m\n";
		return true;
	}
	else
	{
		if (m_car.TurnOnEngine())
		{
			m_output << "Engine is \x1b[93mturned on\x1b[0m\n";
			return true;
		}
	}
	m_output << "\x1b[91mUnable to turn on the engine\x1b[0m\n";
	return false;
}

bool CDriver::EngineOff(std::istream&)
{
	if (!m_car.IsTurnedOn())
	{
		m_output << "Engine is \x1b[93malready turned off\x1b[0m\n";
		return true;
	}
	else
	{
		if (m_car.TurnOffEngine())
		{
			m_output << "Engine is \x1b[93mturned off\x1b[0m\n";
			return true;
		}
	}
	m_output << "\x1b[91mUnable to turn off the engine\x1b[0m\n";
	return false;
}

bool CDriver::SetGear(std::istream &strm)
{
	int arg;

	strm >> arg;

	if (m_car.SetGear(arg))
	{ // сделать код более читаемым
		m_output << "Gear set to \x1b[93m" << to_string(arg) << "\x1b[0m\n";
		return true;
	}
	else
	{
		m_output << "\x1b[91mUnable to set gear " << to_string(arg) << "\x1b[0m\n";
	}
	return false;
}

bool CDriver::SetSpeed(std::istream& strm)
{
	int arg;

	strm >> arg;

	if (m_car.SetSpeed(arg))
	{
		m_output << "Now speed is \x1b[93m" << to_string(arg) << "\x1b[0m\n";
		return true;
	}
	else
	{
		m_output << "\x1b[91mUnable to set speed to " << to_string(arg) << "\x1b[0m\n";
	}
	return false;
}

bool CDriver::Info(std::istream& /*args*/)
{
	Direction dir = m_car.GetDirection();

	m_output << (m_car.IsTurnedOn()
		? "Engine is \x1b[92mturned on\x1b[0m\n"
		: "Engine is \x1b[91mturned off\x1b[0m\n")
	+ "Current gear: \x1b[93m"s
	+ to_string(m_car.GetGear()) + "\x1b[0m\n"
	+ "Current speed: \x1b[92m"s
	+ to_string(m_car.GetSpeed()) + "\x1b[0m\n"
	+ "Direction: \x1b[96m"
	+ (dir == Direction::FORWARD
		? "forward"
		: (dir == Direction::BACKWARD
			? "backward"
			: "stay still"))
	+ "\x1b[0m\n";

	return true;
}

