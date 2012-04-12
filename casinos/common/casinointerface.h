#ifndef CASINOINTERFACE_H
#define CASINOINTERFACE_H

#include <QtPlugin>
#include "../../common/playcmn.h"

static const char *CASINO_INTERFACE = "Casino Interface 1.0";

class CasinoInterface : public QObject
{
	Q_OBJECT

	public:
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const = 0;
		virtual const bool GameActive() const = 0;
		virtual const float GetCash() const = 0;
		virtual const QString GetName() const = 0;
		virtual QWidget *GetSettings() = 0;
		virtual const void MakeBet(const PlayCmn::tBetHash &pBet, const int &pTokensPerBet) const = 0;
		virtual const void Reset() = 0;

	signals:
		void GameActiveChanged(const bool &pActive) const;
}; // CasinoInterface

Q_DECLARE_INTERFACE(CasinoInterface, CASINO_INTERFACE);

#endif // CASINOINTERFACE_H