#include "unibetsettings.h"

const QString TOKEN_VALUE = "TokenValue";

const UnibetSettings::eTokenValue UnibetSettings::GetTokenValue() const
{
	return static_cast<eTokenValue>(_csSettings.value(TOKEN_VALUE, TokenValue1).toInt());
} // GetTokenValue

const void UnibetSettings::SetTokenValue(const eTokenValue &pTokenValue)
{
	_csSettings.setValue(TOKEN_VALUE, pTokenValue);
} // SetTokenValue

UnibetSettings::UnibetSettings()
{
	_csSettings.beginGroup("Unibet");
} // UnibetSettings