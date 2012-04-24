#include "spingeneratorsettings.h"

const QString STARTING_CASH = "StartingCash";

const quint8 SpinGeneratorSettings::GetStartingCash() const
{
	return _csSettings.value(STARTING_CASH, 10).toUInt();
} // GetStartingCash

const void SpinGeneratorSettings::SetStartingCash(const quint8 &pCash)
{
	_csSettings.setValue(STARTING_CASH, pCash);
} // SetStartingCash

SpinGeneratorSettings::SpinGeneratorSettings()
{
	_csSettings.beginGroup("spin generator");
} // SpinGeneratorSettings