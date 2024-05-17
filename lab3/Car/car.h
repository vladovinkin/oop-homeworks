#pragma once

enum class Direction
{
	BACKWARD,
	STAY_STILL,
	FORWARD,
};

struct GearSpeedRange {
	int gear;
	int minSpeed;
	int maxSpeed;
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
		bool IsSpeedValidForGear(int speed, int gear) const;
		bool IsIncreaseSpeedOnNeutralGear(int speed) const;
		bool IsInvalidSpeedOnDriveGears(int speed) const;
	private:
		int m_gear;
		int m_speed;
		bool m_engineIsRunning;
		static const std::vector<GearSpeedRange> s_speedTable;
};