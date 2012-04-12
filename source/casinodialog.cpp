#include "casinodialog.h"

CasinoDialog::CasinoDialog(CasinoInterface *pCasino, const SystemPlugins *pSystems, Settings *pSettings, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QDialog(pParent, pFlags)
{
	_ciCasino = pCasino;
	_spSystems = pSystems;
	_sSettings = pSettings;

	_qdcCasinoDialog.setupUi(this);

	setWindowTitle(windowTitle() += pCasino->GetName());

	RefreshStatus();
	InitSettings();

	connect(pCasino, SIGNAL(GameActiveChanged(const bool &)), SLOT(on_ciCasino_GameActiveChanged(const bool &)));
} // CasinoDialog

const void CasinoDialog::InitSettings() const
{
	for (int iSystem = 0; iSystem < _spSystems->GetCount(); iSystem++) {
		const SystemInterface *siSystem = _spSystems->GetSystem(iSystem);
		_qdcCasinoDialog.qcbSystems->addItem(siSystem->GetName(), reinterpret_cast<unsigned int>(siSystem));
	} // for
} // InitSettings

const bool CasinoDialog::IsPlaying() const
{
	return !_qdcCasinoDialog.qpbStart->isEnabled();
} // IsPlaying

const void CasinoDialog::on_ciCasino_GameActiveChanged(const bool &pActive)
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

const void CasinoDialog::on_qpbStart_clicked(bool checked /* false */)
{
	_qdcCasinoDialog.qgbSettings->setEnabled(false);
	_qdcCasinoDialog.qpbStart->setEnabled(false);
	_qdcCasinoDialog.qpbStop->setEnabled(true);

	SystemInterface *siSystem = reinterpret_cast<SystemInterface *>(_qdcCasinoDialog.qcbSystems->itemData(_qdcCasinoDialog.qcbSystems->currentIndex()).toUInt());

	_qdcCasinoDialog.qpteLog->appendPlainText(tr("Game started."));

	_ciCasino->Reset();
	siSystem->Reset();

	_bStop = false;
	while (!_bStop) {
		PlayRound(siSystem);
	} // while

	_qdcCasinoDialog.qpteLog->appendPlainText(tr("Game stopped."));
	_qdcCasinoDialog.qpteLog->appendPlainText("");

	_qdcCasinoDialog.qpbStop->setEnabled(false);
	_qdcCasinoDialog.qpbStart->setEnabled(_ciCasino->GameActive());
	_qdcCasinoDialog.qgbSettings->setEnabled(true);
} // on_qpbStart_clicked

const void CasinoDialog::on_qpbStop_clicked(bool checked /* false */)
{
	_bStop = true;
} // on_qpbStop_clicked

const void CasinoDialog::PlayRound(SystemInterface *pSystem) const
{
	PlayCmn::tBetHash tbhBet = pSystem->GetBet();
	//_ciCasino->MakeBet(tbhBet, _sSettings->GetTokensPerBet());

	_qdcCasinoDialog.qpteLog->appendPlainText(tr("Spin: "));
	quint8 qui8Spin = _ciCasino->MakeSpin();
	_qdcCasinoDialog.qpteLog->insertPlainText(QString("%1.").arg(qui8Spin));

	SystemInterface::eSpinResult esrResult = pSystem->AnalyzeSpin(qui8Spin);
	switch (esrResult) {
		case SystemInterface::SpinResultNoBet:
			_qdcCasinoDialog.qpteLog->appendPlainText(tr("No bet."));
			break;
		case SystemInterface::SpinResultWon:
			_qdcCasinoDialog.qpteLog->appendPlainText(tr("Won "));
			break;
		case SystemInterface::SpinResultLost:
			_qdcCasinoDialog.qpteLog->appendPlainText(tr("Lost "));
	} // switch

	_ciCasino->RemoveBet();

	float fOldCash = _qdcCasinoDialog.qlCash->text().toFloat();
	RefreshStatus();

	switch (esrResult) {
		case SystemInterface::SpinResultWon:
		case SystemInterface::SpinResultLost:
			float fCash = _qdcCasinoDialog.qlCash->text().toFloat();
			_qdcCasinoDialog.qpteLog->insertPlainText(QString("%1.").arg(qAbs(fCash - fOldCash)));
	} // switch

	_qdcCasinoDialog.qpteLog->appendPlainText(tr("End of round."));
} // PlayRound

const void CasinoDialog::RefreshStatus() const
{
	_qdcCasinoDialog.qlCash->setText(QString::number(_ciCasino->GetCash()));
} // RefreshStatus