#ifndef SYSTEMPLUGINS_H
#define SYSTEMPLUGINS_H

#include "../systems/common/systeminterface.h"

class SystemPlugins
{
	public:
		const quint8 GetCount() const;
		SystemInterface *GetSystem(const quint8 &pIndex) const;
		const void Load();

	private:
		QList<SystemInterface *> _qlSystems;
}; // SystemPlugins

#endif // SYSTEMPLUGINS_H