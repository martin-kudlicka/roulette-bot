#include "unibetsettingswidget.h"

const void UnibetSettingsWidget::InitSettings() const
{
	_qwsSettingsWidget.qcbBetValue->addItem("0.1 / 1 / 25");
	_qwsSettingsWidget.qcbBetValue->addItem("0.5 / 5 / 100");
	_qwsSettingsWidget.qcbBetValue->addItem("1 / 25 / 1000");
	_qwsSettingsWidget.qcbBetValue->addItem("10 / 100 / 5000");
} // InitSettings

const void UnibetSettingsWidget::LoadSettings() const
{
	_qwsSettingsWidget.qcbBetValue->setCurrentIndex(_usSettings->GetBetValue());
} // LoadSettings

const void UnibetSettingsWidget::SaveSettings() const
{
	_usSettings->SetBetValue(static_cast<UnibetSettings::eBetValue>(_qwsSettingsWidget.qcbBetValue->currentIndex()));
} // SaveSettings

UnibetSettingsWidget::UnibetSettingsWidget(UnibetSettings *pSettings, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QWidget(pParent, pFlags)
{
	_usSettings = pSettings;

	_qwsSettingsWidget.setupUi(this);

	InitSettings();
	LoadSettings();
} // UnibetSettingsWidget