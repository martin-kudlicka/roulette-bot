#include "settings.h"

#include "../common/settingscmn.h"

const QString GROUP_GENERAL = "general";
const QString MAX_LOSS_TO_PLAY = "maxlosstoplay";
const QString STOP_ON_LOSS = "stoponloss";
const QString TOKENS_PER_BET = "TokensPerBet";

const int Settings::GetMaxLossToPlay()
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	int iTokens = _qsSettings.value(MAX_LOSS_TO_PLAY, 0).toInt();
	_qsSettings.endGroup();

	return iTokens;
} // GetMaxLossToPlay

const bool Settings::GetStopOnLoss()
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	bool bStop = _qsSettings.value(STOP_ON_LOSS, false).toBool();
	_qsSettings.endGroup();

	return bStop;
} // GetStopOnLoss

const int Settings::GetTokensPerBet()
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	int iTokens = _qsSettings.value(TOKENS_PER_BET, 1).toInt();
	_qsSettings.endGroup();

	return iTokens;
} // GetTokensPerBet

const void Settings::SetMaxLossToPlay(const int &pValue)
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	_qsSettings.setValue(MAX_LOSS_TO_PLAY, pValue);
	_qsSettings.endGroup();
} // SetMaxLossToPlay

const void Settings::SetStopOnLoss(const bool &pStop)
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	_qsSettings.setValue(STOP_ON_LOSS, pStop);
	_qsSettings.endGroup();
} // SetStopOnLoss

Settings::Settings() : _qsSettings(ORGANIZATION, APPLICATION)
{
} // Settings

const void Settings::SetTokensPerBet(const int &pTokens)
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	_qsSettings.setValue(TOKENS_PER_BET, pTokens);
	_qsSettings.endGroup();
} // SetTokensPerBet