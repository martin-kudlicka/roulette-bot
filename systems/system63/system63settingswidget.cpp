#include "system63settingswidget.h"

const void System63SettingsWidget::LoadSettings() const
{
	_qwsSettingsWidget.qsbSameDozenColumnBeforeBet->setValue(_s63sSettings->GetSameDozenColumnBeforeBet());

	if (_s63sSettings->GetProgressionType() == System63Settings::ProgressionTypeAuto) {
		_qwsSettingsWidget.qrbProgressionAuto->setChecked(true);
	} else {
		_qwsSettingsWidget.qrbProgressionManual->setChecked(true);
	} // if else
	_qwsSettingsWidget.qsbProgression->setValue(_s63sSettings->GetProgressionAutoValue());
	_qwsSettingsWidget.qleProgression->setText(_s63sSettings->GetProgressionManualSequence());
	_qwsSettingsWidget.qsbSameDozenColumnProgression->setValue(_s63sSettings->GetSameDozenColumnProgression());
	_qwsSettingsWidget.qcbProgressionDozenColumnNotChanged->setChecked(_s63sSettings->GetProgressionDozenColumnNotChanged());
} // LoadSettings

const void System63SettingsWidget::SaveSettings() const
{
	_s63sSettings->SetSameDozenColumnBeforeBet(_qwsSettingsWidget.qsbSameDozenColumnBeforeBet->value());

	if (_qwsSettingsWidget.qrbProgressionAuto->isChecked()) {
		_s63sSettings->SetProgressionType(System63Settings::ProgressionTypeAuto);
	} else {
		_s63sSettings->SetProgressionType(System63Settings::ProgressionTypeManual);
	} // if else
	_s63sSettings->SetProgressionAutoValue(_qwsSettingsWidget.qsbProgression->value());
	_s63sSettings->SetProgressionManualSequence(_qwsSettingsWidget.qleProgression->text());
	_s63sSettings->SetSameDozenColumnProgression(_qwsSettingsWidget.qsbSameDozenColumnProgression->value());
	_s63sSettings->SetProgressionDozenColumnNotChanged(_qwsSettingsWidget.qcbProgressionDozenColumnNotChanged->isChecked());
} // SaveSettings

System63SettingsWidget::System63SettingsWidget(System63Settings *pSettings, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QWidget(pParent, pFlags)
{
	_s63sSettings = pSettings;

	_qwsSettingsWidget.setupUi(this);

	LoadSettings();
} // System63SettingsWidget