#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "ui_settingsdialog.h"

#include "settings.h"
#include "settingsdialog/casinosettingsmodel.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT

	public:
		SettingsDialog(const Settings *pSettings, const CasinoPlugins *pCasinos, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		CasinoSettingsModel _csmCasinos;
		const CasinoPlugins *_cpCasinos;
		const Settings *_sSettings;
		Ui::qdSettings _qdsSettingsDialog;

		virtual void done(int r);
		const void InitCasinoSettings() const;

	private slots:
		const void on_csmCasinosSelectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
}; // SettingsDialog

#endif // SETTINGSDIALOG_H