#include "system63.h"

#include "system63settingswidget.h"

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
	PlayCmn::tBetHash tbhBet;

	if (_iSameDozenColumnBeforeBet < _s63sSettings.GetSameDozenColumnBeforeBet()) {
		return tbhBet;
	} // if

	if (_qui8ProgressionIndex > 0 && _iSameDozenColumnProgression < _s63sSettings.GetSameDozenColumnProgression()) {
		return tbhBet;
	} // if

	tbhBet = CreateBet();
	_qui8ProgressionIndex++;

	return tbhBet;
} // GetBet

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

	_qlProgressionSequence.clear();
	QStringList qslProgressionSequence = _s63sSettings.GetProgressionManualSequence().split(PROGRESSION_SEQUENCE_SEPARATOR);
	foreach (QString qsProgression, qslProgressionSequence) {
		_qlProgressionSequence.append(qsProgression.toUInt());
	} // foreach
	_qui8ProgressionIndex = 0;
} // Reset

Q_EXPORT_PLUGIN2(system63, System63)