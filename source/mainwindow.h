#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

#include "casinomodel.h"
#include "casinodialog.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		CasinoModel _cmCasinos;
		CasinoPlugins _cpCasinos;
		QHash<int, CasinoDialog *> _qhOpenedCasinos;
		Ui::qmwMain _qmwmMainWindow;

	private slots:
		const void on_cdCasinoDialog_finished(int result);
		const void on_cmCasinos_ActiveChanged(const int &pRow, const bool &pActive) const;
		const void on_qpbPlay_clicked(bool checked = false);
		const void on_qtvCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
}; // MainWindow

#endif // MAINWINDOW_H
