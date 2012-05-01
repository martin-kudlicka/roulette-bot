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
		MartingaleSettings _msSettings;
		MartingaleStatisticsWidget _mswStatistics;
		PlayCmn::qfBetPositions _qfbpLastPosition;
		PlayCmn::qfBetPositions _qfbpLastProgressionPosition;
		QList<quint8> _qlProgressionSequence;
		quint8 _qui8MaxSameInRow;
		quint8 _qui8ProgressionIndex;
		quint8 _qui8SameColorBeforeBet;
		quint8 _qui8SameColorProgression;
		quint8 _qui8SameInRow;

		virtual const PlayCmn::sSpinResult AnalyzeSpin(const quint8 &pSpin);
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual const void CloseStatistics() const;
		const PlayCmn::tBetHash CreateBet() const;
		virtual const PlayCmn::tBetHash GetBet();
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		virtual const void OpenStatistics(QVBoxLayout *pLayout);
		virtual const void Reset(const qfResetContents &pResetContents);
}; // Martingale

#endif // MARTINGALE_H
