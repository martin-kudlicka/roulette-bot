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

const quint8 MartingaleSettings::GetProgressionAutoValue() const
{
	return _ssSettings.value(PROGRESSION_AUTO_VALUE, 6).toUInt();
} // GetProgressionAutoValue

const bool MartingaleSettings::GetProgressionColorNotChanged() const
{
	return _ssSettings.value(PROGRESSION_COLOR_NOT_CHANGED, false).toBool();
} // GetProgressionColorNotChanged

const QString MartingaleSettings::GetProgressionManualSequence() const
{
	return _ssSettings.value(PROGRESSION_MANUAL_SEQUENCE, "1;2;4;8;16;32").toString();
} // GetProgressionManualSequence

const MartingaleSettings::eProgressionType MartingaleSettings::GetProgressionType() const
{
	return static_cast<eProgressionType>(_ssSettings.value(PROGRESSION_TYPE, ProgressionTypeAuto).toInt());
} // GetProgressionType

const quint8 MartingaleSettings::GetSameColorBeforeBet() const
{
	return _ssSettings.value(SAME_COLOR_BEFORE_BET, 3).toUInt();
} // GetSameColorBeforeBet

const quint8 MartingaleSettings::GetSameColorProgression() const
{
	return _ssSettings.value(SAME_COLOR_PROGRESSION, 0).toUInt();
} // GetSameColorProgression

const void MartingaleSettings::SetBetStyle(const eBetStyle &pBetStyle)
{
	_ssSettings.setValue(BET_STYLE, pBetStyle);
} // SetBetStyle

const void MartingaleSettings::SetProgressionAutoValue(const quint8 &pValue)
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

const void MartingaleSettings::SetSameColorBeforeBet(const quint8 &pCount)
{
	_ssSettings.setValue(SAME_COLOR_BEFORE_BET, pCount);
} // SetSameColorBeforeBet

const void MartingaleSettings::SetSameColorProgression(const quint8 &pCount)
{
	_ssSettings.setValue(SAME_COLOR_PROGRESSION, pCount);
} // SetSameColorProgression

MartingaleSettings::MartingaleSettings()
{
	_ssSettings.beginGroup("Martingale");
} // MartingaleSettings