#ifndef UNIBET_H
#define UNIBET_H

#include "../common/casinointerface.h"
#ifdef Q_WS_WIN
# include <Windows.h>
#endif

class Unibet : public CasinoInterface
{
	Q_OBJECT
	Q_INTERFACES(CasinoInterface)

	public:
		Unibet();

	private:
#ifdef Q_WS_WIN
		static const DWORD CHECK_INTERVAL = 5000;
#endif

		bool _bActive;
#ifdef Q_WS_WIN
		bool _bStop;
		uintptr_t _uiptCheckThread;

		static BOOL CALLBACK EnumWindowsProc(__in HWND hwnd, __in LPARAM lParam);
#endif

		virtual const bool GameActive() const;
#ifdef Q_WS_WIN
		static unsigned _stdcall GameCheckThread(void *pContext);
#endif
		virtual const QString GetName() const;
}; // Unibet

#endif // UNIBET_H