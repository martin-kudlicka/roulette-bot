#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QSettings>

class Settings
{
	public:
		Settings();

		const int GetMaxLossToPlay();
		const bool GetStopOnLoss();
		const int GetTokensPerBet();
		const void SetMaxLossToPlay(const int &pValue);
		const void SetStopOnLoss(const bool &pStop);
		const void SetTokensPerBet(const int &pTokens);

	private:
		QSettings _qsSettings;
}; // Settings

#endif // SETTINGS_H