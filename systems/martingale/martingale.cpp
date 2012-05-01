#include "martingale.h"

#include "martingalesettingswidget.h"

const PlayCmn::sSpinResult Martingale::AnalyzeSpin(const quint8 &pSpin)
{
	PlayCmn::qfBetPositions qfbpPosition = GetSpinPosition(pSpin);
	qfbpPosition &= PlayCmn::BetPositionColorBlack | PlayCmn::BetPositionColorRed;

	PlayCmn::sSpinResult srResult;
	do {
		if (_tbhLastBet.isEmpty()) {
			// no bet made
			srResult.esrtType = PlayCmn::SpinResultTypeNoBet;
			srResult.qui8BetProfit = 0;

			if (_qui8SameColorBeforeBet < _msSettings.GetSameColorBeforeBet()) {
				if (_qfbpLastPosition & qfbpPosition || _qfbpLastPosition == PlayCmn::BetPositionNone) {
					_qui8SameColorBeforeBet++;
				} else {
					_qui8SameColorBeforeBet = 1;
				} // if else

				break;
			} // if

			if (_qui8SameColorProgression < _msSettings.GetSameColorProgression()) {
				if (_msSettings.GetProgressionColorNotChanged()) {
					if (_qfbpLastPosition & qfbpPosition) {
						_qui8SameColorProgression++;
					} else {
						srResult.esrtType |= PlayCmn::SpinResultTypeLost;
						_qui8SameColorBeforeBet = 1;
						_qui8SameColorProgression = 0;
						_qui8ProgressionIndex = 0;
					} // if else
				} else {
					if (_qui8SameColorProgression == 0 || !(_qfbpLastProgressionPosition & qfbpPosition)) {
						_qfbpLastProgressionPosition = qfbpPosition;
						_qui8SameColorProgression = 1;
					} else {
						_qui8SameColorProgression++;
					} // if else
				} // if else

				break;
			} // if
		} else {
			// bet made
			if (LastBetContains(qfbpPosition)) {
				// won
				srResult.esrtType = PlayCmn::SpinResultTypeWon;
				srResult.qui8BetProfit = LastBetValue(qfbpPosition) * 2;

				_qui8SameColorBeforeBet = 0;
				_qui8SameColorProgression = 0;
				_qui8ProgressionIndex = 0;

				break;
			} else {
				// lost or progression
				_qui8SameColorProgression = 0;

				if (_qui8ProgressionIndex == _qlProgressionSequence.size() - 1) {
					srResult.esrtType = PlayCmn::SpinResultTypeLost;

					_qui8SameColorBeforeBet = 0;
					_qui8ProgressionIndex = 0;
				} else {
					srResult.esrtType = PlayCmn::SpinResultTypeProgression;

					_qui8ProgressionIndex++;
				} // if else
				srResult.qui8BetProfit = 0;

				break;
			} // if else
		} // if else
	} while (false);

	_qui8SameInRow++;
	if (!(_qfbpLastPosition & qfbpPosition)) {
		if (_qui8MaxSameInRow < _qui8SameInRow) {
			_mswStatistics.SetMaxSameInRow(_qui8SameInRow);
			_qui8MaxSameInRow = _qui8SameInRow;
		} // if
		if (_qui8SameInRow < MartingaleStatisticsWidget::CounterMoreSameInRow) {
			_mswStatistics.Increment(static_cast<MartingaleStatisticsWidget::eCounter>(MartingaleStatisticsWidget::Counter1SameInRow + _qui8SameInRow - 1));
		} else {
			_mswStatistics.Increment(MartingaleStatisticsWidget::CounterMoreSameInRow);
		} // if else
		_qui8SameInRow = 0;

		_qfbpLastPosition = qfbpPosition;
	} // if else

	return srResult;
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
		if (_qfbpLastPosition == PlayCmn::BetPositionColorBlack) {
			ebpPosition = PlayCmn::BetPositionColorRed;
		} else {
			ebpPosition = PlayCmn::BetPositionColorBlack;
		} // if else
	} // if else
	tbhBet.insert(ebpPosition, _qlProgressionSequence.at(_qui8ProgressionIndex));

	return tbhBet;
} // CreateBet

const PlayCmn::tBetHash Martingale::GetBet()
{
	_tbhLastBet.clear();

	if (_qui8SameColorBeforeBet < _msSettings.GetSameColorBeforeBet()) {
		return _tbhLastBet;
	} // if

	if (_qui8ProgressionIndex > 0 && _qui8SameColorProgression < _msSettings.GetSameColorProgression()) {
		return _tbhLastBet;
	} // if

	_tbhLastBet = CreateBet();

	return _tbhLastBet;
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
	pLayout->insertWidget(0, &_mswStatistics);
} // OpenStatistics

const void Martingale::Reset(const qfResetContents &pResetContents)
{
	if (pResetContents & ResetContentCore) {
		_qfbpLastPosition = PlayCmn::BetPositionNone;
		_qfbpLastProgressionPosition = PlayCmn::BetPositionNone;
		_qui8MaxSameInRow = 0;
		_qui8SameColorBeforeBet = 0;
		_qui8SameColorProgression = 0;
		_qui8SameInRow = 0;

		_qlProgressionSequence.clear();
		QStringList qslProgressionSequence = _msSettings.GetProgressionManualSequence().split(PROGRESSION_SEQUENCE_SEPARATOR);
		foreach (QString qsProgression, qslProgressionSequence) {
			_qlProgressionSequence.append(qsProgression.toUInt());
		} // foreach
		_qui8ProgressionIndex = 0;
	} // if

	if (pResetContents & ResetContentStatistics) {
		_qui8MaxSameInRow;
		_mswStatistics.Reset();
	} // if
} // Reset

Q_EXPORT_PLUGIN2(martingale, Martingale)