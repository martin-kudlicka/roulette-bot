#ifndef UNIBET_H
#define UNIBET_H

#include "../common/casinointerface.h"

class Unibet : public QObject, private CasinoInterface
{
	Q_OBJECT
	Q_INTERFACES(CasinoInterface)

	private:
		virtual const QString GetName() const;
}; // Unibet

#endif // UNIBET_H