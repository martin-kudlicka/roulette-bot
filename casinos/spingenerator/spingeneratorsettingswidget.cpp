#include "spingeneratorsettingswidget.h"

const void SpinGeneratorSettingsWidget::LoadSettings() const
{
	_qwsSettingsWidget.qsbStartingCash->setValue(_sgsSettings->GetStartingCash());
} // LoadSettings

const void SpinGeneratorSettingsWidget::SaveSettings() const
{
	_sgsSettings->SetStartingCash(_qwsSettingsWidget.qsbStartingCash->value());
} // SaveSettings

SpinGeneratorSettingsWidget::SpinGeneratorSettingsWidget(SpinGeneratorSettings *pSettings, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QWidget(pParent, pFlags)
{
	_sgsSettings = pSettings;

	_qwsSettingsWidget.setupUi(this);

	LoadSettings();
} // SpinGeneratorSettingsWidget