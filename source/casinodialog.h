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
		~CasinoDialog();
		CasinoDialog(CasinoInterface *pCasino, const SystemPlugins *pSystems, Settings *pSettings, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		bool _bStop;
		CasinoInterface *_ciCasino;
		float _fStartingCash;
		quint8 _qui8MaxProgression;
		Settings *_sSettings;
		SystemInterface *_siSystem;
		const SystemPlugins *_spSystems;
		Ui::qdCasino _qdcCasinoDialog;

		const void IncreaseCounter(QLabel *pCounter) const;
		const void IncreaseProgressionCounter(const quint8 &pProgression) const;
		const void InitSettings() const;
		const bool IsPlaying() const;
		const void PlayRound();
		const void RefreshStatus() const;

	private slots:
		const void on_ciCasino_GameActiveChanged(const bool &pActive);
		const void on_qcbSystems_currentIndexChanged(int index);
		const void on_qpbResetStatistics_clicked(bool checked = false) const;
		const void on_qpbStart_clicked(bool checked = false);
		const void on_qpbStop_clicked(bool checked = false);
}; // CasinoDialog

#endif // CASINODIALOG_H