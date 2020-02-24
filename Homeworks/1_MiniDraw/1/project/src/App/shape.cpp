#include "shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
}

void Shape::set_start(QPoint s)
{
	start = s;
}

void Shape::set_end(QPoint e)
{
	end = e;
}

void Shape::set_point_list_(const vector<QPoint>& points)
{
	//point_list_.clear();
	for (size_t i = 0; i < points.size(); i++)
	{
		point_list_.push_back(points[i]);
	}
}
