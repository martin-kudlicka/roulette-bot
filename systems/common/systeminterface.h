#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H

#include <QtPlugin>
#include "../../common/playcmn.h"
#include <QtGui/QVBoxLayout>

static const char *SYSTEM_INTERFACE = "System Interface 1.0";

class SystemInterface : public QObject
{
	Q_OBJECT
	Q_ENUMS(eResetContent)

	public:
		enum eResetContent {
			ResetContentCore = 1,
			ResetContentStatistics
		}; // eResetType
		Q_DECLARE_FLAGS(qfResetContents, eResetContent)

		virtual const PlayCmn::sSpinResult AnalyzeSpin(const quint8 &pSpin) = 0;
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const = 0;
		virtual const void CloseStatistics() const = 0;
		virtual const PlayCmn::tBetHash GetBet() = 0;
		virtual const QString GetName() const = 0;
		virtual QWidget *GetSettings() = 0;
		virtual const void OpenStatistics(QVBoxLayout *pLayout) = 0;
		virtual const void Reset(const qfResetContents &pResetContents) = 0;

	protected:
		PlayCmn::tBetHash _tbhLastBet;

		const bool BetContains(const PlayCmn::tBetHash &pBet, const PlayCmn::qfBetPositions &pPosition) const;
		const quint8 BetValue(const PlayCmn::tBetHash &pBet, const PlayCmn::qfBetPositions &pPosition) const;
		const PlayCmn::qfBetPositions GetSpinPosition(const quint8 &pSpin) const;
		const bool LastBetContains(const PlayCmn::qfBetPositions &pPosition) const;
		const quint8 LastBetValue(const PlayCmn::qfBetPositions &pPosition) const;
}; // SystemInterface

Q_DECLARE_OPERATORS_FOR_FLAGS(SystemInterface::qfResetContents)

Q_DECLARE_INTERFACE(SystemInterface, SYSTEM_INTERFACE);

#endif // SYSTEMINTERFACE_H