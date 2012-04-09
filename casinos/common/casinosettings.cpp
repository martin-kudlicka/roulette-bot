#include "casinosettings.h"

#include "../../common/settingscmn.h"

CasinoSettings::CasinoSettings() : QSettings(ORGANIZATION, APPLICATION)
{
	beginGroup("casinos");
} // CasinoSettings