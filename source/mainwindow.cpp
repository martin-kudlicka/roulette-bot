#include "mainwindow.h"

MainWindow::MainWindow(QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QMainWindow(pParent, pFlags)
{
	_qmwmMainWindow.setupUi(this);

	_cpCasinos.Load();
	_cmCasinos.SetCasinos(&_cpCasinos);
	_qmwmMainWindow.qtvCasinos->setModel(&_cmCasinos);

	connect(&_cmCasinos, SIGNAL(ActiveChanged(const int &, const bool &)), SLOT(on_cmCasinos_ActiveChanged(const int &, const bool &)));
	connect(_qmwmMainWindow.qtvCasinos->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(on_qtvCasinosSelectionModel_selectionChanged(const QItemSelection &, const QItemSelection &)));
} // MainWindow

const void MainWindow::on_cmCasinos_ActiveChanged(const int &pRow, const bool &pActive) const
{
	if (_qmwmMainWindow.qtvCasinos->selectionModel()->hasSelection() && _qmwmMainWindow.qtvCasinos->currentIndex().row() == pRow) {
		_qmwmMainWindow.qpbPlay->setEnabled(pActive);
	} // if
} // on_cmCasinos_ActiveChanged

const void MainWindow::on_qtvCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
	const CasinoInterface *ciCasino = _cpCasinos.GetCasino(_qmwmMainWindow.qtvCasinos->currentIndex().row());

	_qmwmMainWindow.qpbPlay->setEnabled(_qmwmMainWindow.qtvCasinos->selectionModel()->hasSelection() && ciCasino->GameActive());
	_qmwmMainWindow.qpbConfigure->setEnabled(_qmwmMainWindow.qtvCasinos->selectionModel()->hasSelection());
} // on_qtvCasinosSelectionModel_selectionChanged