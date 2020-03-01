#pragma once
#include <QWidget>
#include <qpen.h>
#include "Wraping.h"
#include "IDW.h"
#include "RBF.h"

QT_BEGIN_NAMESPACE
class QImage;
class QPainter;
QT_END_NAMESPACE

using std::vector;

enum class WrapMode
{
	kDefault = 0,
	kIDW=1,
	kRBF=2,
};

class ImageWidget :
	public QWidget
{
	Q_OBJECT

public:
	ImageWidget(void);
	~ImageWidget(void);
	

protected:
	void paintEvent(QPaintEvent *paintevent);
	void mousePressEvent(QMouseEvent* mouseEvent);
	void mouseMoveEvent(QMouseEvent* mouseEvent);
	void mouseReleaseEvent(QMouseEvent* mouseEvent);
	void Paint(QPainter& painter,QPoint start,QPoint end);

public slots:
	// File IO
	void Open();												// Open an image file, support ".bmp, .png, .jpg" format
	void Save();												// Save image to current file
	void SaveAs();												// Save image to another file

	// Image processing
	void Invert();												// Invert pixel value in image
	void Mirror(bool horizontal=false, bool vertical=true);		// Mirror image vertically or horizontally
	void TurnGray();											// Turn image to gray-scale map
	void Restore();			// Restore image to origin
	void Clear();           // clear the selected points
	void Clear_All();

	void Select_Point();
	void Set_wrapmode_to_IDW();
	void Set_wrapmode_to_RBF();
	void Wrap();

	

private:
	QImage* ptr_image_;				// image 
	QImage* ptr_image_backup_;
	vector<QPoint>     mstart_points;
	vector<QPoint>     mend_points;
	QPoint             start_point;
	QPoint             end_point;
	WrapMode           wrap_mode;
	CWraping* mwrap;
	bool               isSelect;
	

};

