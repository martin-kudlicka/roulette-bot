#include "martingale.h"

#include "martingalesettingswidget.h"

const SystemInterface::qfSpinResults Martingale::AnalyzeSpin(const quint8 &pSpin)
{
	// TODO
	return SystemInterface::SpinResultNoBet;
} // AnalyzeSpin

const void Martingale::CloseSettings(const QWidget *pSettings, const bool &pSave) const
{
	const MartingaleSettingsWidget *mswSettings = qobject_cast<const MartingaleSettingsWidget *>(pSettings);

	if (pSave) {
		mswSettings->SaveSettings();
	} // if

	delete mswSettings;
} // CloseSettings

const void Martingale::CloseStatistics() const
{
	QVBoxLayout *qvbLayout = qobject_cast<QVBoxLayout *>(_mswStatistics.parentWidget()->layout());
	QLayoutItem *qliLayoutItem = qvbLayout->takeAt(0);
	QWidget *qwWidget = qliLayoutItem->widget();
	qwWidget->setParent(NULL);
} // CloseStatistics

const PlayCmn::tBetHash Martingale::CreateBet() const
{
	PlayCmn::tBetHash tbhBet;

	PlayCmn::eBetPosition ebpPosition;
	if (_msSettings.GetBetStyle() == MartingaleSettings::BetStyleRandom) {
		ebpPosition = static_cast<PlayCmn::eBetPosition>((qrand() % (PlayCmn::BetPositionColorRed - PlayCmn::BetPositionColorBlack + 1)) + PlayCmn::BetPositionColorBlack);
	} else {
		if (_qui8ProgressionIndex == 0) {
			if (_ebpLastPosition == PlayCmn::BetPositionColorBlack) {
				ebpPosition = PlayCmn::BetPositionColorRed;
			} else {
				ebpPosition = PlayCmn::BetPositionColorBlack;
			} // if else
		} else {
			ebpPosition = _ebpLastPosition;
		} // if else
	} // if else
	tbhBet.insert(ebpPosition, _qlProgressionSequence.at(_qui8ProgressionIndex));

	return tbhBet;
} // CreateBet

const PlayCmn::tBetHash Martingale::GetBet()
{
	if (_iSameColorBeforeBet < _msSettings.GetSameColorBeforeBet()) {
		return PlayCmn::tBetHash();
	} // if

	if (_qui8ProgressionIndex > 0 && _iSameColorProgression < _msSettings.GetSameColorProgression()) {
		return PlayCmn::tBetHash();
	} // if

	return CreateBet();
} // GetBet

const QString Martingale::GetName() const
{
	return "Martingale";
} // GetName

QWidget *Martingale::GetSettings()
{
	return new MartingaleSettingsWidget(&_msSettings);
} // GetSettings

const void Martingale::OpenStatistics(QVBoxLayout *pLayout)
{
	pLayout->addWidget(&_mswStatistics);
} // OpenStatistics

const void Martingale::Reset()
{
	_ebpLastPosition = PlayCmn::BetPositionNone;
	_ebpLastProgressionPosition = PlayCmn::BetPositionNone;
	_iSameColorBeforeBet = 0;
	_iSameColorProgression = 0;

	_qlProgressionSequence.clear();
	QStringList qslProgressionSequence = _msSettings.GetProgressionManualSequence().split(PROGRESSION_SEQUENCE_SEPARATOR);
	foreach (QString qsProgression, qslProgressionSequence) {
		_qlProgressionSequence.append(qsProgression.toUInt());
	} // foreach
	_qui8ProgressionIndex = 0;
} // Reset

Q_EXPORT_PLUGIN2(martingale, Martingale)