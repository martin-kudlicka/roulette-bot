#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QSettings>

class Settings
{
	public:
		Settings();

	private:
		QSettings _qsSettings;
}; // Settings

#endif // SETTINGS_H