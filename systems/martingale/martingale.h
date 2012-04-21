#ifndef MARTINGALE_H
#define MARTINGALE_H

#include "../common/systeminterface.h"
#include "martingalesettings.h"
#include "martingalestatisticswidget.h"

class Martingale : public SystemInterface
{
	Q_OBJECT
	Q_INTERFACES(SystemInterface)

	private:
		PlayCmn::eBetPosition _ebpLastPosition;
		PlayCmn::eBetPosition _ebpLastProgressionPosition;
		int _iMaxSameInRow;
		int _iSameColorBeforeBet;
		int _iSameColorProgression;
		int _iSameInRow;
		MartingaleSettings _msSettings;
		MartingaleStatisticsWidget _mswStatistics;
		QList<quint8> _qlProgressionSequence;
		quint8 _qui8ProgressionIndex;
		PlayCmn::tBetHash _tbhLastBet;

		virtual const PlayCmn::sSpinResult AnalyzeSpin(const quint8 &pSpin);
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual const void CloseStatistics() const;
		const PlayCmn::tBetHash CreateBet() const;
		virtual const PlayCmn::tBetHash GetBet();
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		const PlayCmn::eBetPosition GetSpinPosition(const quint8 &pSpin) const;
		virtual const void OpenStatistics(QVBoxLayout *pLayout);
		virtual const void Reset(const qfResetContents &pResetContents);
}; // Martingale

#endif // MARTINGALE_H
