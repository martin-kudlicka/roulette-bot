#ifndef SPINGENERATOR_H
#define SPINGENERATOR_H

#include "../common/casinointerface.h"
#include "spingeneratorsettings.h"

class SpinGenerator : public CasinoInterface
{
	Q_OBJECT
	Q_INTERFACES(CasinoInterface)

	public:
		SpinGenerator();

	private:
		float _fCash;
		quint8 _qui8Bet;
		SpinGeneratorSettings _sgsSettings;

		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual const bool GameActive() const;
		virtual const float GetCash() const;
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		virtual const void MakeBet(const PlayCmn::tBetHash &pBet, const quint8 &pTokensPerBet);
		virtual const quint8 MakeSpin() const;
		virtual const void ProcessSpinResult(const PlayCmn::sSpinResult &pResult, const quint8 &pTokensPerBet);
		virtual const void RemoveBet() const;
		virtual const void Reset();
}; // SpinGenerator

#endif // SPINGENERATOR_H