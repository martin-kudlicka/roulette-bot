#ifndef SPINGENERATORSETTINGS_H
#define SPINGENERATORSETTINGS_H

#include "../common/casinosettings.h"

class SpinGeneratorSettings
{
	public:
		SpinGeneratorSettings();

		const int GetStartingCash() const;
		const void SetStartingCash(const int &pCash);

	private:
		CasinoSettings _csSettings;
}; // Settings

#endif // SPINGENERATORSETTINGS_H