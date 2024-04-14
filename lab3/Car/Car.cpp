#include "car.h"

Car::Car()
{
	engineIsRunning_ = false;
	gear_ = 0;
	speed_ = 0;
}

bool Car::TurnOnEngine()
{
	return engineIsRunning_ = true;
}

bool Car::TurnOffEngine()
{
	return engineIsRunning_ = false;
}


bool Car::SetGear(int gear)
{
	if (IsTurnedOn())
	{
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
