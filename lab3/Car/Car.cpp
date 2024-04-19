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
	if (speed_ == 0 && gear_ == GearNeutral)
	{
		engineIsRunning_ = false;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{	
	if (possibleGears_.count(gear))
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
	return false;
}

bool Car::SetSpeed(int speed)
{
	if (speed >= SpeedMin && speed <= SpeedMax)
	{
		if (IsTurnedOn())
		{
			switch (gear_)
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
				if (speed > abs(speed_))
				{
					return false;
				}
			}
			speed_ = (gear_ == GearReverse || speed_ < 0)
				? -speed
				: speed;

			return true;
		}
	}
	return false;
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
	return std::abs(speed_);
}

Direction Car::GetDirection()
{
	return speed_ < 0
		? Direction::BACKWARD
		: (speed_ > 0
			? Direction::FORWARD
			: Direction::STAY_STILL);
}
