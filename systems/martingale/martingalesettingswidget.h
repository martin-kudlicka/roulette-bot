#ifndef MARTINGALESETTINGSWIDGET_H
#define MARTINGALESETTINGSWIDGET_H

#include "ui_martingalesettingswidget.h"

#include "martingalesettings.h"

const QChar PROGRESSION_SEQUENCE_SEPARATOR = ';';

class MartingaleSettingsWidget : public QWidget
{
	Q_OBJECT

	public:
		MartingaleSettingsWidget(MartingaleSettings *pSettings, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

		const void SaveSettings() const;

	private:
		Ui::qwSettings _qwsSettingsWidget;
		MartingaleSettings *_msSettings;

		const void LoadSettings() const;

	private slots:
		const void on_qrbProgressionAuto_toggled(bool checked) const;
		const void on_qrbProgressionManual_toggled(bool checked) const;
		const void on_qsbProgression_valueChanged(int i) const;
}; // MartingaleSettingsWidget

#endif // MARTINGALESETTINGSWIDGET_H