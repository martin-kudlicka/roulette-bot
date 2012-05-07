#include "casinodialog.h"

CasinoDialog::~CasinoDialog()
{
	if (_siSystem) {
		_siSystem->CloseStatistics();
	} // if
} // ~CasinoDialog

CasinoDialog::CasinoDialog(CasinoInterface *pCasino, const SystemPlugins *pSystems, Settings *pSettings, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QDialog(pParent, pFlags)
{
	_bStop = true;
	_ciCasino = pCasino;
	_siSystem = NULL;
	_spSystems = pSystems;
	_sSettings = pSettings;

	_qdcCasinoDialog.setupUi(this);

	setWindowTitle(windowTitle() += pCasino->GetName());

	on_qpbResetStatus_clicked();
	InitSettings();

	connect(pCasino, SIGNAL(GameActiveChanged(const bool &)), SLOT(on_ciCasino_GameActiveChanged(const bool &)));
} // CasinoDialog

const void CasinoDialog::IncreaseCounter(QLabel *pCounter) const
{
	quint16 qui16Count = pCounter->text().toUInt() + 1;
	pCounter->setText(QString::number(qui16Count));
} // IncreaseCounter

const void CasinoDialog::IncreaseProgressionCounter(const quint8 &pProgression) const
{
	switch (pProgression) {
		case 1:
			IncreaseCounter(_qdcCasinoDialog.ql1Progression);
			break;
		case 2:
			IncreaseCounter(_qdcCasinoDialog.ql2Progression);
			break;
		case 3:
			IncreaseCounter(_qdcCasinoDialog.ql3Progression);
			break;
		case 4:
			IncreaseCounter(_qdcCasinoDialog.ql4Progression);
			break;
		case 5:
			IncreaseCounter(_qdcCasinoDialog.ql5Progression);
			break;
		case 6:
			IncreaseCounter(_qdcCasinoDialog.ql6Progression);
			break;
		default:
			IncreaseCounter(_qdcCasinoDialog.qlMoreProgression);
	} // switch
} // IncreaseProgressionCounter

const void CasinoDialog::InitSettings() const
{
	for (quint8 qui8System = 0; qui8System < _spSystems->GetCount(); qui8System++) {
		const SystemInterface *siSystem = _spSystems->GetSystem(qui8System);
		_qdcCasinoDialog.qcbSystems->addItem(siSystem->GetName(), reinterpret_cast<quintptr>(siSystem));
	} // for
} // InitSettings

const bool CasinoDialog::IsPlaying() const
{
	return !_bStop;
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
		} else {
			_qdcCasinoDialog.qpbStart->setEnabled(false);
		} // if else
	} // if else
} // on_ciCasino_GameActiveChanged

const void CasinoDialog::on_qcbSystems_currentIndexChanged(int index)
{
	if (_siSystem) {
		_siSystem->CloseStatistics();
	} // if

	_siSystem = reinterpret_cast<SystemInterface *>(_qdcCasinoDialog.qcbSystems->itemData(index).toUInt());
	_siSystem->OpenStatistics(qobject_cast<QVBoxLayout *>(_qdcCasinoDialog.qgbCasinoStatistics->layout()));
} // on_qcbSystems_currentIndexChanged

const void CasinoDialog::on_qpbResetStatistics_clicked(bool checked /* false */) const
{
	_siSystem->Reset(SystemInterface::ResetContentStatistics);
} // on_qpbResetStatistics_clicked

const void CasinoDialog::on_qpbResetStatus_clicked(bool checked /* false */)
{
	_fStartingCash = _ciCasino->GetCash();
	_qtPlayTime.start();

	_qdcCasinoDialog.qlWon->setText("0");
	_qdcCasinoDialog.qlLost->setText("0");
	_qdcCasinoDialog.qlProgression->setText("0");
	_qdcCasinoDialog.qlNoBet->setText("0");

	_qdcCasinoDialog.qlInProgression->setText("0");
	_qdcCasinoDialog.qlMaxProgression->setText("0");

	_qdcCasinoDialog.ql1Progression->setText("0");
	_qdcCasinoDialog.ql2Progression->setText("0");
	_qdcCasinoDialog.ql3Progression->setText("0");
	_qdcCasinoDialog.ql4Progression->setText("0");
	_qdcCasinoDialog.ql5Progression->setText("0");
	_qdcCasinoDialog.ql6Progression->setText("0");
	_qdcCasinoDialog.qlMoreProgression->setText("0");

	RefreshStatus();
} // on_qpbResetStatus_clicked

const void CasinoDialog::on_qpbStart_clicked(bool checked /* false */)
{
	_qdcCasinoDialog.qgbSettings->setEnabled(false);
	_qdcCasinoDialog.qpbStart->setEnabled(false);
	_qdcCasinoDialog.qpbStop->setEnabled(true);

	_qdcCasinoDialog.qpteLog->appendPlainText(tr("Game started."));

	_ciCasino->Reset();
	_siSystem->Reset(SystemInterface::ResetContentCore);
	_qui8MaxProgression = 0;

	_bStop = false;
	while (!_bStop) {
		PlayRound();

		if (_sSettings->GetMaxWinToPlayEnabled() && _qdcCasinoDialog.qlCash->text().toFloat() - _fStartingCash >= _sSettings->GetMaxWinToPlay()) {
			_qdcCasinoDialog.qpteLog->appendPlainText(tr("Maximum win reached."));
			_bStop = true;
		} else {
			if (_sSettings->GetMaxLossToPlayEnabled() && _fStartingCash - _qdcCasinoDialog.qlCash->text().toFloat() >= _sSettings->GetMaxLossToPlay()) {
				_qdcCasinoDialog.qpteLog->appendPlainText(tr("Maximum lost reached."));
				_bStop = true;
			} // if
		} // if else

		if (_sSettings->GetMaxPlayTimeEnabled() && _qdcCasinoDialog.qlInProgression->text().toUInt() == 0) {
			QTime qtElapsed = QTime().addMSecs(_qtPlayTime.elapsed());
			if (qtElapsed > _sSettings->GetMaxPlayTime()) {
				_qdcCasinoDialog.qpteLog->appendPlainText(tr("Maximum play time reached."));
				_bStop = true;
			} // if
		} // if

		QCoreApplication::processEvents(QEventLoop::ExcludeSocketNotifiers);
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

const void CasinoDialog::PlayRound()
{
	// make bet
	PlayCmn::tBetHash tbhBet = _siSystem->GetBet();
	if (_qdcCasinoDialog.qcbPlayForMoney->isChecked() && !tbhBet.isEmpty()) {
		_ciCasino->MakeBet(tbhBet, _sSettings->GetTokensPerBet());
	} // if

	if (_bStop) {
		return;
	} // if

	// make spin
	_qdcCasinoDialog.qpteLog->appendPlainText(tr("Spin: "));
	quint8 qui8Spin = _ciCasino->MakeSpin();
	_qdcCasinoDialog.qpteLog->insertPlainText(QString("%1.").arg(qui8Spin));

	// analyze spin in system
	PlayCmn::sSpinResult srResult = _siSystem->AnalyzeSpin(qui8Spin);

	// process spin result for GUI
	if (srResult.esrtType & PlayCmn::SpinResultTypeNoBet) {
		_qdcCasinoDialog.qpteLog->appendPlainText(tr("No bet."));
		IncreaseCounter(_qdcCasinoDialog.qlNoBet);
	} // if
	if (srResult.esrtType & PlayCmn::SpinResultTypeWon) {
		_qdcCasinoDialog.qpteLog->appendPlainText(tr("Won"));
		if (_qdcCasinoDialog.qcbPlayForMoney->isChecked()) {
			_qdcCasinoDialog.qpteLog->insertPlainText(" ");
		} else {
			_qdcCasinoDialog.qpteLog->insertPlainText(".");
		} // if else
		IncreaseCounter(_qdcCasinoDialog.qlWon);
	} // if
	if (srResult.esrtType & PlayCmn::SpinResultTypeLost) {
		_qdcCasinoDialog.qpteLog->appendPlainText(tr("Lost"));
		if (_qdcCasinoDialog.qcbPlayForMoney->isChecked() || srResult.esrtType & PlayCmn::SpinResultTypeNoBet) {
			_qdcCasinoDialog.qpteLog->insertPlainText(" ");
		} else {
			_qdcCasinoDialog.qpteLog->insertPlainText(".");
		} // if else
		IncreaseCounter(_qdcCasinoDialog.qlLost);

		if (srResult.esrtType & PlayCmn::SpinResultTypeNoBet) {
			_qdcCasinoDialog.qpteLog->insertPlainText(tr("before."));
		} // if

		if (_sSettings->GetStopOnLoss()) {
			_bStop = true;
		} // if
	} // if
	if (srResult.esrtType & PlayCmn::SpinResultTypeProgression) {
		_qdcCasinoDialog.qpteLog->appendPlainText(tr("Progression"));
		if (_qdcCasinoDialog.qcbPlayForMoney->isChecked()) {
			_qdcCasinoDialog.qpteLog->insertPlainText(" ");
		} else {
			_qdcCasinoDialog.qpteLog->insertPlainText(".");
		} // if else
		IncreaseCounter(_qdcCasinoDialog.qlProgression);
	} // if
	if (srResult.esrtType == PlayCmn::SpinResultTypeNoBet) {
		_qdcCasinoDialog.qlInProgression->setText(QString::number(_qui8MaxProgression));
	} else {
		_qui8MaxProgression++;
		_qdcCasinoDialog.qlInProgression->setText(QString::number(_qui8MaxProgression));
		if (_qdcCasinoDialog.qlMaxProgression->text().toUInt() < _qui8MaxProgression) {
			_qdcCasinoDialog.qlMaxProgression->setText(QString::number(_qui8MaxProgression));
		} // if

		if (srResult.esrtType & (PlayCmn::SpinResultTypeWon | srResult.esrtType & PlayCmn::SpinResultTypeLost)) {
			if (srResult.esrtType & PlayCmn::SpinResultTypeLost) {
				// increase to signalize win could be in higher progression
				_qui8MaxProgression++;
			} // if
			IncreaseProgressionCounter(_qui8MaxProgression);
			_qui8MaxProgression = 0;
		} // if
	} // if

	// process spin result for casino
	if (_qdcCasinoDialog.qcbPlayForMoney->isChecked() && !tbhBet.isEmpty()) {
		_ciCasino->ProcessSpinResult(srResult, _sSettings->GetTokensPerBet());
	} // if

	// remove remaining bet
	if (_qdcCasinoDialog.qcbPlayForMoney->isChecked() && !tbhBet.isEmpty()) {
		_ciCasino->RemoveBet();
	} // if

	// analyze profit
	if (_qdcCasinoDialog.qcbPlayForMoney->isChecked() && !tbhBet.isEmpty()) {
		float fOldCash = _qdcCasinoDialog.qlCash->text().toFloat();
		RefreshStatus();

		float fProfit = qAbs(_qdcCasinoDialog.qlCash->text().toFloat() - fOldCash);
		if (fProfit > 0) {
			_qdcCasinoDialog.qpteLog->insertPlainText(QString("%1.").arg(fProfit));
		} // if
	} // if

	_qdcCasinoDialog.qpteLog->appendPlainText(tr("End of round."));
} // PlayRound

const void CasinoDialog::RefreshStatus() const
{
	float fCash = _ciCasino->GetCash();

	_qdcCasinoDialog.qlCash->setText(QString::number(fCash));
	_qdcCasinoDialog.qlProfit->setText(QString::number(fCash - _fStartingCash));
	_qdcCasinoDialog.qlPlayTime->setText(QTime().addMSecs(_qtPlayTime.elapsed()).toString());
} // RefreshStatus