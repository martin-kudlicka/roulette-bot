#include "system63.h"

#include "system63settingswidget.h"

const void System63::AddToLastBet(const PlayCmn::tBetHash &pBet)
{
	for (PlayCmn::tBetHash::const_iterator ciBet = pBet.constBegin(); ciBet != pBet.constEnd(); ciBet++) {
		quint8 qui8Value;
		if (_tbhLastBet.contains(ciBet.key())) {
			qui8Value = _tbhLastBet.value(ciBet.key());
		} else {
			qui8Value = 0;
		} // if else

		qui8Value += ciBet.value();
		_tbhLastBet.insert(ciBet.key(), qui8Value);
	} // for
} // AddToLastBet

const void System63::AddToResult(PlayCmn::sSpinResult *pResult, const PlayCmn::sSpinResult &pAdd) const
{
	pResult->esrtType |= pAdd.esrtType;
	pResult->qui8BetProfit += pAdd.qui8BetProfit;
} // AddToResult

const PlayCmn::sSpinResult System63::AnalyzeSpin(const PlayCmn::tBetHash &pBet, const PlayCmn::qfBetPositions pPosition, quint8 *pSameBeforeBet, const PlayCmn::qfBetPositions &pCheckToLastPosition, PlayCmn::qfBetPositions *pLastPosition, quint8 *pSameProgression, PlayCmn::qfBetPositions *pLastProgressionPosition, quint8 *pProgressionIndex, quint8 *pSameInRow, quint8 *pMaxSameInRow)
{
	PlayCmn::sSpinResult srResult;

	do {
		if (pBet.isEmpty()) {
			// no bet made
			srResult.esrtType = PlayCmn::SpinResultTypeNoBet;
			srResult.qui8BetProfit = 0;

			if (*pSameBeforeBet < _s63sSettings.GetSameDozenColumnBeforeBet()) {
				if (pCheckToLastPosition & pPosition || pCheckToLastPosition == PlayCmn::BetPositionNone) {
					(*pSameBeforeBet)++;
				} else {
					if (!(pCheckToLastPosition & pPosition) && !(pCheckToLastPosition & *pLastPosition)) {
						*pSameBeforeBet = 0;
					} else {
						*pSameBeforeBet = 1;
					} // if else
				} // if else

				break;
			} // if

			if (*pSameProgression < _s63sSettings.GetSameDozenColumnProgression()) {
				if (_s63sSettings.GetProgressionDozenColumnNotChanged()) {
					if (pCheckToLastPosition & pPosition) {
						(*pSameProgression)++;
					} else {
						srResult.esrtType |= PlayCmn::SpinResultTypeLost;
						if (!(pCheckToLastPosition & pPosition)) {
							*pSameBeforeBet = 0;
						} else {
							*pSameBeforeBet = 1;
						} // if else
						*pSameProgression = 0;
						*pProgressionIndex = 0;
					} // if else
				} else {
					if (*pSameProgression == 0 || !(*pLastProgressionPosition & pPosition)) {
						*pLastProgressionPosition = pPosition;
						if (!(pCheckToLastPosition & pPosition) && !(pCheckToLastPosition & *pLastPosition)) {
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
			if (BetContains(pBet, pPosition)) {
				// won
				srResult.esrtType = PlayCmn::SpinResultTypeWon;
				srResult.qui8BetProfit = BetValue(pBet, pPosition) * 3;

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
				srResult.qui8BetProfit = 0;

				break;
			} // if else
		} // if else
	} while (false);

	(*pSameInRow)++;
	if (!(*pLastPosition & pPosition)) {
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
	srResult.qui8BetProfit = 0;

	PlayCmn::qfBetPositions qfbpPosition = GetSpinPosition(pSpin);

	if (_s63sSettings.GetBetOn() == System63Settings::BetOnRandom) {
		srResult = AnalyzeSpin(_tbhLastBet, qfbpPosition, &_qui8SameRandomBeforeBet, _qfbpLastPositionRandom, &_qfbpLastPositionRandom, &_qui8SameRandomProgression, &_qfbpLastProgressionPositionRandom,  &_qui8ProgressionIndexRandom, &_qui8SameInRowRandom, &_qui8MaxSameInRowRandom);
	} else {
		if (_s63sSettings.GetDozenColumnType() & System63Settings::DozenColumnTypeDozen) {
			qfbpPosition &= PlayCmn::BetPositionNumbers | PlayCmn::BetPositionDozen1 | PlayCmn::BetPositionDozen2 | PlayCmn::BetPositionDozen3;
			quint8 qui8Max = _s63sSettings.GetDozen3x() ? THREEX_COUNT : 1;
			for (quint8 qui8Index = 0; qui8Index < qui8Max; qui8Index++) {
				PlayCmn::qfBetPositions qfbpCheckToPosition = _s63sSettings.GetDozen3x() ? static_cast<PlayCmn::eBetPosition>(PlayCmn::BetPositionDozen1 + qui8Index) : _qfbpLastPositionDozen[qui8Index];
				PlayCmn::sSpinResult srSpin = AnalyzeSpin(_tbhLastDozenBet[qui8Index], qfbpPosition, &_qui8SameDozenBeforeBet[qui8Index], qfbpCheckToPosition, &_qfbpLastPositionDozen[qui8Index], &_qui8SameDozenProgression[qui8Index], &_qfbpLastProgressionPositionDozen[qui8Index], &_qui8ProgressionIndexDozen[qui8Index], &_qui8SameDozenInRow[qui8Index], &_qui8MaxSameDozenInRow[qui8Index]);
				AddToResult(&srResult, srSpin);
			} // for
		} // if
		if (_s63sSettings.GetDozenColumnType() & System63Settings::DozenColumnTypeColumn) {
			qfbpPosition &= PlayCmn::BetPositionNumbers | PlayCmn::BetPositionColumn1 | PlayCmn::BetPositionColumn2 | PlayCmn::BetPositionColumn3;
			quint8 qui8Max = _s63sSettings.GetColumn3x() ? THREEX_COUNT : 1;
			for (quint8 qui8Index = 0; qui8Index < qui8Max; qui8Index++) {
				PlayCmn::qfBetPositions qfbpCheckToPosition = _s63sSettings.GetColumn3x() ? static_cast<PlayCmn::eBetPosition>(PlayCmn::BetPositionColumn1 + qui8Index) : _qfbpLastPositionColumn[qui8Index];
				PlayCmn::sSpinResult srSpin = AnalyzeSpin(_tbhLastColumnBet[qui8Index], qfbpPosition, &_qui8SameColumnBeforeBet[qui8Index], qfbpCheckToPosition, &_qfbpLastPositionColumn[qui8Index], &_qui8SameColumnProgression[qui8Index], &_qfbpLastProgressionPositionColumn[qui8Index], &_qui8ProgressionIndexColumn[qui8Index], &_qui8SameColumnInRow[qui8Index], &_qui8MaxSameColumnInRow[qui8Index]);
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

const PlayCmn::tBetHash System63::CreateBet(const quint8 &pSameBeforeBet, const quint8 &pSameBeforeProgression, const quint8 &pProgressionIndex, const System63Settings::eDozenColumnType &pType, const PlayCmn::qfBetPositions &pLastPosition) const
{
	PlayCmn::tBetHash tbhBet;

	if (pSameBeforeBet < _s63sSettings.GetSameDozenColumnBeforeBet()) {
		return tbhBet;
	} // if
	if (pProgressionIndex > 0 && pSameBeforeProgression < _s63sSettings.GetSameDozenColumnProgression()) {
		return tbhBet;
	} // if

	for (quint8 qui8Bet = 0; qui8Bet < 2; qui8Bet++) {
		do {
			PlayCmn::eBetPosition ebpPosition;
			int iPosition = qrand() % 3;
			switch (iPosition) {
				case 0:
					if (pType == System63Settings::DozenColumnTypeDozen) {
						ebpPosition = PlayCmn::BetPositionDozen1;
					} else {
						ebpPosition = PlayCmn::BetPositionColumn1;
					}
					break;
				case 1:
					if (pType == System63Settings::DozenColumnTypeDozen) {
						ebpPosition = PlayCmn::BetPositionDozen2;
					} else {
						ebpPosition = PlayCmn::BetPositionColumn2;
					}
					break;
				case 2:
					if (pType == System63Settings::DozenColumnTypeDozen) {
						ebpPosition = PlayCmn::BetPositionDozen3;
					} else {
						ebpPosition = PlayCmn::BetPositionColumn3;
					}
			} // switch

			if (!(ebpPosition & pLastPosition) && !tbhBet.contains(ebpPosition)) {
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

		_tbhLastBet = CreateBet(_qui8SameRandomBeforeBet, _qui8SameRandomProgression, _qui8ProgressionIndexRandom, _edctLastBetRandom, ebpPosition);
	} else {
		if (_s63sSettings.GetDozenColumnType() & System63Settings::DozenColumnTypeDozen) {
			quint8 qui8Max = _s63sSettings.GetDozen3x() ? THREEX_COUNT : 1;
			for (quint8 qui8Index = 0; qui8Index < qui8Max; qui8Index++) {
				PlayCmn::qfBetPositions qfbpPosition = _s63sSettings.GetDozen3x() ? static_cast<PlayCmn::qfBetPositions>(PlayCmn::BetPositionDozen1 + qui8Index) : _qfbpLastPositionDozen[qui8Index];
				_tbhLastDozenBet[qui8Index] = CreateBet(_qui8SameDozenBeforeBet[qui8Index], _qui8SameDozenProgression[qui8Index], _qui8ProgressionIndexDozen[qui8Index], System63Settings::DozenColumnTypeDozen, qfbpPosition);
				AddToLastBet(_tbhLastDozenBet[qui8Index]);
			} // for
		} // if
		if (_s63sSettings.GetDozenColumnType() & System63Settings::DozenColumnTypeColumn) {
			quint8 qui8Max = _s63sSettings.GetColumn3x() ? THREEX_COUNT : 1;
			for (quint8 qui8Index = 0; qui8Index < qui8Max; qui8Index++) {
				PlayCmn::qfBetPositions qfbpPosition = _s63sSettings.GetColumn3x() ? static_cast<PlayCmn::qfBetPositions>(PlayCmn::BetPositionColumn1 + qui8Index) : _qfbpLastPositionColumn[qui8Index];
				_tbhLastColumnBet[qui8Index] = CreateBet(_qui8SameColumnBeforeBet[qui8Index], _qui8SameColumnProgression[qui8Index], _qui8ProgressionIndexColumn[qui8Index], System63Settings::DozenColumnTypeColumn, qfbpPosition);
				AddToLastBet(_tbhLastColumnBet[qui8Index]);
			} // for
		} // if
	} // if else

	return _tbhLastBet;
} // GetBet

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
		_qfbpLastPositionRandom = PlayCmn::BetPositionNone;
		_qfbpLastProgressionPositionRandom = PlayCmn::BetPositionNone;
		_qui8MaxSameInRowRandom = 0;
		_qui8SameRandomBeforeBet = 0;
		_qui8SameRandomProgression = 0;
		_qui8SameInRowRandom = 0;

		_qlProgressionSequence.clear();
		QStringList qslProgressionSequence = _s63sSettings.GetProgressionManualSequence().split(PROGRESSION_SEQUENCE_SEPARATOR);
		foreach (QString qsProgression, qslProgressionSequence) {
			_qlProgressionSequence.append(qsProgression.toUInt());
		} // foreach
		_qui8ProgressionIndexRandom = 0;

		for (quint8 qui8Index = 0; qui8Index < THREEX_COUNT; qui8Index++) {
			_qfbpLastPositionColumn[qui8Index] = PlayCmn::BetPositionNone;
			_qfbpLastPositionDozen[qui8Index] = PlayCmn::BetPositionNone;
			_qfbpLastProgressionPositionColumn[qui8Index] = PlayCmn::BetPositionNone;
			_qfbpLastProgressionPositionDozen[qui8Index] = PlayCmn::BetPositionNone;
			_qui8MaxSameColumnInRow[qui8Index] = 0;
			_qui8MaxSameDozenInRow[qui8Index] = 0;
			_qui8SameColumnBeforeBet[qui8Index] = 0;
			_qui8SameDozenBeforeBet[qui8Index] = 0;
			_qui8SameColumnProgression[qui8Index] = 0;
			_qui8SameDozenProgression[qui8Index] = 0;
			_qui8ProgressionIndexColumn[qui8Index] = 0;
			_qui8ProgressionIndexDozen[qui8Index] = 0;
			_qui8SameColumnInRow[THREEX_COUNT] = 0;
			_qui8SameDozenInRow[THREEX_COUNT] = 0;
		} // for
	} // if

	if (pResetContents & ResetContentStatistics) {
		_qui8MaxSameInRowRandom = 0;
		_qui8SameInRowRandom = 0;

		for (quint8 qui8Index = 0; qui8Index < THREEX_COUNT; qui8Index++) {
			_qui8MaxSameColumnInRow[qui8Index] = 0;
			_qui8MaxSameDozenInRow[qui8Index] = 0;
			_qui8SameColumnInRow[THREEX_COUNT] = 0;
			_qui8SameDozenInRow[THREEX_COUNT] = 0;
		} // for

		_s63swStatistics.Reset();
	} // if
} // Reset

Q_EXPORT_PLUGIN2(system63, System63)