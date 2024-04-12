#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Car/car.h"

/*
* Автомобиль изначально незаведён, он не двигается, у него нулевая скорость и включена нейтральная передача
*/
SCENARIO("The car is initially unstarted, it does not move, it has zero speed and the neutral gear is engaged")
{
	GIVEN("Car witn not started engine")
	{
		Car car;
		REQUIRE(!car.IsEngineTurnedOn());
		CHECK(car.GetDirection() == Direction::STAY_STILL);
		CHECK(car.GetSpeed() == 0);
		CHECK(car.);
	}
}

/*
1. У автомобиля двигатель изначально не заведён.
The car's engine is not started initially

2. Если незавёденный двигатель завести, он заведётся
If you start the engine when it is not running, it will start
*/
SCENARIO("The car's engine is not started initially and if you start the engine when it is not running, it will start")
{
	GIVEN("Car witn not started engine")
	{
		Car car;
		REQUIRE(!car.IsEngineTurnedOn());

		WHEN("Start engine")
		{
			car.TurnOnEngine();
			THEN("Engine started")
			{
				CHECK(car.IsEngineTurnedOn());
			}
		}
	}
}

/*
3. Когда двигатель не заведён, включена нейтральная передача

4. Если при незаведённом двигателе включить нейтрельную передачу, она включится
If you turn on the neutral gear when the engine is not running, it will turn on

5. Если при незаведённом двигетеле включить передачу, отличную от нейтральной, она не включится
If you engage a gear other than neutral when the engine is not running, it will not engage
*/
SCENARIO("Сhanging gears in a car with the engine not running")
{
	GIVEN("Car witn not started engine")
	{
		Car car;
		REQUIRE(!car.IsEngineTurnedOn());

		WHEN("If you turn on the neutral gear when the engine is not running")
		{
			THEN("it will turn on the neutral gear")
			{
				CHECK(car.SetGear(GearNeutral));
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
5. Если у остановленного автомобиля на нейтральной передаче выключить двигатель, он заглохнет
If you turn off the engine of a stationary vehicle in neutral, it will turn off.

6. Если у движущегося автомобиля на любой передаче выключить двигатель, он не заглохнет
If you turn off the engine of a moving car in any gear, it will not turn off
*/