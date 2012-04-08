#ifndef CASINODIALOG_H
#define CASINODIALOG_H

#include <QtGui/QDialog>
#include "ui_casinodialog.h"

#include "../casino/common/casinointerface.h"

class CasinoDialog : public QDialog
{
	Q_OBJECT

	public:
		CasinoDialog(const CasinoInterface *pCasino, QWidget *pParent = NULL, Qt::WindowFlags pFlags = 0);

	private:
		const CasinoInterface *_ciCasino;
		Ui::qdCasino _qdcCasinoDialog;

		const void RefreshStatus() const;
}; // CasinoDialog

#endif // CASINODIALOG_H
