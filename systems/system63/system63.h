#ifndef SYSTEM63_H
#define SYSTEM63_H

#include "../common/systeminterface.h"
#include "system63settings.h"
#include "system63statisticswidget.h"

class System63 : public SystemInterface
{
	Q_OBJECT
	Q_INTERFACES(SystemInterface)

	private:
		PlayCmn::eBetPosition _ebpLastPosition;
		PlayCmn::eBetPosition _ebpLastProgressionPosition;
		int _iMaxSameInRow;
		int _iSameDozenColumnBeforeBet;
		int _iSameDozenColumnProgression;
		int _iSameInRow;
		QList<quint8> _qlProgressionSequence;
		quint8 _qui8ProgressionIndex;
		System63Settings _s63sSettings;
		System63StatisticsWidget _s63swStatistics;
		PlayCmn::tBetHash _tbhLastBet;

		virtual const PlayCmn::qfSpinResults AnalyzeSpin(const quint8 &pSpin);
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual const void CloseStatistics() const;
		const PlayCmn::tBetHash CreateBet() const;
		virtual const PlayCmn::tBetHash GetBet();
		const PlayCmn::eBetPosition GetSpinPosition(const quint8 &pSpin) const;
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		virtual const void OpenStatistics(QVBoxLayout *pLayout);
		virtual const void Reset(const qfResetContents &pResetContents);
}; // System63

#endif // SYSTEM63_H
