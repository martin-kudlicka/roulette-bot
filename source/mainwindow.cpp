#include "mainwindow.h"

MainWindow::MainWindow(QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QMainWindow(pParent, pFlags)
{
	_qmwmMainWindow.setupUi(this);

	_cpCasinos.Load();
	_cmCasinos.SetCasinos(&_cpCasinos);
	_qmwmMainWindow.qtvCasinos->setModel(&_cmCasinos);

	connect(_qmwmMainWindow.qtvCasinos->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(on_qtvCasinosSelectionModel_selectionChanged(const QItemSelection &, const QItemSelection &)));
} // MainWindow

const void MainWindow::on_qtvCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
	_qmwmMainWindow.qpbPlay->setEnabled(_qmwmMainWindow.qtvCasinos->selectionModel()->hasSelection());
	_qmwmMainWindow.qpbConfigure->setEnabled(_qmwmMainWindow.qtvCasinos->selectionModel()->hasSelection());
} // on_qtvCasinosSelectionModel_selectionChanged