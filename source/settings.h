#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QSettings>

class Settings
{
	public:
		Settings();

		const int GetTokensPerBet();
		const void SetTokensPerBet(const int &pTokens);

	private:
		QSettings _qsSettings;
}; // Settings

#endif // SETTINGS_H