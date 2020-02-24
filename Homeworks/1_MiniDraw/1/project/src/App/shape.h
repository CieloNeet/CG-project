#pragma once

#include <QtGui>
#include <vector>

using std::vector;

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw(QPainter &paint)=0;	void set_start(QPoint s);	void set_end(QPoint e);
	void set_point_list_(const vector<QPoint>& points);

public:
	enum Type
	{
		kDefault = 0,
		kLine=1,
		kRect=2,
		kEllipse =3,
		kPolygon =4,
		kFree = 5
	};
	
protected:
	QPoint start;
	QPoint end;
	vector<QPoint> point_list_;
};

