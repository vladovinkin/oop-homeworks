#pragma once
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

class CStorage
{
public:
	CStorage() = default;
	void AddShape(std::shared_ptr<IShape> shape);
	size_t GetSize() const;
	std::shared_ptr<IShape> GetShapeWithMaxArea() const;
	std::shared_ptr<IShape> GetShapeWithMinPerimeter() const;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};