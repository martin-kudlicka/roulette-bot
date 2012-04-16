#ifndef MARTINGALE_H
#define MARTINGALE_H

#include "../common/systeminterface.h"
#include "martingalesettings.h"

class Martingale : public SystemInterface
{
	Q_OBJECT
	Q_INTERFACES(SystemInterface)

	private:
		MartingaleSettings _msSettings;

		virtual const qfSpinResults AnalyzeSpin(const quint8 &pSpin);
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual const void CloseStatistics() const;
		virtual const PlayCmn::tBetHash GetBet();
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		virtual const void OpenStatistics(QVBoxLayout *pLayout);
		virtual const void Reset();
}; // Martingale

#endif // MARTINGALE_H
