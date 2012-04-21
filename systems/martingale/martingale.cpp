#include "martingale.h"

#include "martingalesettingswidget.h"

const PlayCmn::qfSpinResults Martingale::AnalyzeSpin(const quint8 &pSpin)
{
	PlayCmn::eBetPosition ebpPosition = GetSpinPosition(pSpin);

	PlayCmn::qfSpinResults qfsrResult;
	do {
		if (_tbhLastBet.isEmpty()) {
			// no bet made
			qfsrResult = PlayCmn::SpinResultNoBet;

			if (_iSameColorBeforeBet < _msSettings.GetSameColorBeforeBet()) {
				if (_ebpLastPosition == ebpPosition || _ebpLastPosition == PlayCmn::BetPositionNone) {
					_iSameColorBeforeBet++;
				} else {
					_iSameColorBeforeBet = 1;
				} // if else

				break;
			} // if

			if (_iSameColorProgression < _msSettings.GetSameColorProgression()) {
				if (_msSettings.GetProgressionColorNotChanged()) {
					if (_ebpLastPosition == ebpPosition) {
						_iSameColorProgression++;
					} else {
						qfsrResult |= PlayCmn::SpinResultLost;
						_iSameColorBeforeBet = 1;
						_iSameColorProgression = 0;
						_qui8ProgressionIndex = 0;
					} // if else
				} else {
					if (_iSameColorProgression == 0 || _ebpLastProgressionPosition != ebpPosition) {
						_ebpLastProgressionPosition = ebpPosition;
						_iSameColorProgression = 1;
					} else {
						_iSameColorProgression++;
					} // if else
				} // if else

				break;
			} // if
		} else {
			// bet made
			if (_tbhLastBet.contains(ebpPosition)) {
				// won
				qfsrResult = PlayCmn::SpinResultWon;

				_iSameColorBeforeBet = 0;
				_iSameColorProgression = 0;
				_qui8ProgressionIndex = 0;

				break;
			} else {
				// lost or progression
				_iSameColorProgression = 0;

				if (_qui8ProgressionIndex == _qlProgressionSequence.size() - 1) {
					qfsrResult = PlayCmn::SpinResultLost;

					_iSameColorBeforeBet = 0;
					_qui8ProgressionIndex = 0;
				} else {
					qfsrResult = PlayCmn::SpinResultProgression;

					_qui8ProgressionIndex++;
				} // if else

				break;
			} // if else
		} // if else
	} while (false);

	_iSameInRow++;
	if (_ebpLastPosition != ebpPosition) {
		if (_iMaxSameInRow < _iSameInRow) {
			_mswStatistics.SetMaxSameInRow(_iSameInRow);
			_iMaxSameInRow = _iSameInRow;
		} // if
		if (_iSameInRow < MartingaleStatisticsWidget::CounterMoreSameInRow) {
			_mswStatistics.Increment(static_cast<MartingaleStatisticsWidget::eCounter>(MartingaleStatisticsWidget::Counter1SameInRow + _iSameInRow - 1));
		} else {
			_mswStatistics.Increment(MartingaleStatisticsWidget::CounterMoreSameInRow);
		} // if else
		_iSameInRow = 0;

		_ebpLastPosition = ebpPosition;
	} // if else

	return qfsrResult;
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
		if (_ebpLastPosition == PlayCmn::BetPositionColorBlack) {
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

	if (_iSameColorBeforeBet < _msSettings.GetSameColorBeforeBet()) {
		return _tbhLastBet;
	} // if

	if (_qui8ProgressionIndex > 0 && _iSameColorProgression < _msSettings.GetSameColorProgression()) {
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

const PlayCmn::eBetPosition Martingale::GetSpinPosition(const quint8 &pSpin) const
{
	if (pSpin == 0) {
		return PlayCmn::BetPosition0;
	} // if

	if (pSpin == 2 || pSpin == 4 || pSpin == 6 || pSpin == 8 || pSpin == 10 || pSpin == 11 || pSpin == 13 || pSpin == 15 || pSpin == 17 || pSpin == 20 || pSpin == 22 || pSpin == 24 || pSpin == 26 || pSpin == 28 || pSpin == 29 || pSpin == 31 || pSpin == 33 || pSpin == 35) {
		return PlayCmn::BetPositionColorBlack;
	} // if

	return PlayCmn::BetPositionColorRed;
} // GetSpinPosition

const void Martingale::OpenStatistics(QVBoxLayout *pLayout)
{
	pLayout->insertWidget(0, &_mswStatistics);
} // OpenStatistics

const void Martingale::Reset(const qfResetContents &pResetContents)
{
	if (pResetContents & ResetContentCore) {
		_ebpLastPosition = PlayCmn::BetPositionNone;
		_ebpLastProgressionPosition = PlayCmn::BetPositionNone;
		_iMaxSameInRow = 0;
		_iSameColorBeforeBet = 0;
		_iSameColorProgression = 0;
		_iSameInRow = 0;

		_qlProgressionSequence.clear();
		QStringList qslProgressionSequence = _msSettings.GetProgressionManualSequence().split(PROGRESSION_SEQUENCE_SEPARATOR);
		foreach (QString qsProgression, qslProgressionSequence) {
			_qlProgressionSequence.append(qsProgression.toUInt());
		} // foreach
		_qui8ProgressionIndex = 0;
	} // if

	if (pResetContents & ResetContentStatistics) {
		_iMaxSameInRow;
		_mswStatistics.Reset();
	} // if
} // Reset

Q_EXPORT_PLUGIN2(martingale, Martingale)