#include "systemplugins.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QPluginLoader>

const QString DIR_SYSTEMS = "systems";

const quint8 SystemPlugins::GetCount() const
{
	return _qlSystems.size();
} // GetCount

SystemInterface *SystemPlugins::GetSystem(const quint8 &pIndex) const
{
	return _qlSystems.at(pIndex);
} // GetCasino

const void SystemPlugins::Load()
{
	QDir qdSystems(QCoreApplication::applicationDirPath());
	qdSystems.cd(DIR_SYSTEMS);

	foreach (QFileInfo qfiSystemDir, qdSystems.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
		QDir qdSystem(qfiSystemDir.filePath());

		foreach (QFileInfo qfiCasino, qdSystem.entryInfoList(QDir::Files)) {
			QPluginLoader qplLoader(qfiCasino.filePath());

			SystemInterface *siCasino = qobject_cast<SystemInterface *>(qplLoader.instance());
			if (siCasino) {
				_qlSystems.append(siCasino);
			} // if
		} // foreach
	} // foreach
} // Load