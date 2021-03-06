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
		const void on_qrbBetOnDozenColumn_toggled(bool checked) const;
		const void on_qrbBetOnRandom_toggled(bool checked) const;
		const void on_qrbBoth_toggled(bool checked) const;
		const void on_qrbColumn_toggled(bool checked) const;
		const void on_qrbDozen_toggled(bool checked) const;
		const void on_qrbProgressionAuto_toggled(bool checked) const;
		const void on_qrbProgressionManual_toggled(bool checked) const;
		const void on_qsbProgression_valueChanged(int i) const;
}; // System63SettingsWidget

#endif // SYSTEM63SETTINGSWIDGET_H