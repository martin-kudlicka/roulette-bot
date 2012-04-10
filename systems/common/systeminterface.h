#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H

#include <QtPlugin>

static const char *SYSTEM_INTERFACE = "System Interface 1.0";

class SystemInterface : public QObject
{
	Q_OBJECT

	public:
		virtual const void CloseSettings(const QWidget *pSettings, const bool &pSave) const = 0;
		virtual QWidget *GetSettings() = 0;
		virtual const void Reset() = 0;
}; // SystemInterface

Q_DECLARE_INTERFACE(SystemInterface, SYSTEM_INTERFACE);

#endif // SYSTEMINTERFACE_H