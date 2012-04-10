#include "casinodialog.h"

CasinoDialog::CasinoDialog(const CasinoInterface *pCasino, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QDialog(pParent, pFlags)
{
	_ciCasino = pCasino;

	_qdcCasinoDialog.setupUi(this);

	setWindowTitle(windowTitle() += pCasino->GetName());

	RefreshStatus();

	connect(pCasino, SIGNAL(GameActiveChanged(const bool &)), SLOT(on_ciCasino_GameActiveChanged(const bool &)));
} // CasinoDialog

const bool CasinoDialog::IsPlaying() const
{
	return !_qdcCasinoDialog.qpbStart->isEnabled();
} // IsPlaying

const void CasinoDialog::on_ciCasino_GameActiveChanged(const bool &pActive) const
{
	if (pActive) {
		if (!IsPlaying()) {
			_qdcCasinoDialog.qpbStart->setEnabled(true);
		} // if
	} else {
		if (IsPlaying()) {
			on_qpbStop_clicked();
		} // if
	} // if else
} // on_ciCasino_GameActiveChanged

const void CasinoDialog::on_qpbStart_clicked(bool checked /* false */) const
{
	_qdcCasinoDialog.qpbStart->setEnabled(false);
	_qdcCasinoDialog.qpbStop->setEnabled(true);
} // on_qpbStart_clicked

const void CasinoDialog::on_qpbStop_clicked(bool checked /* false */) const
{
	_qdcCasinoDialog.qpbStop->setEnabled(false);
	_qdcCasinoDialog.qpbStart->setEnabled(_ciCasino->GameActive());
} // on_qpbStop_clicked

const void CasinoDialog::RefreshStatus() const
{
	_qdcCasinoDialog.qlCash->setText(QString::number(_ciCasino->GetCash()));
} // RefreshStatus