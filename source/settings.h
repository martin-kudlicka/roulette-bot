#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QSettings>

class Settings
{
	public:
		Settings();

		const quint8 GetMaxLossToPlay();
		const quint8 GetMaxWinToPlay();
		const bool GetStopOnLoss();
		const quint8 GetTokensPerBet();
		const void SetMaxLossToPlay(const quint8 &pValue);
		const void SetMaxWinToPlay(const quint8 &pValue);
		const void SetStopOnLoss(const bool &pStop);
		const void SetTokensPerBet(const quint8 &pTokens);

	private:
		QSettings _qsSettings;
}; // Settings

#endif // SETTINGS_H