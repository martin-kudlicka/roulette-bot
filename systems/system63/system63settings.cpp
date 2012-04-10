#include "system63settings.h"

const QString PROGRESSION_AUTO_VALUE = "ProgressionAutoValue";
const QString PROGRESSION_DOZEN_COLUMN_NOT_CHANGED = "ProgressionDozenColumnNotChanged";
const QString PROGRESSION_MANUAL_SEQUENCE = "ProgressionManualSequence";
const QString PROGRESSION_TYPE = "ProgressionType";
const QString SAME_DOZEN_COLUMN_BEFORE_BET = "SameDozenColumnBeforeBet";
const QString SAME_DOZEN_COLUMN_PROGRESSION = "SameDozenColumnProgression";

const int System63Settings::GetProgressionAutoValue() const
{
	return _ssSettings.value(PROGRESSION_AUTO_VALUE, 2).toInt();
} // GetProgressionAutoValue

const bool System63Settings::GetProgressionDozenColumnNotChanged() const
{
	return _ssSettings.value(PROGRESSION_DOZEN_COLUMN_NOT_CHANGED, true).toBool();
} // GetProgressionDozenColumnNotChanged

const QString System63Settings::GetProgressionManualSequence() const
{
	return _ssSettings.value(PROGRESSION_MANUAL_SEQUENCE, "1;3").toString();
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
	return _ssSettings.value(SAME_DOZEN_COLUMN_PROGRESSION, 1).toInt();
} // GetSameDozenColumnProgression

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