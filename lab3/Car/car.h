#pragma once

enum class Direction {
	BACKWARD,
	STAY_STILL,
	FORWARD,
};

struct Info {
	int gear;
	int speed;
	bool engineIsRunning;
};

constexpr int GearReverse = -1;
constexpr int GearNeutral = 0;
constexpr int GearDrive1 = 1;
constexpr int GearDrive2 = 2;
constexpr int GearDrive3 = 3;
constexpr int GearDrive4 = 4;
constexpr int GearDrive5 = 5;

class Car {
	public:
		Car();
		bool TurnOnEngine();
		bool TurnOffEngine();
		bool SetGear(int gear);
		bool SetSpeed(int speed);

		bool IsTurnedOn();
		int GetGear();
		int GetSpeed();
		Direction GetDirection();
	private:
		int gear_;
		int speed_;
		bool engineIsRunning_;
};