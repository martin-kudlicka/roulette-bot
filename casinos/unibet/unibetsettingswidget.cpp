#include "unibetsettingswidget.h"

const void UnibetSettingsWidget::InitSettings() const
{
	_qwsSettingsWidget.qcbTokenValue->addItem("0.1 / 1 / 25");
	_qwsSettingsWidget.qcbTokenValue->addItem("0.5 / 5 / 100");
	_qwsSettingsWidget.qcbTokenValue->addItem("1 / 25 / 1000");
	_qwsSettingsWidget.qcbTokenValue->addItem("10 / 100 / 5000");
} // InitSettings

const void UnibetSettingsWidget::LoadSettings() const
{
	_qwsSettingsWidget.qcbTokenValue->setCurrentIndex(_usSettings->GetTokenValue());
} // LoadSettings

const void UnibetSettingsWidget::SaveSettings() const
{
	_usSettings->SetTokenValue(static_cast<UnibetSettings::eTokenValue>(_qwsSettingsWidget.qcbTokenValue->currentIndex()));
} // SaveSettings

UnibetSettingsWidget::UnibetSettingsWidget(UnibetSettings *pSettings, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QWidget(pParent, pFlags)
{
	_usSettings = pSettings;

	_qwsSettingsWidget.setupUi(this);

	InitSettings();
	LoadSettings();
} // UnibetSettingsWidget