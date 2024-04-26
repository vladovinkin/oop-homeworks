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

bool CCar::SetGear(int gear)
{	// сделать таблицу скоростей 
	if (gear >= GearReverse && gear <= GearDrive5)
	{
		if (gear == m_gear)
		{
			return true;
		}
		else
		{
			if (IsTurnedOn())
			{
				switch (gear)
				{
				case GearReverse:
					if (m_speed != 0)
					{
						return false;
					}
					break;
				case GearDrive1:
					if (m_speed < 0 || m_speed > 30)
					{
						return false;
					}
					break;
				case GearDrive2:
					if (m_speed < 20 || m_speed > 50)
					{
						return false;
					}
					break;
				case GearDrive3:
					if (m_speed < 30 || m_speed > 60)
					{
						return false;
					}
					break;
				case GearDrive4:
					// убедться что все значимые аспекты покрыты тестами
					if (m_speed < 40 || m_speed > 90)
					{
						return false;
					}
					break;
				case GearDrive5:
					if (m_speed < 50 || m_speed > 150)
					{
						return false;
					}
					break;
				}
				m_gear = gear;
				return true;
			}
			else
			{
				return gear == GearNeutral;
			}
		}
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (speed >= SpeedMin && speed <= SpeedMax)
	{
		if (IsTurnedOn())
		{
			switch (m_gear)
			{
			case GearReverse:
				if (speed < 0 || speed > 20)
				{
					return false;
				}
				break;
			case GearDrive1:
				if (speed < 0 || speed > 30)
				{
					return false;
				}
				break;
			case GearDrive2:
				if (speed < 20 || speed > 50)
				{
					return false;
				}
				break;
			case GearDrive3:
				if (speed < 30 || speed > 60)
				{
					return false;
				}
				break;
			case GearDrive4:
				if (speed < 40 || speed > 90)
				{
					return false;
				}
				break;
			case GearDrive5:
				if (speed < 50 || speed > 150)
				{
					return false;
				}
				break;
			case GearNeutral:
				if (speed > abs(m_speed))
				{
					return false;
				}
			}
			m_speed = (m_gear == GearReverse || m_speed < 0)
				? -speed
				: speed;

			return true;
		}
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
