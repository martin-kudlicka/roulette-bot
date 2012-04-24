#ifndef CASINOPLUGINS_H
#define CASINOPLUGINS_H

#include "../casinos/common/casinointerface.h"

class CasinoPlugins
{
	public:
		CasinoInterface *GetCasino(const quint8 &pIndex) const;
		const quint8 GetCount() const;
		const void Load();

	private:
		QList<CasinoInterface *> _qlCasinos;
}; // CasinoPlugins

#endif // CASINOPLUGINS_H