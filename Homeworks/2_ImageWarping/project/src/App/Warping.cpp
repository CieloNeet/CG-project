#include "Wraping.h"
#include <cmath>

CWraping::CWraping()
{

}

CWraping::~CWraping()
{
	wraping_start_points.clear();
	wraping_end_points.clear();
}

void CWraping::Set_Points(vector<QPoint>& start, vector<QPoint>& end)
{
	for (size_t i = 0; i < start.size(); i++)
	{
		wraping_start_points.push_back(start[i]);
		wraping_end_points.push_back(end[i]);
	}
}

void CWraping::wraping(QImage& image)
{
	
}

void CWraping::Fill(QImage& image)
{

}

double CWraping::distance(QPoint start, QPoint end)
{
	double x0 = double(start.x()) - double(end.x()); 
	double y0 = double(start.y()) - double(end.y());
	double sum = sqrt(x0*x0+y0*y0);
	return sum;
}

bool CWraping::InImage(int x, int y, int width, int height)
{
	if (x > 0 && x < width - 1 && y>0 && y < height - 1)
	{
		return true;
	}
	else
		return false;
}

