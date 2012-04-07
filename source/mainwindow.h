#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

#include "casinomodel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		CasinoModel _cmCasinos;
		CasinoPlugins _cpCasinos;
		Ui::qmwMain _qmwmMainWindow;
}; // MainWindow

#endif // MAINWINDOW_H
