#ifndef UNIBETACTIVECHECKER_H
#define UNIBETACTIVECHECKER_H

#include <QtCore/QThread>
#include <QtGui>
#ifdef Q_WS_WIN
# include <Windows.h>
#endif

class UnibetActiveChecker : public QThread
{
#ifdef Q_WS_WIN
	Q_OBJECT

	public:
		enum eBrowser {
			BrowserUnknown,
			BrowserGoogleChrome,
			BrowserInternetExplorer
		}; // eBrowser
#endif

		struct sActiveData {
			WId wiRouletteChild;
#ifdef Q_WS_WIN
			//HWND hwTopLevel;
#endif
			eBrowser ebBrowser;

			sActiveData() {
				wiRouletteChild = NULL;
				//hwTopLevel = NULL;
				ebBrowser = BrowserUnknown;
			} // sActiveData
		}; // sActiveData

#ifdef Q_WS_WIN
		UnibetActiveChecker();

		virtual void run();

	private:
		static const DWORD CHECK_INTERVAL = 5000;

		static BOOL CALLBACK EnumWindowsProc(__in HWND hwnd, __in LPARAM lParam);

	signals:
		void GameActive(const UnibetActiveChecker::sActiveData &pData) const;
#endif
}; // UnibetActiveChecker

#endif // UNIBETACTIVECHECKER_H