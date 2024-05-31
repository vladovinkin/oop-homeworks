#include "stdafx.h"
#include "CStorage.h"

void CStorage::AddShape(std::shared_ptr<IShape> shape)
{
	m_shapes.push_back(shape);
}

size_t CStorage::GetSize() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> CStorage::GetShapeWithMaxArea() const
{
	std::shared_ptr<IShape> resultShape;
	double maxArea = -1.0;

	for (const auto& shape : m_shapes)
	{
		double shapeArea = shape->GetArea();
		if (maxArea < 0.0 || shapeArea > maxArea)
		{
			resultShape = shape;
			maxArea = shapeArea;
		}
	}

	return resultShape;
}

std::shared_ptr<IShape> CStorage::GetShapeWithMinPerimeter() const
{
	std::shared_ptr<IShape> resultShape;
	double minPerimeter = -1.0;

	for (const auto& shape : m_shapes)
	{
		double shapePerimeter = shape->GetPerimeter();
		if (minPerimeter < 0.0 || shapePerimeter < minPerimeter)
		{
			resultShape = shape;
			minPerimeter = shapePerimeter;
		}
	}

	return resultShape;
}