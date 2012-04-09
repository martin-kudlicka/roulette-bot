#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "ui_settingsdialog.h"

#include "settings.h"
#include "settingsdialog/casinosettingsmodel.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT

	public:
		SettingsDialog(Settings *pSettings, const CasinoPlugins *pCasinos, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		CasinoSettingsModel _csmCasinos;
		const CasinoPlugins *_cpCasinos;
		Settings *_sSettings;
		Ui::qdSettings _qdsSettingsDialog;

		const void CloseCasinoSettings(const bool &pSave) const;
		virtual void done(int r);
		const void GetCasinoSettings() const;
		const void LoadSettings() const;
		const void SaveSettings() const;

	private slots:
		const void on_csmCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
}; // SettingsDialog

#endif // SETTINGSDIALOG_H