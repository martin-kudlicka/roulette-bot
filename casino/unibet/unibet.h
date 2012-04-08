#ifndef UNIBET_H
#define UNIBET_H

#include "../common/casinointerface.h"
#ifdef Q_WS_WIN
# include <Windows.h>
#endif
#include <QtGui>

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
		enum eGrab {
			GrabCash
		}; // eGrab

#ifdef Q_WS_WIN
		static const DWORD CHECK_INTERVAL = 5000;
#endif
		static const int PIXMAP_SCALE = 2;

#ifdef Q_WS_WIN
		bool _bStop;
#endif
		WId _wiWindow;

#ifdef Q_WS_WIN
		static BOOL CALLBACK EnumWindowsProc(__in HWND hwnd, __in LPARAM lParam);
#endif

		virtual const bool GameActive() const;
		virtual const float GetCash() const;
#ifdef Q_WS_WIN
		static unsigned _stdcall GameCheckThread(void *pContext);
#endif
		virtual const QString GetName() const;
		const QPixmap GrabWindow(const eGrab &pPart) const;
		const QString Recognize(const QPixmap &pPixmap) const;
}; // Unibet

#endif // UNIBET_H