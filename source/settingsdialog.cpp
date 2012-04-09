#include "settingsdialog.h"

const void SettingsDialog::CloseCasinoSettings(const bool &pSave) const
{
	for (int iCasino = 0; iCasino < _csmCasinos.rowCount(); iCasino++) {
		QModelIndex qmiIndex = _csmCasinos.index(iCasino, CasinoSettingsModel::ColumnName);
		const CasinoInterface *ciCasino = static_cast<const CasinoInterface *>(qmiIndex.internalPointer());
		const QWidget *qwSettings = _qdsSettingsDialog.qswCasinoSettings->widget(iCasino);

		ciCasino->CloseSettings(qwSettings, pSave);
	} // for
} // CloseCasinoSettings

void SettingsDialog::done(int r)
{
	if (r == QDialog::Accepted) {
		SaveSettings();
	} // if
	CloseCasinoSettings(r == QDialog::Accepted);

	QDialog::done(r);
} // done

const void SettingsDialog::GetCasinoSettings() const
{
	for (int iCasino = 0; iCasino < _csmCasinos.rowCount(); iCasino++) {
		QModelIndex qmiIndex = _csmCasinos.index(iCasino, CasinoSettingsModel::ColumnName);
		CasinoInterface *ciCasino = static_cast<CasinoInterface *>(qmiIndex.internalPointer());
		QWidget *qwSettings = ciCasino->GetSettings();

		_qdsSettingsDialog.qswCasinoSettings->addWidget(qwSettings);
	} // for
} // GetCasinoSettings

const void SettingsDialog::LoadSettings() const
{
	_qdsSettingsDialog.qsbTokensPerBet->setValue(_sSettings->GetTokensPerBet());
} // LoadSettings

const void SettingsDialog::on_csmCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
	QModelIndex qmiIndex = _qdsSettingsDialog.qtvCasinos->currentIndex();
	_qdsSettingsDialog.qswCasinoSettings->setCurrentIndex(qmiIndex.row());
} // on_csmCasinosSelectionModel_selectionChanged

const void SettingsDialog::SaveSettings() const
{
	_sSettings->SetTokensPerBet(_qdsSettingsDialog.qsbTokensPerBet->value());
} // SaveSettings

SettingsDialog::SettingsDialog(Settings *pSettings, const CasinoPlugins *pCasinos, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QDialog(pParent, pFlags), _csmCasinos(pCasinos)
{
	_sSettings = pSettings;
	_cpCasinos = pCasinos;

	_qdsSettingsDialog.setupUi(this);

	_qdsSettingsDialog.qtvCasinos->setModel(&_csmCasinos);

	LoadSettings();
	GetCasinoSettings();

	connect(_qdsSettingsDialog.qtvCasinos->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(on_csmCasinosSelectionModel_selectionChanged(const QItemSelection &, const QItemSelection &)));

	_qdsSettingsDialog.qtvCasinos->setCurrentIndex(_csmCasinos.index(0, CasinoSettingsModel::ColumnName));
} // SettingsDialog