// Shapes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "Shapes.h"

int main()
{
    std::vector<std::unique_ptr<IShape>> shapes;

    CCircle circle = CCircle({ 2.3, 4.5 }, 6.7, 0x000000, 0xFFFFFF);
    shapes.push_back(std::make_unique<CCircle>(circle));

    CTriangle triangle = CTriangle({ 3.4, 2.2 }, { 6.4, 8.2 }, { 1.9, 4.6 }, 0x333333, 0x545454);
    shapes.push_back(std::make_unique<CTriangle>(triangle));

    CLineSegment line = CLineSegment({ 7.4, 3.0 }, { 15.2, 7.3 }, 0x282828);
    shapes.push_back(std::make_unique<CLineSegment>(line));

    for (const auto& shape : shapes)
    {
        std::cout << shape->ToString() << '\n';
        std::cout << "area: " << shape->GetArea() << '\n';
        std::cout << "perimeter: " << shape->GetPerimeter() << '\n';
    }

    return 0;
}
