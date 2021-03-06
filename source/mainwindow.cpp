#include "mainwindow.h"

#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QMainWindow(pParent, pFlags)
{
	_qmwmMainWindow.setupUi(this);

	_cpCasinos.Load();
	_cmCasinos.SetCasinos(&_cpCasinos);
	_qmwmMainWindow.qtvCasinos->setModel(&_cmCasinos);

	_spSystems.Load();

	connect(&_cmCasinos, SIGNAL(ActiveChanged(const quint8 &, const bool &)), SLOT(on_cmCasinos_ActiveChanged(const quint8 &, const bool &)));
	connect(_qmwmMainWindow.qtvCasinos->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(on_qtvCasinosSelectionModel_selectionChanged(const QItemSelection &, const QItemSelection &)));
} // MainWindow

const void MainWindow::on_cdCasinoDialog_finished(int result)
{
	CasinoDialog *cdCasino = qobject_cast<CasinoDialog *>(sender());
	quint8 qui8Row = _qhOpenedCasinos.key(cdCasino);
	_qhOpenedCasinos.remove(qui8Row);
	cdCasino->deleteLater();
} // on_cdCasinoDialog_finished

const void MainWindow::on_cmCasinos_ActiveChanged(const quint8 &pRow, const bool &pActive) const
{
	if (_qmwmMainWindow.qtvCasinos->selectionModel()->hasSelection() && _qmwmMainWindow.qtvCasinos->currentIndex().row() == pRow) {
		_qmwmMainWindow.qpbPlay->setEnabled(pActive);
	} // if
} // on_cmCasinos_ActiveChanged

const void MainWindow::on_qaSettings_triggered(bool checked /* false */)
{
	SettingsDialog sdSettings(&_sSettings, &_cpCasinos, &_spSystems, this);
	sdSettings.exec();
} // on_qaSettings_triggered

const void MainWindow::on_qpbPlay_clicked(bool checked /* false */)
{
	quint8 qui8Row = _qmwmMainWindow.qtvCasinos->currentIndex().row();

	CasinoDialog *cdCasino;
	if (_qhOpenedCasinos.contains(qui8Row)) {
		cdCasino = _qhOpenedCasinos.value(qui8Row);
		cdCasino->raise();
	} else {
		CasinoInterface *ciCasino = _cpCasinos.GetCasino(qui8Row);
		cdCasino = new CasinoDialog(ciCasino, &_spSystems, &_sSettings, this);

		connect(cdCasino, SIGNAL(finished(int)), SLOT(on_cdCasinoDialog_finished(int)));

		_qhOpenedCasinos.insert(qui8Row, cdCasino);

		cdCasino->show();
	} // if else
} // on_qpbPlay_clicked

const void MainWindow::on_qtvCasinos_doubleClicked(const QModelIndex &index)
{
	if (_qmwmMainWindow.qpbPlay->isEnabled()) {
		on_qpbPlay_clicked();
	} // if
} // on_qtvCasinos_doubleClicked

const void MainWindow::on_qtvCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
	const CasinoInterface *ciCasino = _cpCasinos.GetCasino(_qmwmMainWindow.qtvCasinos->currentIndex().row());

	_qmwmMainWindow.qpbPlay->setEnabled(_qmwmMainWindow.qtvCasinos->selectionModel()->hasSelection() && ciCasino->GameActive());
} // on_qtvCasinosSelectionModel_selectionChanged