#ifndef SYSTEM63_H
#define SYSTEM63_H

#include "../common/systeminterface.h"
#include "system63settings.h"

class System63 : public SystemInterface
{
	Q_OBJECT
	Q_INTERFACES(SystemInterface)

	private:
		System63Settings _s63sSettings;

		// interface
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const;
		virtual QWidget *GetSettings();
		virtual const void Reset();
}; // System63

#endif // SYSTEM63_H
