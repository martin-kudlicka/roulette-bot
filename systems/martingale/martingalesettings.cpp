#include "martingalesettings.h"

const QString BET_STYLE = "BetStyle";
const QString PROGRESSION_AUTO_VALUE = "ProgressionAutoValue";
const QString PROGRESSION_COLOR_NOT_CHANGED = "ProgressionColorNotChanged";
const QString PROGRESSION_MANUAL_SEQUENCE = "ProgressionManualSequence";
const QString PROGRESSION_TYPE = "ProgressionType";
const QString SAME_COLOR_BEFORE_BET = "SameColorBeforeBet";
const QString SAME_COLOR_PROGRESSION = "SameColorProgression";

const MartingaleSettings::eBetStyle MartingaleSettings::GetBetStyle() const
{
	return static_cast<eBetStyle>(_ssSettings.value(BET_STYLE, BetStyleKeepColor).toInt());
} // GetBetStyle

const int MartingaleSettings::GetProgressionAutoValue() const
{
	return _ssSettings.value(PROGRESSION_AUTO_VALUE, 2).toInt();
} // GetProgressionAutoValue

const bool MartingaleSettings::GetProgressionColorNotChanged() const
{
	return _ssSettings.value(PROGRESSION_COLOR_NOT_CHANGED, false).toBool();
} // GetProgressionColorNotChanged

const QString MartingaleSettings::GetProgressionManualSequence() const
{
	return _ssSettings.value(PROGRESSION_MANUAL_SEQUENCE, "1;3").toString();
} // GetProgressionManualSequence

const MartingaleSettings::eProgressionType MartingaleSettings::GetProgressionType() const
{
	return static_cast<eProgressionType>(_ssSettings.value(PROGRESSION_TYPE, ProgressionTypeAuto).toInt());
} // GetProgressionType

const int MartingaleSettings::GetSameColorBeforeBet() const
{
	return _ssSettings.value(SAME_COLOR_BEFORE_BET, 2).toInt();
} // GetSameColorBeforeBet

const int MartingaleSettings::GetSameColorProgression() const
{
	return _ssSettings.value(SAME_COLOR_PROGRESSION, 2).toInt();
} // GetSameColorProgression

const void MartingaleSettings::SetBetStyle(const eBetStyle &pBetStyle)
{
	_ssSettings.setValue(BET_STYLE, pBetStyle);
} // SetBetStyle

const void MartingaleSettings::SetProgressionAutoValue(const int &pValue)
{
	_ssSettings.setValue(PROGRESSION_AUTO_VALUE, pValue);
} // SetProgressionAutoValue

const void MartingaleSettings::SetProgressionColorNotChanged(const bool &pValue)
{
	_ssSettings.setValue(PROGRESSION_COLOR_NOT_CHANGED, pValue);
} // SetProgressionColorNotChanged

const void MartingaleSettings::SetProgressionManualSequence(const QString &pSequence)
{
	_ssSettings.setValue(PROGRESSION_MANUAL_SEQUENCE, pSequence);
} // SetProgressionManualSequence

const void MartingaleSettings::SetProgressionType(const eProgressionType &pType)
{
	_ssSettings.setValue(PROGRESSION_TYPE, pType);
} // SetProgressionType

const void MartingaleSettings::SetSameColorBeforeBet(const int &pCount)
{
	_ssSettings.setValue(SAME_COLOR_BEFORE_BET, pCount);
} // SetSameColorBeforeBet

const void MartingaleSettings::SetSameColorProgression(const int &pCount)
{
	_ssSettings.setValue(SAME_COLOR_PROGRESSION, pCount);
} // SetSameColorProgression

MartingaleSettings::MartingaleSettings()
{
	_ssSettings.beginGroup("Martingale");
} // MartingaleSettings