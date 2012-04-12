#ifndef CASINODIALOG_H
#define CASINODIALOG_H

#include "ui_casinodialog.h"

#include "../casinos/common/casinointerface.h"
#include "systemplugins.h"
#include "settings.h"

class CasinoDialog : public QDialog
{
	Q_OBJECT

	public:
		CasinoDialog(CasinoInterface *pCasino, const SystemPlugins *pSystems, Settings *pSettings, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		bool _bStop;
		CasinoInterface *_ciCasino;
		Settings *_sSettings;
		const SystemPlugins *_spSystems;
		Ui::qdCasino _qdcCasinoDialog;

		const void InitSettings() const;
		const bool IsPlaying() const;
		const void PlayRound(SystemInterface *pSystem) const;
		const void RefreshStatus() const;

	private slots:
		const void on_ciCasino_GameActiveChanged(const bool &pActive);
		const void on_qpbStart_clicked(bool checked = false);
		const void on_qpbStop_clicked(bool checked = false);
}; // CasinoDialog

#endif // CASINODIALOG_H