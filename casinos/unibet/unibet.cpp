#include "unibet.h"

#ifdef Q_WS_WIN
# include <process.h>
#endif
#undef MAX_PATH
#include "../../3rdparty/tesseract/api/baseapi.h"
#include "../../3rdparty/tesseract/vs2010/include/leptonica/allheaders.h"
#include "../../3rdparty/tesseract/ccutil/strngs.h"
#include "unibetsettingswidget.h"
#include <QTest>

#ifdef Q_WS_WIN
HINSTANCE Unibet::_hiInstance = NULL;

BOOL WINAPI DllMain(__in HINSTANCE hinstDLL, __in DWORD fdwReason, __in LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		Unibet::_hiInstance = hinstDLL;
	} // if

	return TRUE;
} // DllMain
#endif

const quint16 Unibet::CheckForTournaments(const QPixmap &pPixmap) const
{
	QImage qiImage = pPixmap.toImage();

	quint16 qui16Tournaments = 0;
	do {
		QRgb qrgbRgb = qiImage.pixel(qiImage.width() - qui16Tournaments - 1, qiImage.height() / 2);
		if (qrgbRgb == 0xFF1F1F1F) {
			qui16Tournaments++;
		} else {
			break;
		} // if else
	} while (true);

	return qui16Tournaments;
} // CheckForTournaments

const void Unibet::CloseSettings(const QWidget *pSettings, const bool &pSave) const
{
	const UnibetSettingsWidget *uswSettings = qobject_cast<const UnibetSettingsWidget *>(pSettings);

	if (pSave) {
		uswSettings->SaveSettings();
	} // if

	delete uswSettings;
} // CloseSettings

const bool Unibet::GameActive() const
{
	return _sadActiveData.wiRouletteChild != NULL;
} // GameActive

const float Unibet::GetCash() const
{
	QPixmap qpPixmap = GrabWindow(GrabCash);
	QString qsCash = Recognize(qpPixmap);

	return qsCash.toFloat();
} // GetCash

#ifdef Q_WS_WIN
const bool Unibet::GameReady(const WId &pWindow) const
{
	QPixmap qpAll = QPixmap::grabWindow(pWindow);
	quint16 qui16TournamentsWidth = CheckForTournaments(qpAll);

	quint16 iX = PercentCount(qpAll.width() - qui16TournamentsWidth, 81.5);
	quint16 iY = PercentCount(qpAll.height(), 88.5);

	QImage qiImage = qpAll.toImage();
	QRgb qrgbRgb = qiImage.pixel(iX, iY);

	return qrgbRgb == 0xFFAEAEAE;
} // GameReady
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
	QPixmap qpAll = QPixmap::grabWindow(_sadActiveData.wiRouletteChild);
	quint16 qui16TournamentsWidth = CheckForTournaments(qpAll);

	quint16 qui16PartHeight, qui16PartWidth, qui16PartX, qui16PartY;
	switch (pPart) {
		case GrabCash:
			qui16PartX = PercentCount(qpAll.width() - qui16TournamentsWidth, 39.4);
			qui16PartY = PercentCount(qpAll.height(), 90.5);
			qui16PartWidth = PercentCount(qpAll.width() - qui16TournamentsWidth, 5.1);
			qui16PartHeight = PercentCount(qpAll.height(), 2.5);
			break;
		case GrabSpinResult:
			qui16PartX = PercentCount(qpAll.width() - qui16TournamentsWidth, 13);
			qui16PartY = PercentCount(qpAll.height(), 59);
			qui16PartWidth = PercentCount(qpAll.width() - qui16TournamentsWidth, 9.5);
			qui16PartHeight = PercentCount(qpAll.height(), 7.2);
	} // switch

	return qpAll.copy(qui16PartX, qui16PartY, qui16PartWidth, qui16PartHeight);
} // GrabWindow

const void Unibet::MakeBet(const PlayCmn::tBetHash &pBet, const quint8 &pTokensPerBet)
{
	for (PlayCmn::tBetHash::const_iterator ciBet = pBet.constBegin(); ciBet != pBet.constEnd(); ciBet++) {
		for (quint8 qui8Token = 0; qui8Token < pTokensPerBet * ciBet.value(); qui8Token++) {
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

			Wait(100, 200);
		} // for
	} // for
} // MakeBet

const quint8 Unibet::MakeSpin() const
{
	MouseClick(ClickFastSpin);
	Wait(750, 1000);

	QPixmap qpSpin = GrabWindow(GrabSpinResult);
	QString qsSpin = Recognize(qpSpin);

	return qsSpin.toUInt();
} // MakeSpin

const void Unibet::MouseClick(const eClick &pClickOn) const
{
	QPixmap qpAll = QPixmap::grabWindow(_sadActiveData.wiRouletteChild);
	quint16 qui16TournamentsWidth = CheckForTournaments(qpAll);

	quint16 qui16X, qui16Y;
	switch (pClickOn) {
		case ClickFastSpin:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 45);
			qui16Y = PercentCount(qpAll.height(), 83);
			break;
		case ClickPositionColumn1:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 88.5);
			qui16Y = PercentCount(qpAll.height(), 71.5);
			break;
		case ClickPositionColumn2:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 92);
			qui16Y = PercentCount(qpAll.height(), 67);
			break;
		case ClickPositionColumn3:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 95);
			qui16Y = PercentCount(qpAll.height(), 61);
			break;
		case ClickRemoveBet:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 66);
			qui16Y = PercentCount(qpAll.height(), 83);
			break;
		case ClickTokensLeft:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 77.5);
			qui16Y = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokensRight:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 98.5);
			qui16Y = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokenPosition1:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 81);
			qui16Y = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokenPosition2:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 86);
			qui16Y = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokenPosition3:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 91); // 580
			qui16Y = PercentCount(qpAll.height(), 90);
			break;
		case ClickTokenPosition4:
			qui16X = PercentCount(qpAll.width() - qui16TournamentsWidth, 95.5); // 610
			qui16Y = PercentCount(qpAll.height(), 90);
	} // switch

#ifdef Q_WS_WIN
	/*SendMessage(_sadActiveData.wiRouletteChild, WM_MOUSEACTIVATE, reinterpret_cast<WPARAM>(_sadActiveData.hwTopLevel), MAKELONG(HTCLIENT, WM_LBUTTONDOWN));
	SendMessage(_sadActiveData.wiRouletteChild, WM_SETCURSOR, reinterpret_cast<WPARAM>(_sadActiveData.wiRouletteChild), MAKELONG(HTCLIENT, WM_LBUTTONDOWN));
	PostMessage(_sadActiveData.wiRouletteChild, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(qui16X, qui16Y));
	Wait(50, 100);
	PostMessage(_sadActiveData.wiRouletteChild, WM_LBUTTONUP, 0, MAKELONG(qui16X, qui16Y));*/
	POINT pOldPos;
	GetCursorPos(&pOldPos);
	POINT pPos;
	pPos.x = qui16X;
	pPos.y = qui16Y;
	ClientToScreen(_sadActiveData.wiRouletteChild, &pPos);
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

	if (_sadActiveData.ebBrowser == UnibetActiveChecker::BrowserInternetExplorer) {
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

#ifdef Q_WS_WIN
const void Unibet::on_uacChecker_GameActive(const UnibetActiveChecker::sActiveData &pData)
{
	HWND hwLastChild = _sadActiveData.wiRouletteChild;

	if (pData.wiRouletteChild && GameReady(pData.wiRouletteChild)) {
		_sadActiveData = pData;
	} else {
		_sadActiveData = UnibetActiveChecker::sActiveData();
	} // if else

	if (static_cast<bool>(hwLastChild) ^ static_cast<bool>(_sadActiveData.wiRouletteChild)) {
		emit GameActiveChanged(pData.wiRouletteChild);
	} // if
} // on_uacChecker_ActiveChanged
#endif

const quint16 Unibet::PercentCount(const quint16 &pValue, const float &pPercent) const
{
	return static_cast<float>(pValue) / 100 * pPercent;
} // PercentCount

const void Unibet::ProcessSpinResult(const PlayCmn::sSpinResult &pResult, const quint8 &pTokensPerBet)
{
} // ProcessSpinResult

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
	Wait(100, 200);
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
				MouseClick(ClickTokenPosition2);
			} else {
				MouseClick(ClickTokenPosition3);
			} // if else
			break;
		case UnibetSettings::TokenValue3:
			if (_etpTokensPosition == TokensPositionLeft) {
				MouseClick(ClickTokenPosition3);
			} else {
				MouseClick(ClickTokenPosition4);
			} // if else
			break;
		case UnibetSettings::TokenValue4:
			MouseClick(ClickTokenPosition4);
	} // switch
} // SelectToken

#ifdef Q_WS_WIN
Unibet::Unibet() : CasinoInterface()
{
	connect(&_uacChecker, SIGNAL(GameActive(const UnibetActiveChecker::sActiveData &)), SLOT(on_uacChecker_GameActive(const UnibetActiveChecker::sActiveData &)));
	_uacChecker.start();
} // Unibet
#endif

const void Unibet::Wait(const quint16 &pMin, const quint16 &pMax) const
{
	quint16 qui16Wait = (qrand() % (pMax - pMin)) + pMin;
	QTest::qWait(qui16Wait);
} // Wait

Q_EXPORT_PLUGIN2(unibet, Unibet)