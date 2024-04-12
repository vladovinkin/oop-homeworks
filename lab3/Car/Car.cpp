#include "car.h"

Car::Car()
{
	engineIsRunning_ = false;
	gear_ = 0;
	speed_ = 0;
}

bool Car::IsEngineTurnedOn()
{
	return engineIsRunning_;
}

bool Car::TurnOnEngine()
{
	return engineIsRunning_ = true;
}

Direction Car::GetDirection()
{
	return speed_ < 0
		? 
		: ;
}

int Car::GetGear()
{
	return gear_;
}

int Car::GetSpeed()
{
	return speed_;
}