#include "spingeneratorsettings.h"

const QString STARTING_CASH = "StartingCash";

const int SpinGeneratorSettings::GetStartingCash() const
{
	return _csSettings.value(STARTING_CASH, 10).toInt();
} // GetStartingCash

const void SpinGeneratorSettings::SetStartingCash(const int &pCash)
{
	_csSettings.setValue(STARTING_CASH, pCash);
} // SetStartingCash

SpinGeneratorSettings::SpinGeneratorSettings()
{
	_csSettings.beginGroup("spin generator");
} // SpinGeneratorSettings