#ifndef CASINOPLUGINS_H
#define CASINOPLUGINS_H

#include "../casinos/common/casinointerface.h"

class CasinoPlugins
{
	public:
		CasinoInterface *GetCasino(const int &pIndex) const;
		const int GetCount() const;
		const void Load();

	private:
		QList<CasinoInterface *> _qlCasinos;
}; // CasinoPlugins

#endif // CASINOPLUGINS_H
