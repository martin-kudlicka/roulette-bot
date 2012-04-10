#ifndef CASINODIALOG_H
#define CASINODIALOG_H

#include "ui_casinodialog.h"

#include "../casinos/common/casinointerface.h"

class CasinoDialog : public QDialog
{
	Q_OBJECT

	public:
		CasinoDialog(const CasinoInterface *pCasino, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		const CasinoInterface *_ciCasino;
		Ui::qdCasino _qdcCasinoDialog;

		const bool IsPlaying() const;
		const void RefreshStatus() const;

	private slots:
		const void on_ciCasino_GameActiveChanged(const bool &pActive) const;
		const void on_qpbStart_clicked(bool checked = false) const;
		const void on_qpbStop_clicked(bool checked = false) const;
}; // CasinoDialog

#endif // CASINODIALOG_H