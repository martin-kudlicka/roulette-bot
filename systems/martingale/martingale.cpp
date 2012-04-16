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
	// TODO
} // CloseStatistics

const PlayCmn::tBetHash Martingale::GetBet()
{
	// TODO
	return PlayCmn::tBetHash();
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
	// TODO
} // OpenStatistics

const void Martingale::Reset()
{
	// TODO
} // Reset

Q_EXPORT_PLUGIN2(martingale, Martingale)