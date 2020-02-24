#include "minidraw.h"

MiniDraw::MiniDraw(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	view_widget_ = new ViewWidget();
	Creat_Action();
	Creat_ToolBar();
	Creat_Menu();
	setCentralWidget(view_widget_);
}

void MiniDraw::Creat_Action()
{
	Action_About = new QAction(tr("&About"), this);
	connect(Action_About, &QAction::triggered, this, &MiniDraw::AboutBox);
	Action_Line = new QAction(tr("&Line"), this);
	connect(Action_Line, SIGNAL(triggered()), view_widget_, SLOT(setLine()));

	Action_Rect = new QAction(tr("&Rect"), this);
	connect(Action_Rect, &QAction::triggered, view_widget_, &ViewWidget::setRect);

	Action_Ell = new QAction(tr("&Ellipse"), this);
	connect(Action_Ell, &QAction::triggered, view_widget_, &ViewWidget::setEll);

	Action_Pol = new QAction(tr("&Polygon"), this);
	connect(Action_Pol, &QAction::triggered, view_widget_, &ViewWidget::setPol);

	Action_Free = new QAction(tr("&Freehand"), this);
	connect(Action_Free, &QAction::triggered, view_widget_, &ViewWidget::setFree);

	Action_Undo = new QAction(tr("&Undo"), this);
	connect(Action_Undo, &QAction::triggered, view_widget_, &ViewWidget::Undo);
}

void MiniDraw::Creat_ToolBar()
{
	pToolBar = addToolBar(tr("&Main"));	pToolBar->addAction(Action_About);	pToolBar->addAction(Action_Line);	pToolBar->addAction(Action_Rect);
	pToolBar->addAction(Action_Ell);
	pToolBar->addAction(Action_Pol);
	pToolBar->addAction(Action_Free);
	pToolBar->addAction(Action_Undo);
}

void MiniDraw::Creat_Menu()
{
	pMenu = menuBar()->addMenu(tr("&Figure Tool"));	pMenu->addAction(Action_About);	pMenu->addAction(Action_Line);	pMenu->addAction(Action_Rect);
	pMenu->addAction(Action_Ell);
	pMenu->addAction(Action_Pol);
	pMenu->addAction(Action_Free);
	pMenu->addAction(Action_Undo);
}

void MiniDraw::AboutBox()
{
	QMessageBox::about(this, tr("About"), tr("MiniDraw"));
}

MiniDraw::~MiniDraw()
{

}
