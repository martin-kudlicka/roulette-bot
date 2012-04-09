#include "casinoplugins.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QPluginLoader>
#ifdef Q_WS_WIN
# include <Windows.h>
#endif

const QString DIR_CASINOS = "casinos";

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
	qdCasinos.cd(DIR_CASINOS);

	foreach (QFileInfo qfiCasinoDir, qdCasinos.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
		QDir qdCasino(qfiCasinoDir.filePath());
#ifdef Q_WS_WIN
		TCHAR tcCurrentDir[MAX_PATH];
		GetCurrentDirectory(sizeof(tcCurrentDir) / sizeof(TCHAR), tcCurrentDir);
		SetCurrentDirectory(qdCasino.path().utf16());
#endif

		foreach (QFileInfo qfiCasino, qdCasino.entryInfoList(QDir::Files)) {
			QPluginLoader qplLoader(qfiCasino.filePath());

			CasinoInterface *ciCasino = qobject_cast<CasinoInterface *>(qplLoader.instance());
			if (ciCasino) {
				_qlCasinos.append(ciCasino);
			} // if
		} // foreach

#ifdef Q_WS_WIN
		SetCurrentDirectory(tcCurrentDir);
#endif
	} // foreach
} // Load