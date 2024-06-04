#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Shapes/CStorage.h"

double roundFloat(double var)
{
	double value = (int)(var * 100.0 + .5);
	return (double)value / 100.0;
}

/*
std::shared_ptr<IShape> line = std::make_shared<CLineSegment>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, border_color);

std::shared_ptr<IShape> triangle = std::make_shared<CTriangle>(CPoint{ x1, y1 }, CPoint{ x2, y2 }, CPoint{ x3, y3 }, border_color, fill_color);

std::shared_ptr<IShape> rect = std::make_shared<CRectangle>(CPoint{ x, y }, width, height, border_color, fill_color);

std::shared_ptr<IShape> circle = std::make_shared<CCircle>(CPoint{ x, y }, radius, border_color, fill_color);

*/

SCENARIO("Adding one object with zero perimeter and zero area")
{
	GIVEN("Add empty shape")
	{
		CStorage store;
		std::shared_ptr<IShape> line = std::make_shared<CLineSegment>(CPoint{ 5, 5 }, CPoint{ 5, 5 }, 0x767676);

		store.AddShape(line);

		REQUIRE(store.GetSize() == 1);

		auto minPerimeterShape = store.GetShapeWithMinPerimeter();

		REQUIRE(minPerimeterShape->GetOutlineColor() == 0x767676);
		REQUIRE(roundFloat(minPerimeterShape->GetPerimeter()) == 0.0);
		REQUIRE(roundFloat(minPerimeterShape->GetArea()) == 0.0);
	}
}

SCENARIO("Adding one object to storage make storage size = 1")
{
	GIVEN("Add one shape")
	{
		CStorage store;
		std::shared_ptr<IShape> line = std::make_shared<CLineSegment>(CPoint{ 1, 2 }, CPoint{ 3, 4 }, 0xABCDEF);

		store.AddShape(line);

		REQUIRE(store.GetSize() == 1);

		auto minPerimeterShape = store.GetShapeWithMinPerimeter();

		REQUIRE(minPerimeterShape->GetOutlineColor() == 0xABCDEF);
		REQUIRE(roundFloat(minPerimeterShape->GetPerimeter()) == 2.83);
		REQUIRE(minPerimeterShape->GetArea() == 0.0);
	}
}

SCENARIO("Adding some object and choose shape with minimum perimeter")
{
	GIVEN("Add some shapes to choose shape with minimum perimeter")
	{
		CStorage store;

		std::shared_ptr<IShape> line = std::make_shared<CLineSegment>(CPoint{ 1, 2 }, CPoint{ 354, 45 }, 0xABCDEF);
		store.AddShape(line);

		std::shared_ptr<IShape> rect = std::make_shared<CRectangle>(CPoint{ 4, 5 }, 10, 8, 0x545454, 0xCCCCCC);
		store.AddShape(rect);

		std::shared_ptr<IShape> tri = std::make_shared<CTriangle>(CPoint{ 0, 1 }, CPoint{ 5, 6 }, CPoint{ 8, 4 }, 0x101010, 0xFFFFFF);
		store.AddShape(tri);

		std::shared_ptr<IShape> circle = std::make_shared<CCircle>(CPoint{ 2, 3 }, 9, 0x323232, 0xA7A7AB);
		store.AddShape(circle);

		REQUIRE(store.GetSize() == 4);

		auto minPerimeterShape = store.GetShapeWithMinPerimeter();

		REQUIRE(minPerimeterShape->GetOutlineColor() == 0x101010);
		REQUIRE(roundFloat(minPerimeterShape->GetPerimeter()) == 19.22);
		REQUIRE(roundFloat(minPerimeterShape->GetArea()) == 12.5);
		REQUIRE(minPerimeterShape->ToString() == "Shape type: triangle\nVertex1: x = 0.00; y = 1.00\nVertex2: x = 5.00; y = 6.00\nVertex3: x = 8.00; y = 4.00\nFill color: #ffffff");
	}
}

SCENARIO("Adding some object and choose shape with maximum area")
{
	GIVEN("Add some shapes to choose shape with maximum area")
	{
		CStorage store;

		std::shared_ptr<IShape> line = std::make_shared<CLineSegment>(CPoint{ 1, 2 }, CPoint{ 354, 45 }, 0xABCDEF);
		store.AddShape(line);

		std::shared_ptr<IShape> rect = std::make_shared<CRectangle>(CPoint{ 4, 5 }, 10, 8, 0x545454, 0xCCCCCC);
		store.AddShape(rect);

		std::shared_ptr<IShape> tri = std::make_shared<CTriangle>(CPoint{ 0, 1 }, CPoint{ 5, 6 }, CPoint{ 8, 4 }, 0x101010, 0xFFFFFF);
		store.AddShape(tri);

		std::shared_ptr<IShape> circle = std::make_shared<CCircle>(CPoint{ 2, 3 }, 9, 0x323232, 0xA7A7AB);
		store.AddShape(circle);

		REQUIRE(store.GetSize() == 4);

		auto maxAreaShape = store.GetShapeWithMaxArea();

		REQUIRE(maxAreaShape->GetOutlineColor() == 0x323232);
		REQUIRE(roundFloat(maxAreaShape->GetArea()) == 254.47);
		REQUIRE(roundFloat(maxAreaShape->GetPerimeter()) == 56.55);
	}
}
