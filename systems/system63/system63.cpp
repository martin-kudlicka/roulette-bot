#include "system63.h"

#include "system63settingswidget.h"

const void System63::AnalyzeSpin(const quint8 &pSpin)
{
	do {
		if (_tbhLastBet.isEmpty()) {
			// no bet made
			if (_iSameDozenColumnBeforeBet < _s63sSettings.GetSameDozenColumnBeforeBet()) {
				if (_qui8LastSpin == pSpin) {
					_iSameDozenColumnBeforeBet++;
				} else {
					_iSameDozenColumnBeforeBet = 0;
				} // if else

				break;
			} // if

			if (_iSameDozenColumnProgression < _s63sSettings.GetSameDozenColumnProgression()) {
				if ((_s63sSettings.GetProgressionDozenColumnNotChanged() && _qui8LastSpin == pSpin) || !_s63sSettings.GetProgressionDozenColumnNotChanged()) {
					_iSameDozenColumnProgression++;
				} else {
					_iSameDozenColumnBeforeBet = 0;
					_iSameDozenColumnProgression = 0;
					_qui8ProgressionIndex = 0;
				} // if else

				break;
			} // if
		} else {
			// bet made
			PlayCmn::eBetPosition ebpPosition = GetSpinPosition(pSpin);
			if (_tbhLastBet.contains(ebpPosition)) {
				// won
				_iSameDozenColumnBeforeBet = 0;
				_iSameDozenColumnProgression = 0;
				_qui8ProgressionIndex = 0;

				break;
			} else {
				// lost
				_iSameDozenColumnProgression = 0;

				if (_qui8ProgressionIndex == _qlProgressionSequence.size() - 1) {
					_iSameDozenColumnBeforeBet = 0;
					_qui8ProgressionIndex = 0;
				} else {
					_qui8ProgressionIndex++;
				} // if else

				break;
			} // if else
		} // if else
	} while (false);

	_qui8LastSpin = pSpin;
} // AnalyzeSpin

const void System63::CloseSettings(const QWidget *pSettings, const bool &pSave) const
{
	const System63SettingsWidget *s63swSettings = qobject_cast<const System63SettingsWidget *>(pSettings);

	if (pSave) {
		s63swSettings->SaveSettings();
	} // if

	delete s63swSettings;
} // CloseSettings

const PlayCmn::tBetHash System63::CreateBet() const
{
	PlayCmn::tBetHash tbhBet;

	for (int iBet = 0; iBet < 2; iBet++) {
		do {
			PlayCmn::eBetPosition ebpPosition = static_cast<PlayCmn::eBetPosition>((qrand() % (PlayCmn::BetPositionColumn3 - PlayCmn::BetPositionColumn1 + 1)) + PlayCmn::BetPositionColumn1);
			if (ebpPosition != _ebpLastPosition && !tbhBet.contains(ebpPosition)) {
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
	_qui8ProgressionIndex++;

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

const void System63::Reset()
{
	_ebpLastPosition = PlayCmn::BetPositionNone;
	_iSameDozenColumnBeforeBet = 0;
	_iSameDozenColumnProgression = 0;
	_qui8LastSpin = -1;

	_qlProgressionSequence.clear();
	QStringList qslProgressionSequence = _s63sSettings.GetProgressionManualSequence().split(PROGRESSION_SEQUENCE_SEPARATOR);
	foreach (QString qsProgression, qslProgressionSequence) {
		_qlProgressionSequence.append(qsProgression.toUInt());
	} // foreach
	_qui8ProgressionIndex = 0;
} // Reset

Q_EXPORT_PLUGIN2(system63, System63)