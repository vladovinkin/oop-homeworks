// Shapes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "Shapes.h"

int main()
{
    CCircle circle = CCircle({ 2.3, 4.5 }, 6.7, 0x000000, 0xFFFFFF);
    std::cout << circle.GetArea() << '\n';
}
