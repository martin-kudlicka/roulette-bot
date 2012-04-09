#ifndef UNIBETSETTINGSWIDGET_H
#define UNIBETSETTINGSWIDGET_H

#include "ui_unibetsettingswidget.h"

#include "unibetsettings.h"

class UnibetSettingsWidget : public QWidget
{
	Q_OBJECT

	public:
		UnibetSettingsWidget(UnibetSettings *pSettings, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

		const void SaveSettings() const;

	private:
		Ui::qwSettings _qwsSettingsWidget;
		UnibetSettings *_usSettings;

		const void InitSettings() const;
		const void LoadSettings() const;
}; // UnibetSettingsWidget

#endif // UNIBETSETTINGSWIDGET_H