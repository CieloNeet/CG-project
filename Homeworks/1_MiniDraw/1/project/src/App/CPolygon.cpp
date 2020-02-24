#include "Polygon.h"
#include <iostream>

CPolygon::CPolygon()
{

}


CPolygon::~CPolygon()
{
	point_list_.clear();
}

void CPolygon::Draw(QPainter& painter)
{
	unsigned int n = point_list_.size();
	QPointF* points;
	points = new QPointF[point_list_.size()];
	for (size_t i = 0; i < point_list_.size(); i++)
	{
		points[i] = point_list_[i];
	}
	
	painter.drawPolygon(points, n);

	delete points;
	points = NULL;
}