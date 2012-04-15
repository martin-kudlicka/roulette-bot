#include "unibetactivechecker.h"

#ifdef Q_WS_WIN
# define _UNICODE
# include <tchar.h>

LPCTSTR CAPTION_ROULETTE = _T("Roulette");

BOOL CALLBACK UnibetActiveChecker::EnumWindowsProc(__in HWND hwnd, __in LPARAM lParam)
{
	TCHAR tcWindowText[MAX_PATH];
	GetWindowText(hwnd, tcWindowText, sizeof(tcWindowText) / sizeof(TCHAR));

	TCHAR tcRouletteTop[MAX_PATH];
	_tcscpy(tcRouletteTop, CAPTION_ROULETTE);
	_tcscat(tcRouletteTop, _T(" - "));
	bool bRouletteTop = _tcsncmp(tcWindowText, tcRouletteTop, _tcslen(tcRouletteTop)) == 0;
	if (bRouletteTop) {
		// Google Chrome
		HWND hwChrome_WidgetWin_0 = FindWindowEx(hwnd, NULL, _T("Chrome_WidgetWin_0"), CAPTION_ROULETTE);
		if (hwChrome_WidgetWin_0) {
			sActiveData *sadData = reinterpret_cast<sActiveData *>(lParam);
			sadData->wiRouletteChild = FindWindowEx(hwChrome_WidgetWin_0, NULL, _T("Chrome_RenderWidgetHostHWND"), _T(""));
			if (sadData->wiRouletteChild) {
				//sadData->hwTopLevel = hwnd;
				sadData->ebBrowser = BrowserGoogleChrome;
				return FALSE;
			} // if
		} // if

		// Internet Explorer
		HWND hwFrameTab = FindWindowEx(hwnd, NULL, _T("Frame Tab"), _T(""));
		if (hwFrameTab) {
			HWND hwTabWindowClass = FindWindowEx(hwFrameTab, NULL, _T("TabWindowClass"), tcWindowText);
			if (hwTabWindowClass) {
				HWND hwShellDocObjectView = FindWindowEx(hwTabWindowClass, NULL, _T("Shell DocObject View"), _T(""));
				if (hwShellDocObjectView) {
					sActiveData *sadData = reinterpret_cast<sActiveData *>(lParam);
					sadData->wiRouletteChild = FindWindowEx(hwShellDocObjectView, NULL, _T("Internet Explorer_Server"), _T(""));
					if (sadData->wiRouletteChild) {
						//sadData->hwTopLevel = hwnd;
						sadData->ebBrowser = BrowserInternetExplorer;
						return FALSE;
					} // if
				} // if
			} // if
		} // if
	} // if

	return TRUE;
} // EnumWindowsProc

void UnibetActiveChecker::run()
{
	while (true) {
		sActiveData sadData;
		EnumWindows(&UnibetActiveChecker::EnumWindowsProc, reinterpret_cast<LPARAM>(&sadData));

		if (_hwLastChild != sadData.wiRouletteChild) {
			_hwLastChild = sadData.wiRouletteChild;
			emit ActiveChanged(sadData);
		} // if

		Sleep(CHECK_INTERVAL);
	} // while
} // Start

UnibetActiveChecker::UnibetActiveChecker()
{
	_hwLastChild = NULL;

	qRegisterMetaType<sActiveData>("UnibetActiveChecker::sActiveData");
} // UnibetActiveChecker

#endif // Q_WS_WIN