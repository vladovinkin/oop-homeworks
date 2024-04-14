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
0. Если у движущегося автомобиля на любой передаче выключить двигатель, он не заглохнет
If you turn off the engine of a moving car in any gear, it will not turn off
*/

