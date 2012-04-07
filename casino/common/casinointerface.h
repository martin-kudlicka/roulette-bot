#ifndef CASINOINTERFACE_H
#define CASINOINTERFACE_H

#include <QtPlugin>

static const char *CASINO_INTERFACE = "Casino Interface 1.0";

class CasinoInterface
{
	public:
		virtual const QString GetName() const = 0;
}; // CasinoInterface

Q_DECLARE_INTERFACE(CasinoInterface, CASINO_INTERFACE);

#endif // CASINOINTERFACE_H