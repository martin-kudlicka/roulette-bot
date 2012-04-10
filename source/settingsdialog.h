#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "ui_settingsdialog.h"

#include "settings.h"
#include "settingsdialog/casinosettingsmodel.h"
#include "settingsdialog/systemsettingsmodel.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT

	public:
		SettingsDialog(Settings *pSettings, const CasinoPlugins *pCasinos, const SystemPlugins *pSystems, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		const CasinoPlugins *_cpCasinos;
		CasinoSettingsModel _csmCasinos;
		Settings *_sSettings;
		const SystemPlugins *_spSystems;
		SystemSettingsModel _ssmSystems;
		Ui::qdSettings _qdsSettingsDialog;

		const void CloseCasinoSettings(const bool &pSave) const;
		const void CloseSystemSettings(const bool &pSave) const;
		virtual void done(int r);
		const void GetCasinoSettings() const;
		const void GetSystemSettings() const;
		const void LoadSettings() const;
		const void SaveSettings() const;

	private slots:
		const void on_csmCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
		const void on_csmSystemsSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
}; // SettingsDialog

#endif // SETTINGSDIALOG_H