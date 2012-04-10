#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "casinomodel.h"
#include "casinodialog.h"
#include "settings.h"
#include "systemplugins.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		CasinoModel _cmCasinos;
		CasinoPlugins _cpCasinos;
		QHash<int, CasinoDialog *> _qhOpenedCasinos;
		Settings _sSettings;
		SystemPlugins _spSystems;
		Ui::qmwMain _qmwmMainWindow;

	private slots:
		const void on_cdCasinoDialog_finished(int result);
		const void on_cmCasinos_ActiveChanged(const int &pRow, const bool &pActive) const;
		const void on_qaSettings_triggered(bool checked = false);
		const void on_qpbPlay_clicked(bool checked = false);
		const void on_qtvCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
}; // MainWindow

#endif // MAINWINDOW_H