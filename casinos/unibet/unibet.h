#ifndef UNIBET_H
#define UNIBET_H

#include "../common/casinointerface.h"
#ifdef Q_WS_WIN
# include <Windows.h>
#endif
#include <QtGui>
#include "unibetsettings.h"

class Unibet : public CasinoInterface
{
	Q_OBJECT
	Q_INTERFACES(CasinoInterface)

	public:
#ifdef Q_WS_WIN
		static HINSTANCE _hiInstance;
#endif

		Unibet();

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

#ifdef Q_WS_WIN
		static const DWORD CHECK_INTERVAL = 5000;
#endif
		static const int PIXMAP_SCALE = 2;

#ifdef Q_WS_WIN
		bool _bStop;
#endif
		eTokensPosition _etpTokensPosition;
		UnibetSettings _usSettings;
		WId _wiWindow;

		const int CheckForTournaments(const QPixmap &pPixmap) const;
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
#ifdef Q_WS_WIN
		static BOOL CALLBACK EnumWindowsProc(__in HWND hwnd, __in LPARAM lParam);
#endif

		virtual const bool GameActive() const;
		virtual const float GetCash() const;
#ifdef Q_WS_WIN
		static unsigned _stdcall GameCheckThread(void *pContext);
#endif
		virtual const QString GetName() const;
		virtual QWidget *GetSettings();
		const QPixmap GrabWindow(const eGrab &pPart) const;
		virtual const void MakeBet(const PlayCmn::tBetHash &pBet, const int &pTokensPerBet) const;
		virtual const quint8 MakeSpin() const;
		const void MouseClick(const eClick &pClickOn) const;
		const int PercentCount(const int &pValue, const float &pPercent) const;
		const QString Recognize(const QPixmap &pPixmap) const;
		virtual const void Reset();
		const void SelectToken(const UnibetSettings::eTokenValue &pValue) const;
}; // Unibet

#endif // UNIBET_H