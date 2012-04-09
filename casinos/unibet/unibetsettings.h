#ifndef UNIBETSETTINGS_H
#define UNIBETSETTINGS_H

#include "../common/casinosettings.h"

class UnibetSettings
{
	public:
		enum eBetValue {
			BetValue1,
			BetValue2,
			BetValue3,
			BetValue4
		}; // eBetValue

		UnibetSettings();

		const eBetValue GetBetValue() const;
		const void SetBetValue(const eBetValue &pBetValue);

	private:
		CasinoSettings _csSettings;
}; // Settings

#endif // UNIBETSETTINGS_H