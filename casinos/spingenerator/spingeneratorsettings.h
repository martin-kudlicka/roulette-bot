#ifndef SPINGENERATORSETTINGS_H
#define SPINGENERATORSETTINGS_H

#include "../common/casinosettings.h"

class SpinGeneratorSettings
{
	public:
		SpinGeneratorSettings();

		const quint8 GetStartingCash() const;
		const void SetStartingCash(const quint8 &pCash);

	private:
		CasinoSettings _csSettings;
}; // Settings

#endif // SPINGENERATORSETTINGS_H