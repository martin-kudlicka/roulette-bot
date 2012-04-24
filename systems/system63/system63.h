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
		static const quint8 THREEX_COUNT = 3;

		PlayCmn::eBetPosition _ebpLastPositionColumn[THREEX_COUNT];
		PlayCmn::eBetPosition _ebpLastPositionDozen[THREEX_COUNT];
		PlayCmn::eBetPosition _ebpLastPositionRandom;
		PlayCmn::eBetPosition _ebpLastProgressionPositionColumn[THREEX_COUNT];
		PlayCmn::eBetPosition _ebpLastProgressionPositionDozen[THREEX_COUNT];
		PlayCmn::eBetPosition _ebpLastProgressionPositionRandom;
		System63Settings::eDozenColumnType _edctLastBetRandom;
		QList<quint8> _qlProgressionSequence;
		quint8 _qui8MaxSameColumnInRow[THREEX_COUNT];
		quint8 _qui8MaxSameDozenInRow[THREEX_COUNT];
		quint8 _qui8MaxSameInRowRandom;
		quint8 _qui8ProgressionIndexColumn[THREEX_COUNT];
		quint8 _qui8ProgressionIndexDozen[THREEX_COUNT];
		quint8 _qui8ProgressionIndexRandom;
		quint8 _qui8SameColumnBeforeBet[THREEX_COUNT];
		quint8 _qui8SameColumnProgression[THREEX_COUNT];
		quint8 _qui8SameDozenBeforeBet[THREEX_COUNT];
		quint8 _qui8SameDozenProgression[THREEX_COUNT];
		quint8 _qui8SameRandomBeforeBet;
		quint8 _qui8SameRandomProgression;
		quint8 _qui8SameColumnInRow[THREEX_COUNT];
		quint8 _qui8SameDozenInRow[THREEX_COUNT];
		quint8 _qui8SameInRowRandom;
		System63Settings _s63sSettings;
		System63StatisticsWidget _s63swStatistics;
		PlayCmn::tBetHash _tbhLastBet;
		PlayCmn::tBetHash _tbhLastColumnBet[THREEX_COUNT];
		PlayCmn::tBetHash _tbhLastDozenBet[THREEX_COUNT];

		const void AddToLastBet(const PlayCmn::tBetHash &pBet);
		const void AddToResult(PlayCmn::sSpinResult *pResult, const PlayCmn::sSpinResult &pAdd) const;
		const PlayCmn::sSpinResult AnalyzeSpin(const PlayCmn::tBetHash &pBet, const PlayCmn::eBetPosition pPosition, quint8 *pSameBeforeBet, const PlayCmn::eBetPosition &pCheckToLastPosition, PlayCmn::eBetPosition *pLastPosition, quint8 *pSameProgression, PlayCmn::eBetPosition *pLastProgressionPosition, quint8 *pProgressionIndex, quint8 *pSameInRow, quint8 *pMaxSameInRow);
		virtual const PlayCmn::sSpinResult AnalyzeSpin(const quint8 &pSpin);
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual const void CloseStatistics() const;
		const PlayCmn::tBetHash CreateBet(const quint8 &pSameBeforeBet, const quint8 &pSameBeforeProgression, const quint8 &pProgressionIndex, const System63Settings::eDozenColumnType &pType, const PlayCmn::eBetPosition &pLastPosition) const;
		virtual const PlayCmn::tBetHash GetBet();
		const PlayCmn::eBetPosition GetSpinPosition(const quint8 &pSpin, const System63Settings::eDozenColumnType &pType) const;
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		virtual const void OpenStatistics(QVBoxLayout *pLayout);
		virtual const void Reset(const qfResetContents &pResetContents);
}; // System63

#endif // SYSTEM63_H
