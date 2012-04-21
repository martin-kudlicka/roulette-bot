#ifndef SPINGENERATORSETTINGSWIDGET_H
#define SPINGENERATORSETTINGSWIDGET_H

#include "ui_spingeneratorsettingswidget.h"

#include "spingeneratorsettings.h"

class SpinGeneratorSettingsWidget : public QWidget
{
	Q_OBJECT

	public:
		SpinGeneratorSettingsWidget(SpinGeneratorSettings *pSettings, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

		const void SaveSettings() const;

	private:
		Ui::qwSettings _qwsSettingsWidget;
		SpinGeneratorSettings *_sgsSettings;

		const void LoadSettings() const;
}; // SpinGeneratorSettingsWidget

#endif // SPINGENERATORSETTINGSWIDGET_H