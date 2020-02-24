#include "Freehand.h"

Freehand::Freehand()
{

}

Freehand::~Freehand()
{
	point_list_.clear();
}

void Freehand::Draw(QPainter& painter)
{
	for (size_t i = 0; i < point_list_.size()-1; i++)
	{
		painter.drawLine(point_list_[i], point_list_[i + 1]);
	}
}