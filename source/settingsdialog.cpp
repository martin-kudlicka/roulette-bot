#include "settingsdialog.h"

const void SettingsDialog::CloseCasinoSettings(const bool &pSave) const
{
	for (int iCasino = _csmCasinos.rowCount() - 1; iCasino >= 0 ; iCasino--) {
		QModelIndex qmiIndex = _csmCasinos.index(iCasino, CasinoSettingsModel::ColumnName);
		const CasinoInterface *ciCasino = static_cast<const CasinoInterface *>(qmiIndex.internalPointer());
		const QWidget *qwSettings = _qdsSettingsDialog.qswCasinoSettings->widget(iCasino);

		ciCasino->CloseSettings(qwSettings, pSave);
	} // for
} // CloseCasinoSettings

const void SettingsDialog::CloseSystemSettings(const bool &pSave) const
{
	for (int iSystem = _ssmSystems.rowCount() - 1; iSystem >= 0; iSystem--) {
		QModelIndex qmiIndex = _ssmSystems.index(iSystem, SystemSettingsModel::ColumnName);
		const SystemInterface *siSystem = static_cast<const SystemInterface *>(qmiIndex.internalPointer());
		const QWidget *qwSettings = _qdsSettingsDialog.qswSystemSettings->widget(iSystem);

		siSystem->CloseSettings(qwSettings, pSave);
	} // for
} // CloseSystemSettings

void SettingsDialog::done(int r)
{
	if (r == QDialog::Accepted) {
		SaveSettings();
	} // if
	CloseCasinoSettings(r == QDialog::Accepted);
	CloseSystemSettings(r == QDialog::Accepted);

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

const void SettingsDialog::GetSystemSettings() const
{
	for (int iSystem = 0; iSystem < _ssmSystems.rowCount(); iSystem++) {
		QModelIndex qmiIndex = _ssmSystems.index(iSystem, SystemSettingsModel::ColumnName);
		SystemInterface *siSystem = static_cast<SystemInterface *>(qmiIndex.internalPointer());
		QWidget *qwSettings = siSystem->GetSettings();

		_qdsSettingsDialog.qswSystemSettings->addWidget(qwSettings);
	} // for
} // GetSystemSettings

const void SettingsDialog::LoadSettings() const
{
	_qdsSettingsDialog.qsbTokensPerBet->setValue(_sSettings->GetTokensPerBet());
	_qdsSettingsDialog.qsbMaxLossToPlay->setValue(_sSettings->GetMaxLossToPlay());
} // LoadSettings

const void SettingsDialog::on_csmCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
	QModelIndex qmiIndex = _qdsSettingsDialog.qtvCasinos->currentIndex();
	_qdsSettingsDialog.qswCasinoSettings->setCurrentIndex(qmiIndex.row());
} // on_csmCasinosSelectionModel_selectionChanged

const void SettingsDialog::on_csmSystemsSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
	QModelIndex qmiIndex = _qdsSettingsDialog.qtvSystems->currentIndex();
	_qdsSettingsDialog.qswSystemSettings->setCurrentIndex(qmiIndex.row());
} // on_csmSystemsSelectionModel_selectionChanged

const void SettingsDialog::SaveSettings() const
{
	_sSettings->SetTokensPerBet(_qdsSettingsDialog.qsbTokensPerBet->value());
	_sSettings->SetMaxLossToPlay(_qdsSettingsDialog.qsbMaxLossToPlay->value());
} // SaveSettings

SettingsDialog::SettingsDialog(Settings *pSettings, const CasinoPlugins *pCasinos, const SystemPlugins *pSystems, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QDialog(pParent, pFlags), _csmCasinos(pCasinos), _ssmSystems(pSystems)
{
	_sSettings = pSettings;
	_cpCasinos = pCasinos;
	_spSystems = pSystems;

	_qdsSettingsDialog.setupUi(this);

	_qdsSettingsDialog.qtvCasinos->setModel(&_csmCasinos);
	_qdsSettingsDialog.qtvSystems->setModel(&_ssmSystems);

	LoadSettings();
	GetCasinoSettings();
	GetSystemSettings();

	connect(_qdsSettingsDialog.qtvCasinos->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(on_csmCasinosSelectionModel_selectionChanged(const QItemSelection &, const QItemSelection &)));
	connect(_qdsSettingsDialog.qtvSystems->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), SLOT(on_csmSystemsSelectionModel_selectionChanged(const QItemSelection &, const QItemSelection &)));

	_qdsSettingsDialog.qtvCasinos->setCurrentIndex(_csmCasinos.index(0, CasinoSettingsModel::ColumnName));
	_qdsSettingsDialog.qtvSystems->setCurrentIndex(_ssmSystems.index(0, SystemSettingsModel::ColumnName));
} // SettingsDialog