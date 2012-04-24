#include "settings.h"

#include "../common/settingscmn.h"

const QString GROUP_GENERAL = "general";
const QString MAX_LOSS_TO_PLAY = "maxlosstoplay";
const QString MAX_WIN_TO_PLAY = "maxwintoplay";
const QString STOP_ON_LOSS = "stoponloss";
const QString TOKENS_PER_BET = "TokensPerBet";

const quint8 Settings::GetMaxLossToPlay()
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	quint8 qui8MaxLoss = _qsSettings.value(MAX_LOSS_TO_PLAY, 1).toUInt();
	_qsSettings.endGroup();

	return qui8MaxLoss;
} // GetMaxLossToPlay

const quint8 Settings::GetMaxWinToPlay()
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	quint8 qui8MaxWin = _qsSettings.value(MAX_WIN_TO_PLAY, 10).toUInt();
	_qsSettings.endGroup();

	return qui8MaxWin;
} // GetMaxWinToPlay

const bool Settings::GetStopOnLoss()
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	bool bStop = _qsSettings.value(STOP_ON_LOSS, false).toBool();
	_qsSettings.endGroup();

	return bStop;
} // GetStopOnLoss

const quint8 Settings::GetTokensPerBet()
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	quint8 qui8Tokens = _qsSettings.value(TOKENS_PER_BET, 1).toUInt();
	_qsSettings.endGroup();

	return qui8Tokens;
} // GetTokensPerBet

const void Settings::SetMaxLossToPlay(const quint8 &pValue)
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	_qsSettings.setValue(MAX_LOSS_TO_PLAY, pValue);
	_qsSettings.endGroup();
} // SetMaxLossToPlay

const void Settings::SetMaxWinToPlay(const quint8 &pValue)
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	_qsSettings.setValue(MAX_WIN_TO_PLAY, pValue);
	_qsSettings.endGroup();
} // SetMaxWinToPlay

const void Settings::SetStopOnLoss(const bool &pStop)
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	_qsSettings.setValue(STOP_ON_LOSS, pStop);
	_qsSettings.endGroup();
} // SetStopOnLoss

Settings::Settings() : _qsSettings(ORGANIZATION, APPLICATION)
{
} // Settings

const void Settings::SetTokensPerBet(const quint8 &pTokens)
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	_qsSettings.setValue(TOKENS_PER_BET, pTokens);
	_qsSettings.endGroup();
} // SetTokensPerBet