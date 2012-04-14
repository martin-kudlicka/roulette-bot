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
#include <QTest>

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

const int Unibet::CheckForTournaments(const QPixmap &pPixmap) const
{
	QImage qiImage = pPixmap.toImage();

	int iTournaments = 0;
	do {
		QRgb qrgbRgb = qiImage.pixel(qiImage.width() - iTournaments - 1, qiImage.height() / 2);
		if (qrgbRgb == 0xFF1F1F1F) {
			iTournaments++;
		} else {
			break;
		} // if else
	} while (true);

	return iTournaments;
} // CheckForTournaments

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

	TCHAR tcRouletteTop[MAX_PATH];
	_tcscpy(tcRouletteTop, CAPTION_ROULETTE);
	_tcscat(tcRouletteTop, _T(" - "));
	bool bRouletteTop = _tcsncmp(tcWindowText, tcRouletteTop, _tcslen(tcRouletteTop)) == 0;
	if (bRouletteTop) {
		// Google Chrome
		HWND hwChrome_WidgetWin_0 = FindWindowEx(hwnd, NULL, _T("Chrome_WidgetWin_0"), CAPTION_ROULETTE);
		if (hwChrome_WidgetWin_0) {
			sEnumWindowsData *sewdData = reinterpret_cast<sEnumWindowsData *>(lParam);
			sewdData->hwRouletteChild = FindWindowEx(hwChrome_WidgetWin_0, NULL, _T("Chrome_RenderWidgetHostHWND"), _T(""));
			if (sewdData->hwRouletteChild) {
				//sewdData->hwTopLevel = hwnd;
				sewdData->ebBrowser = BrowserGoogleChrome;
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
					sEnumWindowsData *sewdData = reinterpret_cast<sEnumWindowsData *>(lParam);
					sewdData->hwRouletteChild = FindWindowEx(hwShellDocObjectView, NULL, _T("Internet Explorer_Server"), _T(""));
					if (sewdData->hwRouletteChild) {
						//sewdData->hwTopLevel = hwnd;
						sewdData->ebBrowser = BrowserInternetExplorer;
						return FALSE;
					} // if
				} // if
			} // if
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
		sEnumWindowsData sewdData;
		EnumWindows(&Unibet::EnumWindowsProc, reinterpret_cast<LPARAM>(&sewdData));

		if (uUnibet->_wiWindow != sewdData.hwRouletteChild) {
			if (static_cast<bool>(uUnibet->_wiWindow) ^ static_cast<bool>(sewdData.hwRouletteChild)) {
				emit uUnibet->GameActiveChanged(sewdData.hwRouletteChild);
			} // if
			uUnibet->_wiWindow = sewdData.hwRouletteChild;
			//uUnibet->_wiTopLevelWindow = GetParent(GetParent(sewdData.hwTopLevel));
			uUnibet->_ebBrowser = sewdData.ebBrowser;
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

	int iTournamentsWidth = CheckForTournaments(qpAll);

	int iPartHeight, iPartWidth, iPartX, iPartY;
	switch (pPart) {
		case GrabCash:
			iPartX = PercentCount(qpAll.width() - iTournamentsWidth, 39);
			iPartY = PercentCount(qpAll.height(), 90.5);
			iPartWidth = PercentCount(qpAll.width() - iTournamentsWidth, 6);
			iPartHeight = PercentCount(qpAll.height(), 2.5);
			break;
		case GrabSpinResult:
			iPartX = PercentCount(qpAll.width() - iTournamentsWidth, 13);
			iPartY = PercentCount(qpAll.height(), 59);
			iPartWidth = PercentCount(qpAll.width() - iTournamentsWidth, 9.5);
			iPartHeight = PercentCount(qpAll.height(), 7.2);
	} // switch

	return qpAll.copy(iPartX, iPartY, iPartWidth, iPartHeight);
} // GrabWindow

const void Unibet::MakeBet(const PlayCmn::tBetHash &pBet, const int &pTokensPerBet) const
{
	for (PlayCmn::tBetHash::const_iterator ciBet = pBet.constBegin(); ciBet != pBet.constEnd(); ciBet++) {
		for (int iToken = 0; iToken < pTokensPerBet; iToken++) {
			switch (ciBet.key()) {
				case PlayCmn::BetPositionColumn1:
					MouseClick(ClickPositionColumn1);
					break;
				case PlayCmn::BetPositionColumn2:
					MouseClick(ClickPositionColumn2);
					break;
				case PlayCmn::BetPositionColumn3:
					MouseClick(ClickPositionColumn3);
			} // switch

			Wait(200, 500);
		} // for
	} // for
} // MakeBet

const quint8 Unibet::MakeSpin() const
{
	MouseClick(ClickFastSpin);
	Wait(1000, 2000);

	QPixmap qpSpin = GrabWindow(GrabSpinResult);
	QString qsSpin = Recognize(qpSpin);

	return qsSpin.toUInt();
} // MakeSpin

const void Unibet::MouseClick(const eClick &pClickOn) const
{
	QPixmap qpAll = QPixmap::grabWindow(_wiWindow);
	int iTournamentsWidth = CheckForTournaments(qpAll);

	int iX, iY;
	switch (pClickOn) {
		case ClickFastSpin:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 45);
			iY = PercentCount(qpAll.height(), 83);
			break;
		case ClickPositionColumn1:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 88.5);
			iY = PercentCount(qpAll.height(), 71.5);
			break;
		case ClickPositionColumn2:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 92);
			iY = PercentCount(qpAll.height(), 67);
			break;
		case ClickPositionColumn3:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 95);
			iY = PercentCount(qpAll.height(), 61);
			break;
		case ClickRemoveBet:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 66);
			iY = PercentCount(qpAll.height(), 83);
			break;
		case ClickTokensLeft:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 77.5);
			iY = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokensRight:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 98.5);
			iY = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokenPosition1:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 81);
			iY = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokenPosition2:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 86);
			iY = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokenPosition3:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 91); // 580
			iY = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokenPosition4:
			iX = PercentCount(qpAll.width() - iTournamentsWidth, 95.5); // 610
			iY = PercentCount(qpAll.height(), 90);
	} // switch

#ifdef Q_WS_WIN
	/*SendMessage(_wiWindow, WM_MOUSEACTIVATE, reinterpret_cast<WPARAM>(_wiTopLevelWindow), MAKELONG(HTCLIENT, WM_LBUTTONDOWN));
	SendMessage(_wiWindow, WM_SETCURSOR, reinterpret_cast<WPARAM>(_wiWindow), MAKELONG(HTCLIENT, WM_LBUTTONDOWN));
	PostMessage(_wiWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(iX, iY));
	Wait(50, 100);
	PostMessage(_wiWindow, WM_LBUTTONUP, 0, MAKELONG(iX, iY));*/
	POINT pOldPos;
	GetCursorPos(&pOldPos);
	POINT pPos;
	pPos.x = iX;
	pPos.y = iY;
	ClientToScreen(_wiWindow, &pPos);
	SetCursorPos(pPos.x, pPos.y);
	HWND hwForegroundWindow = GetForegroundWindow();

	INPUT iInput;
	ZeroMemory(&iInput, sizeof(iInput));
	iInput.type = INPUT_MOUSE;
	iInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &iInput, sizeof(iInput));

	Wait(50, 100);

	ZeroMemory(&iInput, sizeof(iInput));
	iInput.type = INPUT_MOUSE;
	iInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &iInput, sizeof(iInput));

	Wait(50, 100);

	if (_ebBrowser == BrowserInternetExplorer) {
		ZeroMemory(&iInput, sizeof(iInput));
		iInput.type = INPUT_MOUSE;
		iInput.mi.dx = 1;
		iInput.mi.dy = 1;
		iInput.mi.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &iInput, sizeof(iInput));

		Wait(50, 100);
	} // if

	SetCursorPos(pOldPos.x, pOldPos.y);
	SetForegroundWindow(hwForegroundWindow);
#endif
} // MouseClick

const int Unibet::PercentCount(const int &pValue, const float &pPercent) const
{
	return static_cast<float>(pValue) / 100 * pPercent;
} // PercentCount

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
	tbaTesseract.SetPageSegMode(tesseract::PSM_SINGLE_LINE);

	QTemporaryFile qtfTempFile;
	qtfTempFile.open();
	qpScaled.save(qtfTempFile.fileName(), "PNG");

	STRING sText;
	tbaTesseract.ProcessPages(qtfTempFile.fileName().toLocal8Bit(), NULL, 0, &sText);

	return sText.string();
} // Recognize

const void Unibet::RemoveBet() const
{
	MouseClick(ClickRemoveBet);
	Wait(250, 500);
} // RemoveBet

const void Unibet::Reset()
{
	_etpTokensPosition = TokensPositionUnknown;

	RemoveBet();
	SelectToken(_usSettings.GetTokenValue());
} // Reset

const void Unibet::SelectToken(const UnibetSettings::eTokenValue &pValue) const
{
	if ((_etpTokensPosition == TokensPositionUnknown && pValue != UnibetSettings::TokenValue4) || (_etpTokensPosition == TokensPositionRight && pValue == UnibetSettings::TokenValue1)) {
		MouseClick(ClickTokensLeft);
	} else {
		if (_etpTokensPosition == TokensPositionUnknown || (_etpTokensPosition == TokensPositionLeft && pValue == UnibetSettings::TokenValue4)) {
			MouseClick(ClickTokensRight);
		} // if
	} // if else

	switch (pValue) {
		case UnibetSettings::TokenValue1:
			MouseClick(ClickTokenPosition2);
			break;
		case UnibetSettings::TokenValue2:
			if (_etpTokensPosition == TokensPositionLeft) {
				MouseClick(ClickTokenPosition3);
			} else {
				MouseClick(ClickTokenPosition2);
			} // if else
			break;
		case UnibetSettings::TokenValue3:
			if (_etpTokensPosition == TokensPositionLeft) {
				MouseClick(ClickTokenPosition4);
			} else {
				MouseClick(ClickTokenPosition3);
			} // if else
			break;
		case UnibetSettings::TokenValue4:
			MouseClick(ClickTokenPosition4);
	} // switch
} // SelectToken

Unibet::Unibet() : CasinoInterface()
{
#ifdef Q_WS_WIN
	_bStop = false;
#endif
	_ebBrowser = BrowserUnknown;
	//_wiTopLevelWindow = NULL;
	_wiWindow = NULL;

#ifdef Q_WS_WIN
	_beginthreadex(NULL, 0, &Unibet::GameCheckThread, this, 0, NULL);
#endif
} // Unibet

const void Unibet::Wait(const int &pMin, const int &pMax) const
{
	int iWait = (qrand() % (pMax - pMin)) + pMin;
	QTest::qWait(iWait);
	qDebug("%d", iWait);
} // Wait

Q_EXPORT_PLUGIN2(unibet, Unibet)