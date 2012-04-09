#include "unibetsettings.h"

const QString BET_VALUE = "BetValue";

const UnibetSettings::eBetValue UnibetSettings::GetBetValue() const
{
	return static_cast<eBetValue>(_csSettings.value(BET_VALUE, BetValue1).toInt());
} // GetBetValue

const void UnibetSettings::SetBetValue(const eBetValue &pBetValue)
{
	_csSettings.setValue(BET_VALUE, pBetValue);
} // SetBetValue

UnibetSettings::UnibetSettings()
{
	_csSettings.beginGroup("Unibet");
} // UnibetSettings