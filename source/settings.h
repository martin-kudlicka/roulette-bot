#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QSettings>

class Settings
{
	public:
		Settings();

		const int GetMaxLossToPlay();
		const int GetTokensPerBet();
		const void SetMaxLossToPlay(const int &pValue);
		const void SetTokensPerBet(const int &pTokens);

	private:
		QSettings _qsSettings;
}; // Settings

#endif // SETTINGS_H