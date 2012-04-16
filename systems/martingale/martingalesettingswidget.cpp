#include "martingalesettingswidget.h"

const void MartingaleSettingsWidget::LoadSettings() const
{
	if (_msSettings->GetBetStyle() == MartingaleSettings::BetStyleKeepColor) {
		_qwsSettingsWidget.qrbBetStyleKeepColor->setChecked(true);
	} else {
		_qwsSettingsWidget.qrbBetStyleRandom->setChecked(true);
	} // if else
	_qwsSettingsWidget.qsbSameColorBeforeBet->setValue(_msSettings->GetSameColorBeforeBet());

	if (_msSettings->GetProgressionType() == MartingaleSettings::ProgressionTypeAuto) {
		_qwsSettingsWidget.qrbProgressionAuto->setChecked(true);
		on_qrbProgressionAuto_clicked();
	} else {
		_qwsSettingsWidget.qrbProgressionManual->setChecked(true);
		on_qrbProgressionManual_clicked();
	} // if else
	_qwsSettingsWidget.qsbProgression->setValue(_msSettings->GetProgressionAutoValue());
	_qwsSettingsWidget.qleProgression->setText(_msSettings->GetProgressionManualSequence());
	_qwsSettingsWidget.qsbSameColorProgression->setValue(_msSettings->GetSameColorProgression());
	_qwsSettingsWidget.qcbProgressionColorNotChanged->setChecked(_msSettings->GetProgressionColorNotChanged());
} // LoadSettings

const void MartingaleSettingsWidget::on_qrbProgressionAuto_clicked(bool checked /* false */) const
{
	_qwsSettingsWidget.qsbProgression->setEnabled(true);
	_qwsSettingsWidget.qleProgression->setEnabled(false);
} // on_qrbProgressionAuto_clicked

const void MartingaleSettingsWidget::on_qrbProgressionManual_clicked(bool checked /* false */) const
{
	_qwsSettingsWidget.qsbProgression->setEnabled(false);
	_qwsSettingsWidget.qleProgression->setEnabled(true);
} // on_qrbProgressionManual_clicked

const void MartingaleSettingsWidget::on_qsbProgression_valueChanged(int i) const
{
	QString qsSequence;
	int iProgression = 1;
	for (int iValue = 0; iValue < i; iValue++) {
		if (!qsSequence.isEmpty()) {
			qsSequence += PROGRESSION_SEQUENCE_SEPARATOR;
		} // if

		qsSequence += QString::number(iProgression);
		iProgression *= 2;
	} // for

	_qwsSettingsWidget.qleProgression->setText(qsSequence);
} // on_qsbProgression_valueChanged

const void MartingaleSettingsWidget::SaveSettings() const
{
	if (_qwsSettingsWidget.qrbBetStyleKeepColor->isChecked()) {
		_msSettings->SetBetStyle(MartingaleSettings::BetStyleKeepColor);
	} else {
		_msSettings->SetBetStyle(MartingaleSettings::BetStyleRandom);
	} // if else
	_msSettings->SetSameColorBeforeBet(_qwsSettingsWidget.qsbSameColorBeforeBet->value());

	if (_qwsSettingsWidget.qrbProgressionAuto->isChecked()) {
		_msSettings->SetProgressionType(MartingaleSettings::ProgressionTypeAuto);
	} else {
		_msSettings->SetProgressionType(MartingaleSettings::ProgressionTypeManual);
	} // if else
	_msSettings->SetProgressionAutoValue(_qwsSettingsWidget.qsbProgression->value());
	_msSettings->SetProgressionManualSequence(_qwsSettingsWidget.qleProgression->text());
	_msSettings->SetSameColorProgression(_qwsSettingsWidget.qsbSameColorProgression->value());
	_msSettings->SetProgressionColorNotChanged(_qwsSettingsWidget.qcbProgressionColorNotChanged->isChecked());
} // SaveSettings

MartingaleSettingsWidget::MartingaleSettingsWidget(MartingaleSettings *pSettings, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QWidget(pParent, pFlags)
{
	_msSettings = pSettings;

	_qwsSettingsWidget.setupUi(this);

	LoadSettings();
} // MartingaleSettingsWidget