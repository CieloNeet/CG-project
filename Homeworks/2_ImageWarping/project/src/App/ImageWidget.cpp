#include "ImageWidget.h"
#include <QImage>
#include <QPainter>
#include <QtWidgets> 
#include <iostream>

//using std::cout;
//using std::endl;
using namespace std;

ImageWidget::ImageWidget(void)
{
	ptr_image_ = new QImage();
	ptr_image_backup_ = new QImage();
	isSelect = false;
	wrap_mode = WrapMode::kDefault;
	mwrap = NULL;
	
	
}


ImageWidget::~ImageWidget(void)
{
}

void ImageWidget::Paint(QPainter& painter, QPoint start, QPoint end)
{
	QPen pen1,pen2,pen3;
	pen1.setWidth(7); pen1.setColor(Qt::green); 
	pen2.setWidth(2); pen2.setColor(Qt::black);
	pen3.setWidth(7); pen3.setColor(Qt::red);
	
	if (start.x() == end.x() && start.y() == end.y())
	{
		painter.setPen(pen1);
		painter.drawPoint(start);
	}
	else
	{
		painter.setPen(pen1);
		painter.drawPoint(start);
		
		painter.setPen(pen2);
		painter.drawLine(start, end);

		painter.setPen(pen3);
		painter.drawPoint(end);
	}
}

void ImageWidget::paintEvent(QPaintEvent *paintevent)
{
	QPainter painter;
	painter.begin(this);

	// Draw background
	painter.setBrush(Qt::lightGray);
	QRect back_rect(0, 0, width(), height());
	painter.drawRect(back_rect);

	// Draw image
	//QRect rect = QRect( (width()-ptr_image_->width())/2, (height()-ptr_image_->height())/2, ptr_image_->width(), ptr_image_->height());
	QRect rect = QRect(0, 0, ptr_image_->width(), ptr_image_->height());
	painter.drawImage(rect, *ptr_image_); 


	if (isSelect)
	{
		/*QPen pen;
		pen.setColor(Qt::green);
		pen.setWidth(4);
		painter.setPen(pen);
		painter.drawLine(start_point, end_point);
		for (int i = 0; i < mstart_points.size(); i++)
		{
			painter.drawLine(mstart_points[i], mend_points[i]);
		}*/
		Paint(painter, start_point, end_point);
		for (int i = 0; i < mstart_points.size(); i++)
		{
			Paint(painter, mstart_points[i], mend_points[i]);
		}
	}

	painter.end();
	update();
}

void ImageWidget::mousePressEvent(QMouseEvent* mouseevent)
{
	if (isSelect && Qt::LeftButton == mouseevent->button())
	{
		start_point = end_point = mouseevent->pos();
	}
}

void ImageWidget::mouseMoveEvent(QMouseEvent* mouseevent)
{
	if (isSelect)
	{
		end_point = mouseevent->pos();
	}
	
}

void ImageWidget::mouseReleaseEvent(QMouseEvent* mouseevent)
{
	if (isSelect)
	{
		end_point = mouseevent->pos();
		mstart_points.push_back(start_point);
		mend_points.push_back(end_point);
	}
}


void ImageWidget::Select_Point()
{
	isSelect = (!isSelect) ? true : false;
	
}

void ImageWidget::Set_wrapmode_to_IDW()
{
	wrap_mode = WrapMode::kIDW;
	Wrap();
}

void ImageWidget::Set_wrapmode_to_RBF()
{
	wrap_mode = WrapMode::kRBF;
	Wrap();
}

void ImageWidget::Wrap()
{
	switch (wrap_mode)
	{
	case WrapMode::kIDW:
		mwrap = new IDW();
		break;

	case WrapMode::kRBF:
		mwrap = new RBF();
		break;

	case WrapMode::kDefault:
		break;
	}
	if (mwrap != NULL)
	{
		mwrap->Set_Points(mstart_points, mend_points);
		mwrap->wraping(*(ptr_image_));
		//isSelect = false;
	}
	update();
	mwrap = NULL;
}

void ImageWidget::Open()
{
	// Open file
	QString fileName = QFileDialog::getOpenFileName(this, tr("Read Image"), ".", tr("Images(*.bmp *.png *.jpg)"));

	// Load file
	if (!fileName.isEmpty())
	{
		ptr_image_->load(fileName);
		*(ptr_image_backup_) = *(ptr_image_);
	}

	//ptr_image_->invertPixels(QImage::InvertRgb);
	//*(ptr_image_) = ptr_image_->mirrored(true, true);
	//*(ptr_image_) = ptr_image_->rgbSwapped();
	cout<<"image size: "<<ptr_image_->width()<<' '<<ptr_image_->height()<<endl;
	update();
}

void ImageWidget::Save()
{
	SaveAs();
}

void ImageWidget::SaveAs()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), ".", tr("Images(*.bmp *.png *.jpg)"));
	if (filename.isNull())
	{
		return;
	}	

	ptr_image_->save(filename);
}

void ImageWidget::Invert()
{
	for (int i=0; i<ptr_image_->width(); i++)
	{
		for (int j=0; j<ptr_image_->height(); j++)
		{
			QRgb color = ptr_image_->pixel(i, j);
			ptr_image_->setPixel(i, j, qRgb(255-qRed(color), 255-qGreen(color), 255-qBlue(color)) );
		}
	}

	// equivalent member function of class QImage
	// ptr_image_->invertPixels(QImage::InvertRgb);
	update();
}

void ImageWidget::Mirror(bool ishorizontal, bool isvertical)
{
	QImage image_tmp(*(ptr_image_));
	int width = ptr_image_->width();
	int height = ptr_image_->height();

	if (ishorizontal)
	{
		if (isvertical)
		{
			for (int i=0; i<width; i++)
			{
				for (int j=0; j<height; j++)
				{
					ptr_image_->setPixel(i, j, image_tmp.pixel(width-1-i, height-1-j));
				}
			}
		} 
		else
		{
			for (int i=0; i<width; i++)
			{
				for (int j=0; j<height; j++)
				{
					ptr_image_->setPixel(i, j, image_tmp.pixel(i, height-1-j));
				}
			}
		}
		
	}
	else
	{
		if (isvertical)
		{
			for (int i=0; i<width; i++)
			{
				for (int j=0; j<height; j++)
				{
					ptr_image_->setPixel(i, j, image_tmp.pixel(width-1-i, j));
				}
			}
		}
	}

	// equivalent member function of class QImage
	//*(ptr_image_) = ptr_image_->mirrored(true, true);
	update();
}

void ImageWidget::TurnGray()
{
	for (int i=0; i<ptr_image_->width(); i++)
	{
		for (int j=0; j<ptr_image_->height(); j++)
		{
			QRgb color = ptr_image_->pixel(i, j);
			int gray_value = (qRed(color)+qGreen(color)+qBlue(color))/3;
			ptr_image_->setPixel(i, j, qRgb(gray_value, gray_value, gray_value) );
		}
	}

	update();
}

void ImageWidget::Restore()
{
	*(ptr_image_) = *(ptr_image_backup_);
	
	update();
}

void ImageWidget::Clear()
{
	mstart_points.clear();
	mend_points.clear();
	start_point = end_point = QPoint(-1, -1);
	update();
}

void ImageWidget::Clear_All()
{
	*(ptr_image_) = *(ptr_image_backup_);
	isSelect = false;
	mstart_points.clear();
	mend_points.clear();
	start_point = end_point = QPoint(-1, -1);
	
	update();
}