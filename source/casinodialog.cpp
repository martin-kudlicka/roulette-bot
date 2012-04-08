#include "casinodialog.h"

CasinoDialog::CasinoDialog(const CasinoInterface *pCasino, QWidget *pParent /* NULL */, Qt::WindowFlags pFlags /* 0 */) : QDialog(pParent, pFlags)
{
	_ciCasino = pCasino;

	_qdcCasinoDialog.setupUi(this);
} // CasinoDialog