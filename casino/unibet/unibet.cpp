#include "unibet.h"

#ifdef Q_WS_WIN
# include <process.h>
# define _UNICODE
# include <tchar.h>

LPCTSTR CAPTION_ROULETTE = _T("Roulette");

BOOL CALLBACK Unibet::EnumWindowsProc(__in HWND hwnd, __in LPARAM lParam)
{
	TCHAR tcWindowText[MAX_PATH];
	GetWindowText(hwnd, tcWindowText, sizeof(tcWindowText) / sizeof(TCHAR));

	bool bRoulette = _tcsncmp(tcWindowText, CAPTION_ROULETTE, _tcslen(CAPTION_ROULETTE)) == 0;
	if (bRoulette) {
		HWND hwRoulette = FindWindowEx(hwnd, NULL, NULL, CAPTION_ROULETTE);
		if (hwRoulette) {
			*reinterpret_cast<bool *>(lParam) = true;
			return FALSE;
		} // if
	} // if

	return TRUE;
} // EnumWindowsProc
#endif

const bool Unibet::GameActive() const
{
	return _bActive;
} // GameActive

#ifdef Q_WS_WIN
unsigned _stdcall Unibet::GameCheckThread(void *pContext)
{
	Unibet *uUnibet = static_cast<Unibet *>(pContext);
	while (!uUnibet->_bStop) {
		bool bFound = false;
		EnumWindows(&Unibet::EnumWindowsProc, reinterpret_cast<LPARAM>(&bFound));

		if (uUnibet->_bActive != bFound) {
			uUnibet->_bActive = bFound;
			emit uUnibet->GameActiveChanged(bFound);
		} // if

		Sleep(uUnibet->CHECK_INTERVAL);
	} // while

	return TRUE;
} // GameCheckThread
#endif

const QString Unibet::GetName() const
{
	return "Unibet";
} // GetName

Unibet::Unibet() : CasinoInterface()
{
	_bActive = false;
#ifdef Q_WS_WIN
	_bStop = false;

	_uiptCheckThread = _beginthreadex(NULL, 0, &Unibet::GameCheckThread, this, 0, NULL);
#endif
} // Unibet

Q_EXPORT_PLUGIN2(unibet, Unibet)