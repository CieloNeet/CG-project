#pragma once
#include <QWidget>
#include <vector>
#include <iostream>

//using namespace std;
using std::vector;

class CWraping
{
public:
	CWraping();
	~CWraping();

	virtual void wraping(QImage& image);
	virtual void Fill(QImage& image);
	void Set_Points(vector<QPoint>& start, vector<QPoint>& end);
	double distance(QPoint start, QPoint end);
	bool InImage(int x, int y, int width, int height);
	
	

protected:
	vector<QPoint> wraping_start_points;
	vector<QPoint> wraping_end_points;
	
};

