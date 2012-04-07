#include "mainwindow.h"

MainWindow::MainWindow(QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QMainWindow(pParent, pFlags), _cmCasinos(&_cpCasinos)
{
	_qmwmMainWindow.setupUi(this);

	_cpCasinos.Load();
	_qmwmMainWindow.qtvCasinos->setModel(&_cmCasinos);
} // MainWindow