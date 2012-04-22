#include "system63settingswidget.h"

const void System63SettingsWidget::LoadSettings() const
{
	if (_s63sSettings->GetBetOn() == System63Settings::BetOnDozenColumn) {
		_qwsSettingsWidget.qrbBetOnDozenColumn->setChecked(true);
	} else {
		_qwsSettingsWidget.qrbBetOnRandom->setChecked(true);
	} // if else

	if (_s63sSettings->GetDozenColumnType() == System63Settings::DozenColumnTypeDozen) {
		_qwsSettingsWidget.qrbDozen->setChecked(true);
	} else {
		if (_s63sSettings->GetDozenColumnType() == System63Settings::DozenColumnTypeColumn) {
			_qwsSettingsWidget.qrbColumn->setChecked(true);
		} else {
			_qwsSettingsWidget.qrbBoth->setChecked(true);
		} // if else
	} // if else
	_qwsSettingsWidget.qcbDozen3x->setChecked(_s63sSettings->GetDozen3x());
	_qwsSettingsWidget.qcbColumn3x->setChecked(_s63sSettings->GetColumn3x());

	_qwsSettingsWidget.qsbSameDozenColumnBeforeBet->setValue(_s63sSettings->GetSameDozenColumnBeforeBet());

	if (_s63sSettings->GetProgressionType() == System63Settings::ProgressionTypeAuto) {
		_qwsSettingsWidget.qrbProgressionAuto->setChecked(true);
		on_qrbProgressionAuto_clicked();
	} else {
		_qwsSettingsWidget.qrbProgressionManual->setChecked(true);
		on_qrbProgressionManual_clicked();
	} // if else
	_qwsSettingsWidget.qsbProgression->setValue(_s63sSettings->GetProgressionAutoValue());
	_qwsSettingsWidget.qleProgression->setText(_s63sSettings->GetProgressionManualSequence());
	_qwsSettingsWidget.qsbSameDozenColumnProgression->setValue(_s63sSettings->GetSameDozenColumnProgression());
	_qwsSettingsWidget.qcbProgressionDozenColumnNotChanged->setChecked(_s63sSettings->GetProgressionDozenColumnNotChanged());
} // LoadSettings

const void System63SettingsWidget::on_qrbBetOnDozenColumn_toggled(bool checked) const
{
	_qwsSettingsWidget.qgbDozenColumn->setEnabled(checked);
} // on_qrbBetOnDozenColumn_clicked

const void System63SettingsWidget::on_qrbBetOnRandom_toggled(bool checked) const
{
	_qwsSettingsWidget.qgbDozenColumn->setEnabled(!checked);
} // on_qrbBetOnRandom_clicked

const void System63SettingsWidget::on_qrbBoth_toggled(bool checked) const
{
	if (checked) {
		_qwsSettingsWidget.qcbDozen3x->setEnabled(true);
		_qwsSettingsWidget.qcbColumn3x->setEnabled(true);
	} // if
} // on_qrbBoth_toggled

const void System63SettingsWidget::on_qrbColumn_toggled(bool checked) const
{
	_qwsSettingsWidget.qcbDozen3x->setEnabled(!checked);
	_qwsSettingsWidget.qcbColumn3x->setEnabled(checked);
} // on_qrbColumn_toggled

const void System63SettingsWidget::on_qrbDozen_toggled(bool checked) const
{
	_qwsSettingsWidget.qcbDozen3x->setEnabled(checked);
	_qwsSettingsWidget.qcbColumn3x->setEnabled(!checked);
} // on_qrbDozen_toggled

const void System63SettingsWidget::on_qrbProgressionAuto_clicked(bool checked /* false */) const
{
	_qwsSettingsWidget.qsbProgression->setEnabled(true);
	_qwsSettingsWidget.qleProgression->setEnabled(false);
} // on_qrbProgressionAuto_clicked

const void System63SettingsWidget::on_qrbProgressionManual_clicked(bool checked /* false */) const
{
	_qwsSettingsWidget.qsbProgression->setEnabled(false);
	_qwsSettingsWidget.qleProgression->setEnabled(true);
} // on_qrbProgressionManual_clicked

const void System63SettingsWidget::on_qsbProgression_valueChanged(int i) const
{
	QString qsSequence;
	int iProgression = 1;
	for (int iValue = 0; iValue < i; iValue++) {
		if (!qsSequence.isEmpty()) {
			qsSequence += PROGRESSION_SEQUENCE_SEPARATOR;
		} // if

		qsSequence += QString::number(iProgression);
		iProgression *= 3;
	} // for

	_qwsSettingsWidget.qleProgression->setText(qsSequence);
} // on_qsbProgression_valueChanged

const void System63SettingsWidget::SaveSettings() const
{
	if (_qwsSettingsWidget.qrbBetOnDozenColumn->isChecked()) {
		_s63sSettings->SetBetOn(System63Settings::BetOnDozenColumn);
	} else {
		_s63sSettings->SetBetOn(System63Settings::BetOnRandom);
	} // if else

	if (_qwsSettingsWidget.qrbDozen->isChecked()) {
		_s63sSettings->SetDozenColumnType(System63Settings::DozenColumnTypeDozen);
	} else {
		if (_qwsSettingsWidget.qrbColumn->isChecked()) {
			_s63sSettings->SetDozenColumnType(System63Settings::DozenColumnTypeColumn);
		} else {
			_s63sSettings->SetDozenColumnType(System63Settings::DozenColumnTypeBoth);
		} // if else
	} // if else
	_s63sSettings->SetDozen3x(_qwsSettingsWidget.qcbDozen3x->isChecked());
	_s63sSettings->SetColumn3x(_qwsSettingsWidget.qcbColumn3x->isChecked());

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