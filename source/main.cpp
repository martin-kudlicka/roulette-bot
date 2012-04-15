#include "mainwindow.h"
#include <QtCore/QTime>

int main(int argc, char *argv[])
{
	QApplication qaApplication(argc, argv);
	MainWindow mwMainWindow;

	qsrand(QTime::currentTime().msec());

	mwMainWindow.show();
	return qaApplication.exec();
} // main