#include "unibet.h"

#ifdef Q_WS_WIN
# include <process.h>
# define _UNICODE
# include <tchar.h>
#endif
#undef MAX_PATH
#include "../../3rdparty/tesseract/api/baseapi.h"
#include "../../3rdparty/tesseract/vs2010/include/leptonica/allheaders.h"
#include "../../3rdparty/tesseract/ccutil/strngs.h"
#include "unibetsettingswidget.h"

#ifdef Q_WS_WIN
LPCTSTR CAPTION_ROULETTE = _T("Roulette");

HINSTANCE Unibet::_hiInstance = NULL;

BOOL WINAPI DllMain(__in HINSTANCE hinstDLL, __in DWORD fdwReason, __in LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		Unibet::_hiInstance = hinstDLL;
	} // if

	return TRUE;
} // DllMain

const void Unibet::CloseSettings(const QWidget *pSettings, const bool &pSave) const
{
	const UnibetSettingsWidget *uswSettings = qobject_cast<const UnibetSettingsWidget *>(pSettings);

	if (pSave) {
		uswSettings->SaveSettings();
	} // if

	delete uswSettings;
} // CloseSettings

BOOL CALLBACK Unibet::EnumWindowsProc(__in HWND hwnd, __in LPARAM lParam)
{
	TCHAR tcWindowText[MAX_PATH];
	GetWindowText(hwnd, tcWindowText, sizeof(tcWindowText) / sizeof(TCHAR));

	bool bRoulette = _tcsncmp(tcWindowText, CAPTION_ROULETTE, _tcslen(CAPTION_ROULETTE)) == 0;
	if (bRoulette) {
		HWND *hwRoulette = reinterpret_cast<HWND *>(lParam);
		*hwRoulette = FindWindowEx(hwnd, NULL, NULL, CAPTION_ROULETTE);
		if (*hwRoulette) {
			return FALSE;
		} // if
	} // if

	return TRUE;
} // EnumWindowsProc
#endif

const bool Unibet::GameActive() const
{
	return _wiWindow != NULL;
} // GameActive

const float Unibet::GetCash() const
{
	QPixmap qpPixmap = GrabWindow(GrabCash);
	QString qsCash = Recognize(qpPixmap);

	return qsCash.toFloat();
} // GetCash

#ifdef Q_WS_WIN
unsigned _stdcall Unibet::GameCheckThread(void *pContext)
{
	Unibet *uUnibet = static_cast<Unibet *>(pContext);
	while (!uUnibet->_bStop) {
		HWND hwRoulette = NULL;
		EnumWindows(&Unibet::EnumWindowsProc, reinterpret_cast<LPARAM>(&hwRoulette));

		if (uUnibet->_wiWindow != hwRoulette) {
			if (static_cast<bool>(uUnibet->_wiWindow) ^ static_cast<bool>(hwRoulette)) {
				emit uUnibet->GameActiveChanged(hwRoulette);
			} // if
			uUnibet->_wiWindow = hwRoulette;
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

QWidget *Unibet::GetSettings()
{
	return new UnibetSettingsWidget(&_usSettings);
} // GetSettings

const QPixmap Unibet::GrabWindow(const eGrab &pPart) const
{
	QPixmap qpAll = QPixmap::grabWindow(_wiWindow);

	int iPartHeight, iPartWidth, iPartX, iPartY;
	switch (pPart) {
		case GrabCash:
			iPartX = static_cast<float>(qpAll.width()) / 100 * 39;
			iPartY = static_cast<float>(qpAll.height()) / 100 * 90.5;
			iPartWidth = static_cast<float>(qpAll.width()) / 100 * 6;
			iPartHeight = static_cast<float>(qpAll.height()) / 100 * 2.5;
	} // switch

	return qpAll.copy(iPartX, iPartY, iPartWidth, iPartHeight);
} // GrabWindow

const QString Unibet::Recognize(const QPixmap &pPixmap) const
{
	QPixmap qpScaled = pPixmap.scaled(pPixmap.size() * PIXMAP_SCALE, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

	tesseract::TessBaseAPI tbaTesseract;
#ifdef Q_WS_WIN
	char cFilePath[MAX_PATH];
	GetModuleFileNameA(Unibet::_hiInstance, cFilePath, sizeof(cFilePath));
#endif
	tbaTesseract.Init(
#ifdef Q_WS_WIN
		cFilePath,
#else
		NULL,
#endif
		NULL);

	QTemporaryFile qtfTempFile;
	qtfTempFile.open();
	qpScaled.save(qtfTempFile.fileName(), "PNG");

	STRING sText;
	tbaTesseract.ProcessPages(qtfTempFile.fileName().toLocal8Bit(), NULL, 0, &sText);

	return sText.string();
} // Recognize

Unibet::Unibet() : CasinoInterface()
{
#ifdef Q_WS_WIN
	_bStop = false;
#endif
	_wiWindow = NULL;

#ifdef Q_WS_WIN
	_beginthreadex(NULL, 0, &Unibet::GameCheckThread, this, 0, NULL);
#endif
} // Unibet

Q_EXPORT_PLUGIN2(unibet, Unibet)