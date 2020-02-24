#include "viewwidget.h"

ViewWidget::ViewWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	draw_status_ = false;
	shape_ = NULL;
	type_ = Shape::kDefault;
}

ViewWidget::~ViewWidget()
{
	for (size_t i = 0; i < shape_list_.size(); i++)
	{
		if (shape_list_[i])
		{
			delete shape_list_[i];
			shape_list_[i] = NULL;
		}
	}
}

void ViewWidget::setLine()
{
	type_ = Shape::kLine;
}

void ViewWidget::setRect()
{
	type_ = Shape::kRect;
}

void ViewWidget::setEll()
{
	type_ = Shape::kEllipse;
}

void ViewWidget::setPol()
{
	type_ = Shape::kPolygon;
}

void ViewWidget::setFree()
{
	type_ = Shape::kFree;
}

void ViewWidget::mousePressEvent(QMouseEvent* event)
{
	if (Qt::LeftButton == event->button())
	{
		switch (type_)
		{
		case Shape::kLine:
			shape_ = new Line();
			break;
		case Shape::kDefault:
			break;

		case Shape::kRect:
			shape_ = new Rect();
			break;

		case Shape::kEllipse:
			shape_ = new CEllipse();
			break;

		case Shape::kPolygon:
			//shape_ = new CPolygon();
			draw_status_ = true;
			start_point_ = end_point_ = event->pos();
			points.push_back(start_point_);
			break;

		case Shape::kFree:
			draw_status_ = true;
			start_point_ = end_point_ = event->pos();
			points.push_back(start_point_);
			break;

		}
		
		if (shape_ != NULL)
		{
			draw_status_ = true;
			start_point_ = end_point_ = event->pos();
			shape_->set_start(start_point_);
			shape_->set_end(end_point_);
			
			
		}
	}
	update();
}

void ViewWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (draw_status_ &&shape_ != NULL)
	{
		end_point_ = event->pos();
		shape_->set_end(end_point_);
	}
	if (type_ == Shape::kFree)
	{
		end_point_ = event->pos();
		points.push_back(end_point_);
	}
	
	
}

void ViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (type_ == Shape::kPolygon)
	{
		if (Qt::LeftButton == event->button())
		{
			points.push_back(end_point_);
		}
		else
		{
			points.push_back(end_point_);
			
			shape_ = new CPolygon();
			shape_->set_point_list_(points);
			points.clear();
			draw_status_ = false;
			shape_list_.push_back(shape_);
		    shape_ = NULL;
		}
		/*if (Qt::LeftButton != event->button())
		{
			draw_status_ = false;
			shape_list_.push_back(shape_);
			shape_ = NULL;
			shape_ = new Line();
			shape_->set_start(end_point_);
			shape_->set_end(start_point_);
			shape_list_.push_back(shape_);
			shape_ = NULL;
		}
		else
		{
			shape_list_.push_back(shape_);
			//shape_ = NULL;
		}*/
	}
	else if (type_ == Shape::kFree)
	{
		points.push_back(end_point_);
		shape_ = new Freehand();
		shape_->set_point_list_(points);
		points.clear();
		draw_status_ = false;
		shape_list_.push_back(shape_);
		shape_ = NULL;
	}
	else if (shape_ != NULL)
	{
		draw_status_ = false;
		shape_list_.push_back(shape_);
		shape_ = NULL;
	}
}

void ViewWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	for (int i = 0; i < shape_list_.size(); i++)
	{
		shape_list_[i]->Draw(painter);
	}

	if (shape_ != NULL) {
		shape_->Draw(painter);
	}

	if (type_ == Shape::kPolygon) {
		QPen mpen;
		mpen.setWidth(10);
		painter.setPen(mpen);
		painter.drawPoint(start_point_);
	}
	if (type_ == Shape::kFree)
	{
		QPen mpen;
		mpen.setWidth(10);
		painter.setPen(mpen);
		painter.drawPoint(end_point_);
	}

	update();
}

void ViewWidget::Undo()
{
	if (!shape_list_.empty())
	{
		if (shape_list_.back())
		{
			delete shape_list_.back();
			shape_list_.back() = NULL;
			shape_list_.pop_back();
		}
	}
	
	update();
}