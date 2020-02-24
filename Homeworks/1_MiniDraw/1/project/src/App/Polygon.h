#pragma once

#include"shape.h"

class CPolygon :public Shape
{
public:
	CPolygon();
	~CPolygon();

	void Draw(QPainter& painter);
};