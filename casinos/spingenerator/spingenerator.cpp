#include "spingenerator.h"

#include "spingeneratorsettingswidget.h"

const void SpinGenerator::CloseSettings(const QWidget *pSettings, const bool &pSave) const
{
	const SpinGeneratorSettingsWidget *sgswSettings = qobject_cast<const SpinGeneratorSettingsWidget *>(pSettings);

	if (pSave) {
		sgswSettings->SaveSettings();
	} // if

	delete sgswSettings;
} // CloseSettings

const bool SpinGenerator::GameActive() const
{
	return true;
} // GameActive

const float SpinGenerator::GetCash() const
{
	return _fCash;
} // GetCash

const QString SpinGenerator::GetName() const
{
	return "spin generator";
} // GetName

QWidget *SpinGenerator::GetSettings()
{
	return new SpinGeneratorSettingsWidget(&_sgsSettings);
} // GetSettings

const void SpinGenerator::MakeBet(const PlayCmn::tBetHash &pBet, const int &pTokensPerBet)
{
	_iBet = 0;

	for (PlayCmn::tBetHash::const_iterator ciBet = pBet.constBegin(); ciBet != pBet.constEnd(); ciBet++) {
		_iBet += ciBet.value() * pTokensPerBet;
	} // for
} // MakeBet

const quint8 SpinGenerator::MakeSpin() const
{
	return qrand() % 37;
} // MakeSpin

const void SpinGenerator::ProcessSpinResult(const PlayCmn::sSpinResult &pResult, const int &pTokensPerBet)
{
	_fCash -= _iBet;

	if (pResult.esrtType & PlayCmn::SpinResultTypeWon) {
		_fCash += pResult.iBetProfit * pTokensPerBet;
	} // if
} // ProcessSpinResult

const void SpinGenerator::RemoveBet() const
{
} // RemoveBet

const void SpinGenerator::Reset()
{
} // Reset

SpinGenerator::SpinGenerator() : CasinoInterface()
{
	_fCash = _sgsSettings.GetStartingCash();
} // SpinGenerator

Q_EXPORT_PLUGIN2(spingenerator, SpinGenerator)