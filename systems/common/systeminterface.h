#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H

#include <QtPlugin>
#include "../../common/playcmn.h"

static const char *SYSTEM_INTERFACE = "System Interface 1.0";

class SystemInterface : public QObject
{
	Q_OBJECT

	public:
		enum eSpinResult {
			SpinResultNoBet = 1,
			SpinResultWon = 2,
			SpinResultLost = 4,
			SpinResultProgression = 8
		}; // eSpinResult
		Q_DECLARE_FLAGS(qfSpinResults, eSpinResult)

		virtual const qfSpinResults AnalyzeSpin(const quint8 &pSpin) = 0;
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const = 0;
		virtual const PlayCmn::tBetHash GetBet() = 0;
		virtual const QString GetName() const = 0;
		virtual QWidget *GetSettings() = 0;
		virtual const void Reset() = 0;
}; // SystemInterface

Q_DECLARE_OPERATORS_FOR_FLAGS(SystemInterface::qfSpinResults)

Q_DECLARE_INTERFACE(SystemInterface, SYSTEM_INTERFACE);

#endif // SYSTEMINTERFACE_H