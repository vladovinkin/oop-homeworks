#include "car.h"

Car::Car()
{
	engineIsRunning_ = false;
	gear_ = 0;
	speed_ = 0;
}

bool Car::TurnOnEngine()
{
	engineIsRunning_ = true;
	return true;
}

bool Car::TurnOffEngine()
{
	engineIsRunning_ = false;
	return true;
}


bool Car::SetGear(int gear)
{
	if (IsTurnedOn())
	{
		switch (gear)
		{
		case GearReverse:
			if (speed_ != 0)
			{
				return false;
			}
			break;
		case GearDrive1:
			if (speed_ < 0 || speed_ > 30)
			{
				return false;
			}
			break;
		case GearDrive2:
			if (speed_ < 20 || speed_ > 50)
			{
				return false;
			}
			break;
		case GearDrive3:
			if (speed_ < 30 || speed_ > 60)
			{
				return false;
			}
			break;
		case GearDrive4:
			if (speed_ < 40 || speed_ > 90)
			{
				return false;
			}
			break;
		case GearDrive5:
			if (speed_ < 50 || speed_ > 150)
			{
				return false;
			}
			break;
		}
		gear_ = gear;
		return true;
	}
	else
	{
		return gear == GearNeutral;
	}
}

bool Car::SetSpeed(int speed)
{
	speed_ = speed;
	return true;
}

bool Car::IsTurnedOn()
{
	return engineIsRunning_;
}

int Car::GetGear()
{
	return gear_;
}

int Car::GetSpeed()
{
	return speed_;
}

Direction Car::GetDirection()
{
	return speed_ < 0
		? Direction::BACKWARD
		: (speed_ > 0
			? Direction::FORWARD
			: Direction::STAY_STILL);
}
