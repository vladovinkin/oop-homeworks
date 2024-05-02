﻿#pragma once

enum class Direction
{
	BACKWARD,
	STAY_STILL,
	FORWARD,
};

constexpr int GearReverse = -1;
constexpr int GearNeutral = 0;
constexpr int GearDrive1 = 1;
constexpr int GearDrive2 = 2;
constexpr int GearDrive3 = 3;
constexpr int GearDrive4 = 4;
constexpr int GearDrive5 = 5;

constexpr int SpeedMin = 0;
constexpr int SpeedMax = 150;

const int GearSpeedLimit[6][2]{
	{0, 0},
	{0, 30},
	{20, 50},
	{30, 60},
	{40, 90},
	{50, 150},
};

class CCar
{
	public:
		CCar();
		bool TurnOnEngine();
		bool TurnOffEngine();
		bool SetGear(int gear);
		bool SetSpeed(int speed);

		bool IsTurnedOn() const;
		int GetGear() const;
		int GetSpeed() const;
		Direction GetDirection() const;
	private:
		int m_gear;
		int m_speed;
		bool m_engineIsRunning;
};