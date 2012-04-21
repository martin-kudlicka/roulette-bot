#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H

#include <QtPlugin>
#include "../../common/playcmn.h"
#include <QtGui/QVBoxLayout>

static const char *SYSTEM_INTERFACE = "System Interface 1.0";

class SystemInterface : public QObject
{
	Q_OBJECT

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
}; // SystemInterface

Q_DECLARE_OPERATORS_FOR_FLAGS(SystemInterface::qfResetContents)

Q_DECLARE_INTERFACE(SystemInterface, SYSTEM_INTERFACE);

#endif // SYSTEMINTERFACE_H