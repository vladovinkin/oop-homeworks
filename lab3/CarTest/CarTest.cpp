#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Car/car.h"

/*
1. Автомобиль изначально незаведён, он не двигается, у него нулевая скорость и включена нейтральная передача
The car is initially not started, it does not move, it has zero speed and the neutral gear is engaged

2. Если попытаться заглушить незаведенный двигатель, он останется незаведённым
If you try to turn off an unstarted engine, it will remain unstarted
*/
SCENARIO("The car is initially unstarted, it does not move, it has zero speed and the neutral gear is engaged")
{
	GIVEN("Car witn not started engine")
	{
		Car car;
		REQUIRE(!car.IsTurnedOn());
		CHECK(car.GetDirection() == Direction::STAY_STILL);
		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetGear() == GearNeutral);

		WHEN("If you try to turn off an unstarted engine")
		{
			REQUIRE(car.TurnOffEngine());
			THEN("it will remain unstarted")
			{
				REQUIRE(!car.IsTurnedOn());
				CHECK(car.GetDirection() == Direction::STAY_STILL);
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetGear() == GearNeutral);
			}
		}
	}
}

/*
3. Если незавёденный двигатель завести, он заведётся
If you start the engine when it is not running, it will start

4. Если включить включенный двигатель, то он останется включенным
If you turn on the engine while it is on, it will remain on

5. Если у остановленного заведённого автомобиля на нейтральной передаче выключить двигатель, он выключится
If you turn off the engine of a stationary vehicle in neutral, it will turn off.
*/
SCENARIO("The car's engine is not started initially and if you start the engine when it is not running, it will start")
{
	GIVEN("Car witn not started engine")
	{
		Car car;
		REQUIRE(!car.IsTurnedOn());

		WHEN("Start engine")
		{
			REQUIRE(car.TurnOnEngine());
			THEN("Engine started")
			{
				CHECK(car.IsTurnedOn());
				CHECK(car.GetDirection() == Direction::STAY_STILL);
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetGear() == GearNeutral);
			}

			AND_WHEN("If you turn on the engine while it is on")
			{
				REQUIRE(car.TurnOnEngine());
				THEN("it will remain on")
				{
					CHECK(car.IsTurnedOn());
				}
			}

			AND_WHEN("If you turn off the engine of a stationary vehicle in neutral")
			{
				REQUIRE(car.IsTurnedOn());
				REQUIRE(car.GetDirection() == Direction::STAY_STILL);
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(car.GetGear() == GearNeutral);
				REQUIRE(car.TurnOffEngine());
				THEN("it will turn off")
				{
					CHECK(!car.IsTurnedOn());
				}
			}
		}
	}
}

/*
6. Когда двигатель не заведён, включена нейтральная передача

7. Если при незаведённом двигателе включить нейтрельную передачу, она включится
If you turn on the neutral gear when the engine is not running, it will turn on

8. Если при незаведённом двигетеле включить передачу, отличную от нейтральной, она не включится
If you engage a gear other than neutral when the engine is not running, it will not engage
*/
SCENARIO("Changing gears in a car with the engine not running")
{
	GIVEN("Car witn not started engine")
	{
		Car car;
		REQUIRE(!car.IsTurnedOn());
		WHEN("If you turn on the neutral gear when the engine is not running")
		{
			REQUIRE(car.SetGear(GearNeutral));
			THEN("it will turn on the neutral gear")
			{
				CHECK(car.GetGear() == GearNeutral);
			}
		}

		WHEN("If you engage a gear other than neutral when the engine is not running")
		{
			THEN("it will not engage")
			{
				CHECK(!car.SetGear(GearReverse));
				CHECK(!car.SetGear(GearDrive1));
				CHECK(!car.SetGear(GearDrive2));
				CHECK(!car.SetGear(GearDrive3));
				CHECK(!car.SetGear(GearDrive4));
				CHECK(!car.SetGear(GearDrive5));
			}
		}
	}
}

/*
* Переключение скоростей у остановленного автомобиля с заведённым двигателем на нейтральной передаче
* 
Если у остановленного автомобиля с заведённым двигателем на нейтральной передаче включить нейтральную передачу, она включится

Если у остановленного автомобиля с заведённым двигателем на нейтральной передаче включить первую передачу, она включится

Если у остановленного автомобиля на первый передаче включить нейтральную передачу, она включится

Если у остановленного автомобиля с заведённым двигателем на нейтральной передаче включить заднюю передачу, она включится

Если у остановленного автомобиля с заведённым двигателем на нейтральной передаче включить 2, 3, 4 или 5 передачу, она не включится
*/
SCENARIO("Changing gears with a stopped car with the engine running in neutral gear")
{
	GIVEN("The car is initially started, it does not move, it has zero speed and the neutral gear is engaged")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		CHECK(car.GetDirection() == Direction::STAY_STILL);
		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetGear() == GearNeutral);

		WHEN("If you put the gear in neutral")
		{
			REQUIRE(car.SetGear(GearNeutral));
			THEN("it will engage")
			{
				CHECK(car.GetGear() == GearNeutral);
			}

			AND_WHEN("If you put it in first gear")
			{
				REQUIRE(car.SetGear(GearDrive1));
				THEN("it will engage")
				{
					CHECK(car.GetGear() == GearDrive1);
				}
			}

			AND_WHEN("If you put the gear in neutral")
			{
				REQUIRE(car.SetGear(GearNeutral));
				THEN("it will engage")
				{
					CHECK(car.GetGear() == GearNeutral);
				}
			}

			AND_WHEN("If you put the gear in reverse")
			{
				REQUIRE(car.SetGear(GearReverse));
				THEN("it will engage")
				{
					CHECK(car.GetGear() == GearReverse);
				}
			}
		}

		WHEN("If you engage a gear other than reverse, neutral or first")
		{
			THEN("it will not engage")
			{
				REQUIRE(!car.SetGear(GearDrive2));
				REQUIRE(!car.SetGear(GearDrive3));
				REQUIRE(!car.SetGear(GearDrive4));
				REQUIRE(!car.SetGear(GearDrive5));
			}
		}
	}
}

/*
* Включение задней передачи, увеличение и уменьшение скорости
*/
SCENARIO("Engaging reverse gear, increasing and decreasing speed")
{
	GIVEN("Car witn started engine on reverse gear")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(GearReverse));
		REQUIRE(car.GetDirection() == Direction::STAY_STILL);
		REQUIRE(car.GetSpeed() == 0);

		WHEN("Speed change within acceptable limits")
		{
			THEN("speed will changed")
			{
				REQUIRE(car.SetSpeed(20));
				CHECK(car.GetDirection() == Direction::BACKWARD);
				CHECK(car.GetSpeed() == 20);

				AND_WHEN("change gear to Neutral")
				{
					REQUIRE(car.SetSpeed(15));
					REQUIRE(!car.SetSpeed(25));

					REQUIRE(car.SetGear(GearNeutral));
					REQUIRE(car.SetSpeed(10));
					CHECK(car.GetDirection() == Direction::BACKWARD);
					REQUIRE(!car.SetSpeed(15));
				}
			}
		}
	}
}


/*
Если у движущегося автомобиля на любой передаче выключить двигатель, он не выключится
If you turn off the engine of a moving car in any gear, it will not turn off
*/
SCENARIO("If you turn off the engine of a moving car in any gear, it will not turn off")
{
	GIVEN("Moving car witn started engine on first gear")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(GearDrive1));
		REQUIRE(car.SetSpeed(15));

		WHEN("attempt turn off the engine of a moving car")
		{
			REQUIRE(!car.TurnOffEngine());
			THEN("it will not turn off")
			{
				CHECK(car.IsTurnedOn());
			}
		}
	}
}

// Разгон на 1 передаче до допустимой и недопустимой скорости
SCENARIO("Acceleration in 1st gear to permissible and unacceptable speed")
{
	GIVEN("Stopped car witn started engine in first gear")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(GearDrive1));
		REQUIRE(car.GetSpeed() == 0);

		WHEN("Set speed 0")
		{
			REQUIRE(car.SetSpeed(0));
			THEN("Speed will remain 0")
			{
				CHECK(car.GetSpeed() == 0);
			}
		}

		WHEN("Set speed -1")
		{
			REQUIRE(!car.SetSpeed(-1));
			THEN("Speed will remain 0")
			{
				CHECK(car.GetSpeed() == 0);
			}
		}

		WHEN("Set speed 15")
		{
			REQUIRE(car.SetSpeed(15));
			THEN("Speed will set to 15")
			{
				CHECK(car.GetSpeed() == 15);
			}
		}

		WHEN("Set speed 30")
		{
			REQUIRE(car.SetSpeed(30));
			THEN("Speed will set to 30")
			{
				CHECK(car.GetSpeed() == 30);
			}
		}

		WHEN("Set speed 31")
		{
			REQUIRE(!car.SetSpeed(31));
			THEN("Speed will remain 0")
			{
				CHECK(car.GetSpeed() == 0);
			}
		}
	}
}

// Изменение скорости движущегося автомобиля на нейтральной передаче
SCENARIO("Changing the speed of a moving car witn started engine in neutral gear")
{
	GIVEN("Car witn started engine moving forward in neutral gear")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(GearDrive1));
		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.SetGear(GearNeutral));
		REQUIRE(car.GetSpeed() == 20);

		WHEN("Increase speed")
		{
			REQUIRE(!car.SetSpeed(30));
			THEN("Speed will not set")
			{
				CHECK(car.GetSpeed() == 20);
			}
		}

		WHEN("Decrease speed")
		{
			REQUIRE(car.SetSpeed(10));
			THEN("Speed will set")
			{
				CHECK(car.GetSpeed() == 10);
			}
		}

		WHEN("Decrease speed to negative value")
		{
			REQUIRE(!car.SetSpeed(-1));
			THEN("Speed will not set")
			{
				CHECK(car.GetSpeed() == 20);
			}
		}

		WHEN("Set speed to current value")
		{
			REQUIRE(car.SetSpeed(20));
			THEN("Speed will remain the currentn value")
			{
				CHECK(car.GetSpeed() == 20);
			}
		}
	}

	GIVEN("Car moving backward in neutral gear")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(GearReverse));
		REQUIRE(car.SetSpeed(10));
		REQUIRE(car.SetGear(GearNeutral));
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == Direction::BACKWARD);

		WHEN("Increase speed")
		{
			REQUIRE(!car.SetSpeed(20));
			THEN("Speed will not set")
			{
				CHECK(car.GetSpeed() == 10);
				REQUIRE(car.GetDirection() == Direction::BACKWARD);
			}
		}

		WHEN("Decrease speed")
		{
			REQUIRE(car.SetSpeed(5));
			THEN("Speed will set")
			{
				CHECK(car.GetSpeed() == 5);
				REQUIRE(car.GetDirection() == Direction::BACKWARD);
			}
		}

		WHEN("Decrease speed to negative value")
		{
			REQUIRE(!car.SetSpeed(-1));
			THEN("Speed will not set")
			{
				CHECK(car.GetSpeed() == 10);
				REQUIRE(car.GetDirection() == Direction::BACKWARD);
			}
		}

		WHEN("Set speed to current value")
		{
			REQUIRE(car.SetSpeed(10));
			THEN("Speed will remain the currentn value")
			{
				CHECK(car.GetSpeed() == 10);
				REQUIRE(car.GetDirection() == Direction::BACKWARD);
			}
		}
	}
}

// Включение передач на различных скоростях
SCENARIO("Engaging gears within acceptable speed ranges")
{
	GIVEN("Stopped car witn started engine in neutral gear")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());

		CHECK(car.GetGear() == GearNeutral);
		CHECK(car.GetDirection() == Direction::STAY_STILL);
		CHECK(car.GetSpeed() == 0);

		WHEN("Engage first gear ")
		{
			REQUIRE(car.SetGear(GearDrive1));
			THEN("Gear engaged")
			{
				CHECK(car.GetGear() == GearDrive1);
			}
		}
	}
}

/* Template
 SCENARIO("")
{
	GIVEN("")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
	
		WHEN("")
		{
			REQUIRE();
			THEN("")
			{
				CHECK();
			}
		}
	}
}
*/