#ifndef SYSTEM63_H
#define SYSTEM63_H

#include "../common/systeminterface.h"

class System63 : public SystemInterface
{
	Q_INTERFACES(SystemInterface)

	private:
		// interface
		virtual const void Reset();
}; // System63

#endif // SYSTEM63_H
