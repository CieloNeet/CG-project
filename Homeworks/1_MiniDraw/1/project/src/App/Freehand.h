#pragma once

#include "shape.h"

class Freehand :public Shape
{
public:
	Freehand();
	~Freehand();

	void Draw(QPainter& painter);
};
