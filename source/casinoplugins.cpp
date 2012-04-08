#include "casinoplugins.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QPluginLoader>

CasinoInterface *CasinoPlugins::GetCasino(const int &pIndex) const
{
	return _qlCasinos.at(pIndex);
} // GetCasino

const int CasinoPlugins::GetCount() const
{
	return _qlCasinos.size();
} // GetCount

const void CasinoPlugins::Load()
{
	QDir qdCasinos(QCoreApplication::applicationDirPath());
	qdCasinos.cd("casino");

	foreach (QFileInfo qfiCasinoDir, qdCasinos.entryInfoList(QDir::Dirs)) {
		QDir qdCasino(qfiCasinoDir.filePath());

		foreach (QFileInfo qfiCasino, qdCasino.entryInfoList(QDir::Files)) {
			QPluginLoader qplLoader(qfiCasino.filePath());

			CasinoInterface *ciCasino = qobject_cast<CasinoInterface *>(qplLoader.instance());
			if (ciCasino) {
				_qlCasinos.append(ciCasino);
			} // if
		} // foreach
	} // foreach
} // Load