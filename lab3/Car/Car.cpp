#include "stdafx.h"
#include "car.h"

CCar::CCar()
{
	m_engineIsRunning = false;
	m_gear = 0;
	m_speed = 0;
}

bool CCar::TurnOnEngine()
{
	if (m_speed == 0 && m_gear == GearNeutral)
	{
		m_engineIsRunning = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_speed == 0 && m_gear == GearNeutral)
	{
		m_engineIsRunning = false;
		return true;
	}
	return false;
}

// убедиться, что все значимые аспекты покрыты тестами
bool CCar::SetGear(int gear)
{	// (+) сделать таблицу скоростей
	if (gear == m_gear)
	{
		return true;
	}

	if (gear == GearNeutral)
	{
		m_gear = gear;
		return true;
	}

	if (IsTurnedOn())
	{
		if (gear == GearReverse)
		{
			if (m_speed == 0)
			{
				m_gear = gear;
			}
			return m_speed == 0;
		}

		if (gear >= GearDrive1 && gear <= GearDrive5)
		{
			if (m_speed < GearSpeedLimit[gear][0] || m_speed > GearSpeedLimit[gear][1])
			{
				return false;
			}
			else
			{
				m_gear = gear;
				return true;
			}
		}
	}
	else
	{
		return gear == GearNeutral;
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!IsTurnedOn() && speed == 0)
	{
		return true;
	}
	if (speed >= SpeedMin && speed <= SpeedMax && IsTurnedOn())
	{
		if (m_gear == GearNeutral && speed > abs(m_speed) || m_gear == GearReverse && (speed < 0 || speed > 20))
		{
			return false;
		}

		if (m_gear >= GearDrive1 && m_gear <= GearDrive5 && (speed < GearSpeedLimit[m_gear][0] || speed > GearSpeedLimit[m_gear][1]))
		{
			return false;
		}
			
		m_speed = (m_gear == GearReverse || m_speed < 0)
			? -speed
			: speed;

		return true;
	}
	return false;
}

bool CCar::IsTurnedOn() const
{
	return m_engineIsRunning;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return std::abs(m_speed);
}

Direction CCar::GetDirection() const
{
	return m_speed < 0
		? Direction::BACKWARD
		: (m_speed > 0
			? Direction::FORWARD
			: Direction::STAY_STILL);
}
