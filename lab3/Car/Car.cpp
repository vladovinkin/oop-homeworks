﻿#include "stdafx.h"
#include "car.h"

const std::vector<GearSpeedRange> CCar::s_speedTable = {
	{ GearNeutral, 0, 150 },
	{ GearDrive1, 0, 30 },
	{ GearDrive2, 20, 50 },
	{ GearDrive3, 30, 60 },
	{ GearDrive4, 40, 90 },
	{ GearDrive5, 50, 150 },
	{ GearReverse, 0, 20 },
};

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
			if (!IsSpeedValidForGear(m_speed, gear))
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
	{// добавить функции для условий
		if (IsIncreaseSpeedOnNeutralGear(speed))
		{
			return false;
		}

		if (IsInvalidSpeedOnDriveGears(speed))
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

bool CCar::IsSpeedValidForGear(int speed, int gear) const
{
	for (auto& range : s_speedTable) {
		if (range.gear == gear) {
			return range.minSpeed <= speed && speed <= range.maxSpeed;
		}
	}
	return false;
}

bool CCar::IsIncreaseSpeedOnNeutralGear(int speed) const
{
	// разбить на 2 функции
	return m_gear == GearNeutral && speed > abs(m_speed) || m_gear == GearReverse && !IsSpeedValidForGear(speed, GearReverse);
}

bool CCar::IsInvalidSpeedOnDriveGears(int speed) const
{
	return m_gear >= GearDrive1 && m_gear <= GearDrive5 && !IsSpeedValidForGear(speed, m_gear);
}
