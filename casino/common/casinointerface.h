#ifndef CASINOINTERFACE_H
#define CASINOINTERFACE_H

#include <QtPlugin>

static const char *CASINO_INTERFACE = "Casino Interface 1.0";

class CasinoInterface : public QObject
{
	Q_OBJECT

	public:
		virtual const bool GameActive() const = 0;
		virtual const QString GetName() const = 0;

	signals:
		void GameActiveChanged(const bool &pActive) const;
}; // CasinoInterface

Q_DECLARE_INTERFACE(CasinoInterface, CASINO_INTERFACE);

#endif // CASINOINTERFACE_H