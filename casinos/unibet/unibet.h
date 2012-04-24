#ifndef UNIBET_H
#define UNIBET_H

#include "../common/casinointerface.h"
#include "unibetsettings.h"
#ifdef Q_WS_WIN
# include "unibetactivechecker.h"
#endif

class Unibet : public CasinoInterface
{
	Q_OBJECT
	Q_INTERFACES(CasinoInterface)

	public:
#ifdef Q_WS_WIN
		static HINSTANCE _hiInstance;

		Unibet();
#endif

	private:
		enum eClick {
			ClickFastSpin,
			ClickPositionColumn1,
			ClickPositionColumn2,
			ClickPositionColumn3,
			ClickRemoveBet,
			ClickTokensLeft,
			ClickTokensRight,
			ClickTokenPosition1,
			ClickTokenPosition2,
			ClickTokenPosition3,
			ClickTokenPosition4
		}; // eClick
		enum eGrab {
			GrabCash,
			GrabSpinResult
		}; // eGrab
		enum eTokensPosition {
			TokensPositionUnknown,
			TokensPositionLeft,
			TokensPositionRight
		}; // eTokensPosition

		static const quint8 PIXMAP_SCALE = 4;

		eTokensPosition _etpTokensPosition;
		UnibetActiveChecker::sActiveData _sadActiveData;
		UnibetActiveChecker _uacChecker;
		UnibetSettings _usSettings;

		const quint16 CheckForTournaments(const QPixmap &pPixmap) const;
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual const bool GameActive() const;
		virtual const float GetCash() const;
#ifdef Q_WS_WIN
		const bool GameReady(const WId &pWindow) const;
#endif
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		const QPixmap GrabWindow(const eGrab &pPart) const;
		virtual const void MakeBet(const PlayCmn::tBetHash &pBet, const quint8 &pTokensPerBet);
		virtual const quint8 MakeSpin() const;
		const void MouseClick(const eClick &pClickOn) const;
		const quint16 PercentCount(const quint16 &pValue, const float &pPercent) const;
		virtual const void ProcessSpinResult(const PlayCmn::sSpinResult &pResult, const quint8 &pTokensPerBet);
		const QString Recognize(const QPixmap &pPixmap) const;
		virtual const void RemoveBet() const;
		virtual const void Reset();
		const void SelectToken(const UnibetSettings::eTokenValue &pValue) const;
		const void Wait(const quint16 &pMin, const quint16 &pMax) const;

#ifdef Q_WS_WIN
	private slots:
		const void on_uacChecker_GameActive(const UnibetActiveChecker::sActiveData &pData);
#endif
}; // Unibet

#endif // UNIBET_H