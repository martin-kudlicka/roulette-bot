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
		int _iMaxSameColumnInRow[THREEX_COUNT];
		int _iMaxSameDozenInRow[THREEX_COUNT];
		int _iMaxSameInRowRandom;
		int _iSameColumnBeforeBet[THREEX_COUNT];
		int _iSameColumnProgression[THREEX_COUNT];
		int _iSameDozenBeforeBet[THREEX_COUNT];
		int _iSameDozenProgression[THREEX_COUNT];
		int _iSameRandomBeforeBet;
		int _iSameRandomProgression;
		int _iSameColumnInRow[THREEX_COUNT];
		int _iSameDozenInRow[THREEX_COUNT];
		int _iSameInRowRandom;
		QList<quint8> _qlProgressionSequence;
		quint8 _qui8ProgressionIndexColumn[THREEX_COUNT];
		quint8 _qui8ProgressionIndexDozen[THREEX_COUNT];
		quint8 _qui8ProgressionIndexRandom;
		System63Settings _s63sSettings;
		System63StatisticsWidget _s63swStatistics;
		PlayCmn::tBetHash _tbhLastBet;
		PlayCmn::tBetHash _tbhLastColumnBet[THREEX_COUNT];
		PlayCmn::tBetHash _tbhLastDozenBet[THREEX_COUNT];

		const void AddToLastBet(const PlayCmn::tBetHash &pBet);
		const void AddToResult(PlayCmn::sSpinResult *pResult, const PlayCmn::sSpinResult &pAdd) const;
		const PlayCmn::sSpinResult AnalyzeSpin(const PlayCmn::tBetHash &pBet, const PlayCmn::eBetPosition pPosition, int *pSameBeforeBet, const PlayCmn::eBetPosition &pCheckToLastPosition, PlayCmn::eBetPosition *pLastPosition, int *pSameProgression, PlayCmn::eBetPosition *pLastProgressionPosition, quint8 *pProgressionIndex, int *pSameInRow, int *pMaxSameInRow);
		virtual const PlayCmn::sSpinResult AnalyzeSpin(const quint8 &pSpin);
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual const void CloseStatistics() const;
		const PlayCmn::tBetHash CreateBet(const int &pSameBeforeBet, const int &pSameBeforeProgression, const quint8 &pProgressionIndex, const System63Settings::eDozenColumnType &pType, const PlayCmn::eBetPosition &pLastPosition) const;
		virtual const PlayCmn::tBetHash GetBet();
		const PlayCmn::eBetPosition GetSpinPosition(const quint8 &pSpin, const System63Settings::eDozenColumnType &pType) const;
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		virtual const void OpenStatistics(QVBoxLayout *pLayout);
		virtual const void Reset(const qfResetContents &pResetContents);
}; // System63

#endif // SYSTEM63_H
