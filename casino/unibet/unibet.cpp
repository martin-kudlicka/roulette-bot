#include "unibet.h"

const QString Unibet::GetName() const
{
	return "Unibet";
} // GetName

Q_EXPORT_PLUGIN2(unibet, Unibet)