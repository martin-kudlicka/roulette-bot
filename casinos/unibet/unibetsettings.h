#ifndef UNIBETSETTINGS_H
#define UNIBETSETTINGS_H

#include "../common/casinosettings.h"

class UnibetSettings
{
	Q_ENUMS(eTokenValue)

	public:
		enum eTokenValue {
			TokenValue1,
			TokenValue2,
			TokenValue3,
			TokenValue4
		}; // eTokenValue

		UnibetSettings();

		const eTokenValue GetTokenValue() const;
		const void SetTokenValue(const eTokenValue &pTokenValue);

	private:
		CasinoSettings _csSettings;
}; // Settings

#endif // UNIBETSETTINGS_H