#include "systemsettings.h"

#include "../../common/settingscmn.h"

SystemSettings::SystemSettings() : QSettings(ORGANIZATION, APPLICATION)
{
	beginGroup("systems");
} // SystemSettings