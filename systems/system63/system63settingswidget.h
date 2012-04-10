#ifndef SYSTEM63SETTINGSWIDGET_H
#define SYSTEM63SETTINGSWIDGET_H

#include "ui_system63settingswidget.h"

#include "system63settings.h"

const QChar PROGRESSION_SEQUENCE_SEPARATOR = ';';

class System63SettingsWidget : public QWidget
{
	Q_OBJECT

	public:
		System63SettingsWidget(System63Settings *pSettings, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

		const void SaveSettings() const;

	private:
		Ui::qwSettings _qwsSettingsWidget;
		System63Settings *_s63sSettings;

		const void LoadSettings() const;

	private slots:
		const void on_qrbProgressionAuto_clicked(bool checked = false) const;
		const void on_qrbProgressionManual_clicked(bool checked = false) const;
		const void on_qsbProgression_valueChanged(int i) const;
}; // System63SettingsWidget

#endif // SYSTEM63SETTINGSWIDGET_H