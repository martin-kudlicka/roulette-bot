#include "settings.h"

#include "../common/settingscmn.h"

const QString GROUP_GENERAL = "general";
const QString MAX_LOSS_TO_PLAY = "maxlosstoplay";
const QString TOKENS_PER_BET = "TokensPerBet";

const int Settings::GetMaxLossToPlay()
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	int iTokens = _qsSettings.value(MAX_LOSS_TO_PLAY, 0).toInt();
	_qsSettings.endGroup();

	return iTokens;
} // GetMaxLossToPlay

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

Settings::Settings() : _qsSettings(ORGANIZATION, APPLICATION)
{
} // Settings

const void Settings::SetTokensPerBet(const int &pTokens)
{
	_qsSettings.beginGroup(GROUP_GENERAL);
	_qsSettings.setValue(TOKENS_PER_BET, pTokens);
	_qsSettings.endGroup();
} // SetTokensPerBet