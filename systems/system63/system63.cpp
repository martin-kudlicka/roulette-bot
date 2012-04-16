#include "system63.h"

#include "system63settingswidget.h"

const SystemInterface::qfSpinResults System63::AnalyzeSpin(const quint8 &pSpin)
{
	PlayCmn::eBetPosition ebpPosition = GetSpinPosition(pSpin);

	qfSpinResults qfsrResult;
	do {
		if (_tbhLastBet.isEmpty()) {
			// no bet made
			qfsrResult = SpinResultNoBet;

			if (_iSameDozenColumnBeforeBet < _s63sSettings.GetSameDozenColumnBeforeBet()) {
				if (_ebpLastPosition == ebpPosition || _ebpLastPosition == PlayCmn::BetPositionNone) {
					_iSameDozenColumnBeforeBet++;
				} else {
					_iSameDozenColumnBeforeBet = 1;
				} // if else

				break;
			} // if

			if (_iSameDozenColumnProgression < _s63sSettings.GetSameDozenColumnProgression()) {
				if (_s63sSettings.GetProgressionDozenColumnNotChanged()) {
					if (_ebpLastPosition == ebpPosition) {
						_iSameDozenColumnProgression++;
					} else {
						qfsrResult |= SpinResultLost;
						_iSameDozenColumnBeforeBet = 1;
						_iSameDozenColumnProgression = 0;
						_qui8ProgressionIndex = 0;
					} // if else
				} else {
					if (_iSameDozenColumnProgression == 0 || _ebpLastProgressionPosition != ebpPosition) {
						_ebpLastProgressionPosition = ebpPosition;
						_iSameDozenColumnProgression = 1;
					} else {
						_iSameDozenColumnProgression++;
					} // if else
				} // if else

				break;
			} // if
		} else {
			// bet made
			if (_tbhLastBet.contains(ebpPosition)) {
				// won
				qfsrResult = SpinResultWon;

				_iSameDozenColumnBeforeBet = 0;
				_iSameDozenColumnProgression = 0;
				_qui8ProgressionIndex = 0;

				break;
			} else {
				// lost or progression
				_iSameDozenColumnProgression = 0;

				if (_qui8ProgressionIndex == _qlProgressionSequence.size() - 1) {
					qfsrResult = SpinResultLost;

					_iSameDozenColumnBeforeBet = 0;
					_qui8ProgressionIndex = 0;
				} else {
					qfsrResult = SpinResultProgression;

					_qui8ProgressionIndex++;
				} // if else

				break;
			} // if else
		} // if else
	} while (false);

	_iSameInRow++;
	if (_ebpLastPosition != ebpPosition) {
		if (_iMaxSameInRow < _iSameInRow) {
			_s63Statistics.SetMaxSameInRow(_iSameInRow);
			_iMaxSameInRow = _iSameInRow;
		} // if
		if (_iSameInRow < System63StatisticsWidget::CounterMoreSameInRow) {
			_s63Statistics.Increment(static_cast<System63StatisticsWidget::eCounter>(System63StatisticsWidget::Counter1SameInRow + _iSameInRow - 1));
		} else {
			_s63Statistics.Increment(System63StatisticsWidget::CounterMoreSameInRow);
		} // if else
		_iSameInRow = 0;

		_ebpLastPosition = ebpPosition;
	} // if

	return qfsrResult;
} // AnalyzeSpin

const void System63::CloseSettings(const QWidget *pSettings, const bool &pSave) const
{
	const System63SettingsWidget *s63swSettings = qobject_cast<const System63SettingsWidget *>(pSettings);

	if (pSave) {
		s63swSettings->SaveSettings();
	} // if

	delete s63swSettings;
} // CloseSettings

const void System63::CloseStatistics() const
{
	QVBoxLayout *qvbLayout = qobject_cast<QVBoxLayout *>(_s63Statistics.parentWidget()->layout());
	QLayoutItem *qliLayoutItem = qvbLayout->takeAt(0);
	QWidget *qwWidget = qliLayoutItem->widget();
	qwWidget->setParent(NULL);
} // CloseStatistics

const PlayCmn::tBetHash System63::CreateBet() const
{
	PlayCmn::tBetHash tbhBet;

	for (int iBet = 0; iBet < 2; iBet++) {
		do {
			PlayCmn::eBetPosition ebpPosition = static_cast<PlayCmn::eBetPosition>((qrand() % (PlayCmn::BetPositionColumn3 - PlayCmn::BetPositionColumn1 + 1)) + PlayCmn::BetPositionColumn1);
			if ((_s63sSettings.GetBetOn() != System63Settings::BetOnRandom || ebpPosition != _ebpLastPosition) && !tbhBet.contains(ebpPosition)) {
				tbhBet.insert(ebpPosition, _qlProgressionSequence.at(_qui8ProgressionIndex));
				break;
			} // if
		} while (true);
	} // for

	return tbhBet;
} // CreateBet

const PlayCmn::tBetHash System63::GetBet()
{
	_tbhLastBet.clear();

	if (_iSameDozenColumnBeforeBet < _s63sSettings.GetSameDozenColumnBeforeBet()) {
		return _tbhLastBet;
	} // if

	if (_qui8ProgressionIndex > 0 && _iSameDozenColumnProgression < _s63sSettings.GetSameDozenColumnProgression()) {
		return _tbhLastBet;
	} // if

	_tbhLastBet = CreateBet();

	return _tbhLastBet;
} // GetBet

const PlayCmn::eBetPosition System63::GetSpinPosition(const quint8 &pSpin) const
{
	if (pSpin == 0) {
		return PlayCmn::BetPosition0;
	} // if

	if (pSpin == 1 || pSpin == 4 || pSpin == 7 || pSpin == 10 || pSpin == 13 || pSpin == 16 || pSpin == 19 || pSpin == 22 || pSpin == 25 || pSpin == 28 || pSpin == 31 || pSpin == 34) {
		return PlayCmn::BetPositionColumn1;
	} // if

	if (pSpin == 2 || pSpin == 5 || pSpin == 8 || pSpin == 11 || pSpin == 14 || pSpin == 17 || pSpin == 20 || pSpin == 23 || pSpin == 26 || pSpin == 29 || pSpin == 32 || pSpin == 35) {
		return PlayCmn::BetPositionColumn2;
	} // if

	return PlayCmn::BetPositionColumn3;
} // GetBetPosition

const QString System63::GetName() const
{
	return "System 63";
} // GetName

QWidget *System63::GetSettings()
{
	return new System63SettingsWidget(&_s63sSettings);
} // GetSettings

const void System63::OpenStatistics(QVBoxLayout *pLayout)
{
	pLayout->addWidget(&_s63Statistics);
} // OpenStatistics

const void System63::Reset()
{
	_ebpLastPosition = PlayCmn::BetPositionNone;
	_ebpLastProgressionPosition = PlayCmn::BetPositionNone;
	_iMaxSameInRow = 0;
	_iSameDozenColumnBeforeBet = 0;
	_iSameDozenColumnProgression = 0;
	_iSameInRow = 0;

	_qlProgressionSequence.clear();
	QStringList qslProgressionSequence = _s63sSettings.GetProgressionManualSequence().split(PROGRESSION_SEQUENCE_SEPARATOR);
	foreach (QString qsProgression, qslProgressionSequence) {
		_qlProgressionSequence.append(qsProgression.toUInt());
	} // foreach
	_qui8ProgressionIndex = 0;
} // Reset

Q_EXPORT_PLUGIN2(system63, System63)