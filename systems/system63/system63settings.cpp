#include "system63settings.h"

const QString BET_ON = "BetOn";
const QString COLUMN_3X = "Column3x";
const QString DOZEN_3X = "Dozen3x";
const QString DOZEN_COLUMN_TYPE = "DozenColumnType";
const QString PROGRESSION_AUTO_VALUE = "ProgressionAutoValue";
const QString PROGRESSION_DOZEN_COLUMN_NOT_CHANGED = "ProgressionDozenColumnNotChanged";
const QString PROGRESSION_MANUAL_SEQUENCE = "ProgressionManualSequence";
const QString PROGRESSION_TYPE = "ProgressionType";
const QString SAME_DOZEN_COLUMN_BEFORE_BET = "SameDozenColumnBeforeBet";
const QString SAME_DOZEN_COLUMN_PROGRESSION = "SameDozenColumnProgression";

const System63Settings::eBetOn System63Settings::GetBetOn() const
{
	return static_cast<eBetOn>(_ssSettings.value(BET_ON, BetOnDozenColumn).toInt());
} // GetBetOn

const bool System63Settings::GetColumn3x() const
{
	return _ssSettings.value(COLUMN_3X, false).toBool();
} // GetColumn3x

const bool System63Settings::GetDozen3x() const
{
	return _ssSettings.value(DOZEN_3X, false).toBool();
} // GetDozen3x

const System63Settings::eDozenColumnType System63Settings::GetDozenColumnType() const
{
	return static_cast<eDozenColumnType>(_ssSettings.value(DOZEN_COLUMN_TYPE, DozenColumnTypeColumn).toInt());
} // GetDozenColumnType

const int System63Settings::GetProgressionAutoValue() const
{
	return _ssSettings.value(PROGRESSION_AUTO_VALUE, 4).toInt();
} // GetProgressionAutoValue

const bool System63Settings::GetProgressionDozenColumnNotChanged() const
{
	return _ssSettings.value(PROGRESSION_DOZEN_COLUMN_NOT_CHANGED, false).toBool();
} // GetProgressionDozenColumnNotChanged

const QString System63Settings::GetProgressionManualSequence() const
{
	return _ssSettings.value(PROGRESSION_MANUAL_SEQUENCE, "1;3;9;27").toString();
} // GetProgressionManualSequence

const System63Settings::eProgressionType System63Settings::GetProgressionType() const
{
	return static_cast<eProgressionType>(_ssSettings.value(PROGRESSION_TYPE, ProgressionTypeAuto).toInt());
} // GetProgressionType

const int System63Settings::GetSameDozenColumnBeforeBet() const
{
	return _ssSettings.value(SAME_DOZEN_COLUMN_BEFORE_BET, 2).toInt();
} // GetSameDozenColumnBeforeBet

const int System63Settings::GetSameDozenColumnProgression() const
{
	return _ssSettings.value(SAME_DOZEN_COLUMN_PROGRESSION, 2).toInt();
} // GetSameDozenColumnProgression

const void System63Settings::SetBetOn(const eBetOn &pBetOn)
{
	_ssSettings.setValue(BET_ON, pBetOn);
} // SetBetOn

const void System63Settings::SetColumn3x(const bool &pEnabled)
{
	_ssSettings.setValue(COLUMN_3X, pEnabled);
} // SetColumn3x

const void System63Settings::SetDozen3x(const bool &pEnabled)
{
	_ssSettings.setValue(DOZEN_3X, pEnabled);
} // SetDozen3x

const void System63Settings::SetDozenColumnType(const eDozenColumnType &pType)
{
	_ssSettings.setValue(DOZEN_COLUMN_TYPE, pType);
} // SetDozenColumnType

const void System63Settings::SetProgressionAutoValue(const int &pValue)
{
	_ssSettings.setValue(PROGRESSION_AUTO_VALUE, pValue);
} // SetProgressionAutoValue

const void System63Settings::SetProgressionDozenColumnNotChanged(const bool &pValue)
{
	_ssSettings.setValue(PROGRESSION_DOZEN_COLUMN_NOT_CHANGED, pValue);
} // SetProgressionDozenColumnNotChanged

const void System63Settings::SetProgressionManualSequence(const QString &pSequence)
{
	_ssSettings.setValue(PROGRESSION_MANUAL_SEQUENCE, pSequence);
} // SetProgressionManualSequence

const void System63Settings::SetProgressionType(const eProgressionType &pType)
{
	_ssSettings.setValue(PROGRESSION_TYPE, pType);
} // SetProgressionType

const void System63Settings::SetSameDozenColumnBeforeBet(const int &pCount)
{
	_ssSettings.setValue(SAME_DOZEN_COLUMN_BEFORE_BET, pCount);
} // SetSameDozenColumnBeforeBet

const void System63Settings::SetSameDozenColumnProgression(const int &pCount)
{
	_ssSettings.setValue(SAME_DOZEN_COLUMN_PROGRESSION, pCount);
} // SetSameDozenColumnProgression

System63Settings::System63Settings()
{
	_ssSettings.beginGroup("System 63");
} // System63Settings