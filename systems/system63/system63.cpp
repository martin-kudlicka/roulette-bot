#include "system63.h"

#include "system63settingswidget.h"

const void System63::AddToLastBet(const PlayCmn::tBetHash &pBet)
{
	for (PlayCmn::tBetHash::const_iterator ciBet = pBet.constBegin(); ciBet != pBet.constEnd(); ciBet++) {
		int iValue;
		if (_tbhLastBet.contains(ciBet.key())) {
			iValue = _tbhLastBet.value(ciBet.key());
		} else {
			iValue = 0;
		} // if else

		iValue += ciBet.value();
		_tbhLastBet.insert(ciBet.key(), iValue);
	} // for
} // AddToLastBet

const void System63::AddToResult(PlayCmn::sSpinResult *pResult, const PlayCmn::sSpinResult &pAdd) const
{
	pResult->esrtType |= pAdd.esrtType;
	pResult->iBetProfit += pAdd.iBetProfit;
} // AddToResult

const PlayCmn::sSpinResult System63::AnalyzeSpin(const PlayCmn::tBetHash &pBet, const PlayCmn::eBetPosition pPosition, int *pSameBeforeBet, const PlayCmn::eBetPosition &pCheckToLastPosition, PlayCmn::eBetPosition *pLastPosition, int *pSameProgression, PlayCmn::eBetPosition *pLastProgressionPosition, quint8 *pProgressionIndex, int *pSameInRow, int *pMaxSameInRow)
{
	PlayCmn::sSpinResult srResult;

	do {
		if (pBet.isEmpty()) {
			// no bet made
			srResult.esrtType = PlayCmn::SpinResultTypeNoBet;
			srResult.iBetProfit = 0;

			if (*pSameBeforeBet < _s63sSettings.GetSameDozenColumnBeforeBet()) {
				if (pCheckToLastPosition == pPosition || pCheckToLastPosition == PlayCmn::BetPositionNone) {
					(*pSameBeforeBet)++;
				} else {
					if (pCheckToLastPosition != pPosition) {
						*pSameBeforeBet = 0;
					} else {
						*pSameBeforeBet = 1;
					} // if else
				} // if else

				break;
			} // if

			if (*pSameProgression < _s63sSettings.GetSameDozenColumnProgression()) {
				if (_s63sSettings.GetProgressionDozenColumnNotChanged()) {
					if (pCheckToLastPosition == pPosition) {
						(*pSameProgression)++;
					} else {
						srResult.esrtType |= PlayCmn::SpinResultTypeLost;
						if (pCheckToLastPosition != pPosition) {
							*pSameBeforeBet = 0;
						} else {
							*pSameBeforeBet = 1;
						} // if else
						*pSameProgression = 0;
						*pProgressionIndex = 0;
					} // if else
				} else {
					if (*pSameProgression == 0 || *pLastProgressionPosition != pPosition) {
						*pLastProgressionPosition = pPosition;
						if (pCheckToLastPosition != pPosition) {
							*pSameProgression = 0;
						} else {
							*pSameProgression = 1;
						} // if else
					} else {
						(*pSameProgression)++;
					} // if else
				} // if else

				break;
			} // if
		} else {
			// bet made
			if (pBet.contains(pPosition)) {
				// won
				srResult.esrtType = PlayCmn::SpinResultTypeWon;
				srResult.iBetProfit = pBet.value(pPosition) * 3;

				*pSameBeforeBet = 0;
				*pSameProgression = 0;
				*pProgressionIndex = 0;

				break;
			} else {
				// lost or progression
				*pSameProgression = 0;

				if (*pProgressionIndex == _qlProgressionSequence.size() - 1) {
					srResult.esrtType = PlayCmn::SpinResultTypeLost;

					*pSameBeforeBet = 0;
					*pProgressionIndex = 0;
				} else {
					srResult.esrtType = PlayCmn::SpinResultTypeProgression;

					(*pProgressionIndex)++;
				} // if else
				srResult.iBetProfit = 0;

				break;
			} // if else
		} // if else
	} while (false);

	(*pSameInRow)++;
	if (*pLastPosition != pPosition) {
		if (*pMaxSameInRow < *pSameInRow) {
			_s63swStatistics.SetMaxSameInRow(*pSameInRow);
			*pMaxSameInRow = *pSameInRow;
		} // if
		if (*pSameInRow < System63StatisticsWidget::CounterMoreSameInRow) {
			_s63swStatistics.Increment(static_cast<System63StatisticsWidget::eCounter>(System63StatisticsWidget::Counter1SameInRow + *pSameInRow - 1));
		} else {
			_s63swStatistics.Increment(System63StatisticsWidget::CounterMoreSameInRow);
		} // if else
		*pSameInRow = 0;

		*pLastPosition = pPosition;
	} // if

	return srResult;
} // AnalyzeSpin

const PlayCmn::sSpinResult System63::AnalyzeSpin(const quint8 &pSpin)
{
	PlayCmn::sSpinResult srResult;
	srResult.esrtType = PlayCmn::SpinResultTypeNone;
	srResult.iBetProfit = 0;

	if (_s63sSettings.GetBetOn() == System63Settings::BetOnRandom) {
		PlayCmn::eBetPosition ebpPosition = GetSpinPosition(pSpin, _edctLastBetRandom);
		srResult = AnalyzeSpin(_tbhLastBet, ebpPosition, &_iSameRandomBeforeBet, _ebpLastPositionRandom, &_ebpLastPositionRandom, &_iSameRandomProgression, &_ebpLastProgressionPositionRandom,  &_qui8ProgressionIndexRandom, &_iSameInRowRandom, &_iMaxSameInRowRandom);
	} else {
		if (_s63sSettings.GetDozenColumnType() & System63Settings::DozenColumnTypeDozen) {
			PlayCmn::eBetPosition ebpPosition = GetSpinPosition(pSpin, System63Settings::DozenColumnTypeDozen);
			quint8 qui8Max = _s63sSettings.GetDozen3x() ? THREEX_COUNT : 1;
			for (quint8 qui8Index = 0; qui8Index < qui8Max; qui8Index++) {
				PlayCmn::eBetPosition ebpCheckToPosition = _s63sSettings.GetDozen3x() ? static_cast<PlayCmn::eBetPosition>(PlayCmn::BetPositionDozen1 + qui8Index) : _ebpLastPositionDozen[qui8Index];
				PlayCmn::sSpinResult srSpin = AnalyzeSpin(_tbhLastDozenBet[qui8Index], ebpPosition, &_iSameDozenBeforeBet[qui8Index], ebpCheckToPosition, &_ebpLastPositionDozen[qui8Index], &_iSameDozenProgression[qui8Index], &_ebpLastProgressionPositionDozen[qui8Index], &_qui8ProgressionIndexDozen[qui8Index], &_iSameDozenInRow[qui8Index], &_iMaxSameDozenInRow[qui8Index]);
				AddToResult(&srResult, srSpin);
			} // for
		} // if
		if (_s63sSettings.GetDozenColumnType() & System63Settings::DozenColumnTypeColumn) {
			PlayCmn::eBetPosition ebpPosition = GetSpinPosition(pSpin, System63Settings::DozenColumnTypeColumn);
			quint8 qui8Max = _s63sSettings.GetColumn3x() ? THREEX_COUNT : 1;
			for (quint8 qui8Index = 0; qui8Index < qui8Max; qui8Index++) {
				PlayCmn::eBetPosition ebpCheckToPosition = _s63sSettings.GetColumn3x() ? static_cast<PlayCmn::eBetPosition>(PlayCmn::BetPositionColumn1 + qui8Index) : _ebpLastPositionColumn[qui8Index];
				PlayCmn::sSpinResult srSpin = AnalyzeSpin(_tbhLastColumnBet[qui8Index], ebpPosition, &_iSameColumnBeforeBet[qui8Index], ebpCheckToPosition, &_ebpLastPositionColumn[qui8Index], &_iSameColumnProgression[qui8Index], &_ebpLastProgressionPositionColumn[qui8Index], &_qui8ProgressionIndexColumn[qui8Index], &_iSameColumnInRow[qui8Index], &_iMaxSameColumnInRow[qui8Index]);
				AddToResult(&srResult, srSpin);
			} // for
		} // if
	} // if else

	return srResult;
} // AnalyzeSpin

const void System63::CloseSettings(const QWidget *pSettings, const bool &pSave) const
{
	const System63SettingsWidget *s63swSettings = qobject_cast<const System63SettingsWidget *>(pSettings);

	if (pSave) {
		s63swSettings->SaveSettings();
	} // if

	delete s63swSettings;
} // CloseSettings

const void System63::CloseStatistics() const
{
	QVBoxLayout *qvbLayout = qobject_cast<QVBoxLayout *>(_s63swStatistics.parentWidget()->layout());
	QLayoutItem *qliLayoutItem = qvbLayout->takeAt(0);
	QWidget *qwWidget = qliLayoutItem->widget();
	qwWidget->setParent(NULL);
} // CloseStatistics

const PlayCmn::tBetHash System63::CreateBet(const int &pSameBeforeBet, const int &pSameBeforeProgression, const quint8 &pProgressionIndex, const System63Settings::eDozenColumnType &pType, const PlayCmn::eBetPosition &pLastPosition) const
{
	PlayCmn::tBetHash tbhBet;

	if (pSameBeforeBet < _s63sSettings.GetSameDozenColumnBeforeBet()) {
		return tbhBet;
	} // if
	if (pProgressionIndex > 0 && pSameBeforeProgression < _s63sSettings.GetSameDozenColumnProgression()) {
		return tbhBet;
	} // if

	for (int iBet = 0; iBet < 2; iBet++) {
		do {
			PlayCmn::eBetPosition ebpPosition;
			if (pType == System63Settings::DozenColumnTypeDozen) {
				ebpPosition = static_cast<PlayCmn::eBetPosition>((qrand() % (PlayCmn::BetPositionDozen3 - PlayCmn::BetPositionDozen1 + 1)) + PlayCmn::BetPositionDozen1);
			} else {
				ebpPosition = static_cast<PlayCmn::eBetPosition>((qrand() % (PlayCmn::BetPositionColumn3 - PlayCmn::BetPositionColumn1 + 1)) + PlayCmn::BetPositionColumn1);
			} // if else

			if (ebpPosition != pLastPosition && !tbhBet.contains(ebpPosition)) {
				tbhBet.insert(ebpPosition, _qlProgressionSequence.at(pProgressionIndex));
				break;
			} // if
		} while (true);
	} // for

	return tbhBet;
} // CreateBet

const PlayCmn::tBetHash System63::GetBet()
{
	_tbhLastBet.clear();

	if (_s63sSettings.GetBetOn() == System63Settings::BetOnRandom) {
		_edctLastBetRandom = static_cast<System63Settings::eDozenColumnType>(qrand() % (System63Settings::DozenColumnTypeBoth - System63Settings::DozenColumnTypeDozen) + System63Settings::DozenColumnTypeDozen);
		PlayCmn::eBetPosition ebpPosition;
		if (_edctLastBetRandom == System63Settings::DozenColumnTypeDozen) {
			ebpPosition = static_cast<PlayCmn::eBetPosition>((qrand() % (PlayCmn::BetPositionDozen3 - PlayCmn::BetPositionDozen1 + 1)) + PlayCmn::BetPositionDozen1);
		} else {
			ebpPosition = static_cast<PlayCmn::eBetPosition>((qrand() % (PlayCmn::BetPositionColumn3 - PlayCmn::BetPositionColumn1 + 1)) + PlayCmn::BetPositionColumn1);
		} // if else

		_tbhLastBet = CreateBet(_iSameRandomBeforeBet, _iSameRandomProgression, _qui8ProgressionIndexRandom, _edctLastBetRandom, ebpPosition);
	} else {
		if (_s63sSettings.GetDozenColumnType() & System63Settings::DozenColumnTypeDozen) {
			quint8 qui8Max = _s63sSettings.GetDozen3x() ? THREEX_COUNT : 1;
			for (quint8 qui8Index = 0; qui8Index < qui8Max; qui8Index++) {
				PlayCmn::eBetPosition ebpPosition = _s63sSettings.GetDozen3x() ? static_cast<PlayCmn::eBetPosition>(PlayCmn::BetPositionDozen1 + qui8Index) : _ebpLastPositionDozen[qui8Index];
				_tbhLastDozenBet[qui8Index] = CreateBet(_iSameDozenBeforeBet[qui8Index], _iSameDozenProgression[qui8Index], _qui8ProgressionIndexDozen[qui8Index], System63Settings::DozenColumnTypeDozen, ebpPosition);
				AddToLastBet(_tbhLastDozenBet[qui8Index]);
			} // for
		} // if
		if (_s63sSettings.GetDozenColumnType() & System63Settings::DozenColumnTypeColumn) {
			quint8 qui8Max = _s63sSettings.GetColumn3x() ? THREEX_COUNT : 1;
			for (quint8 qui8Index = 0; qui8Index < qui8Max; qui8Index++) {
				PlayCmn::eBetPosition ebpPosition = _s63sSettings.GetColumn3x() ? static_cast<PlayCmn::eBetPosition>(PlayCmn::BetPositionColumn1 + qui8Index) : _ebpLastPositionColumn[qui8Index];
				_tbhLastColumnBet[qui8Index] = CreateBet(_iSameColumnBeforeBet[qui8Index], _iSameColumnProgression[qui8Index], _qui8ProgressionIndexColumn[qui8Index], System63Settings::DozenColumnTypeColumn, ebpPosition);
				AddToLastBet(_tbhLastColumnBet[qui8Index]);
			} // for
		} // if
	} // if else

	return _tbhLastBet;
} // GetBet

const PlayCmn::eBetPosition System63::GetSpinPosition(const quint8 &pSpin, const System63Settings::eDozenColumnType &pType) const
{
	if (pSpin == 0) {
		return PlayCmn::BetPosition0;
	} // if

	if (pType == System63Settings::DozenColumnTypeDozen) {
		if (pSpin < 13) {
			return PlayCmn::BetPositionDozen1;
		} // if

		if (pSpin < 25) {
			return PlayCmn::BetPositionDozen2;
		} // if

		return PlayCmn::BetPositionDozen3;
	} else {
		if (pSpin == 1 || pSpin == 4 || pSpin == 7 || pSpin == 10 || pSpin == 13 || pSpin == 16 || pSpin == 19 || pSpin == 22 || pSpin == 25 || pSpin == 28 || pSpin == 31 || pSpin == 34) {
			return PlayCmn::BetPositionColumn1;
		} // if

		if (pSpin == 2 || pSpin == 5 || pSpin == 8 || pSpin == 11 || pSpin == 14 || pSpin == 17 || pSpin == 20 || pSpin == 23 || pSpin == 26 || pSpin == 29 || pSpin == 32 || pSpin == 35) {
			return PlayCmn::BetPositionColumn2;
		} // if

		return PlayCmn::BetPositionColumn3;
	} // if else
} // GetBetPosition

const QString System63::GetName() const
{
	return "System 63";
} // GetName

QWidget *System63::GetSettings()
{
	return new System63SettingsWidget(&_s63sSettings);
} // GetSettings

const void System63::OpenStatistics(QVBoxLayout *pLayout)
{
	pLayout->insertWidget(0, &_s63swStatistics);
} // OpenStatistics

const void System63::Reset(const qfResetContents &pResetContents)
{
	if (pResetContents & ResetContentCore) {
		_ebpLastPositionRandom = PlayCmn::BetPositionNone;
		_ebpLastProgressionPositionRandom = PlayCmn::BetPositionNone;
		_iMaxSameInRowRandom = 0;
		_iSameRandomBeforeBet = 0;
		_iSameRandomProgression = 0;
		_iSameInRowRandom = 0;

		_qlProgressionSequence.clear();
		QStringList qslProgressionSequence = _s63sSettings.GetProgressionManualSequence().split(PROGRESSION_SEQUENCE_SEPARATOR);
		foreach (QString qsProgression, qslProgressionSequence) {
			_qlProgressionSequence.append(qsProgression.toUInt());
		} // foreach
		_qui8ProgressionIndexRandom = 0;

		for (quint8 qui8Index = 0; qui8Index < THREEX_COUNT; qui8Index++) {
			_ebpLastPositionColumn[qui8Index] = PlayCmn::BetPositionNone;
			_ebpLastPositionDozen[qui8Index] = PlayCmn::BetPositionNone;
			_ebpLastProgressionPositionColumn[qui8Index] = PlayCmn::BetPositionNone;
			_ebpLastProgressionPositionDozen[qui8Index] = PlayCmn::BetPositionNone;
			_iMaxSameColumnInRow[qui8Index] = 0;
			_iMaxSameDozenInRow[qui8Index] = 0;
			_iSameColumnBeforeBet[qui8Index] = 0;
			_iSameDozenBeforeBet[qui8Index] = 0;
			_iSameColumnProgression[qui8Index] = 0;
			_iSameDozenProgression[qui8Index] = 0;
			_qui8ProgressionIndexColumn[qui8Index] = 0;
			_qui8ProgressionIndexDozen[qui8Index] = 0;
			_iSameColumnInRow[THREEX_COUNT] = 0;
			_iSameDozenInRow[THREEX_COUNT] = 0;
		} // for
	} // if

	if (pResetContents & ResetContentStatistics) {
		_iMaxSameInRowRandom = 0;
		_iSameInRowRandom = 0;

		for (quint8 qui8Index = 0; qui8Index < THREEX_COUNT; qui8Index++) {
			_iMaxSameColumnInRow[qui8Index] = 0;
			_iMaxSameDozenInRow[qui8Index] = 0;
			_iSameColumnInRow[THREEX_COUNT] = 0;
			_iSameDozenInRow[THREEX_COUNT] = 0;
		} // for

		_s63swStatistics.Reset();
	} // if
} // Reset

Q_EXPORT_PLUGIN2(system63, System63)