#ifndef SYSTEMSETTINGSMODEL_H
#define SYSTEMSETTINGSMODEL_H

#include <QtCore/QAbstractItemModel>
#include "systemplugins.h"

class SystemSettingsModel : public QAbstractItemModel
{
	Q_ENUMS(eColumn)

	public:
		enum eColumn {
			ColumnName,
			ColumnCount
		}; // eColumn

		SystemSettingsModel(const SystemPlugins *pSystems, QObject *pParent = NULL);

		virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

	private:
		const SystemPlugins *_spSystems;

		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		virtual QModelIndex parent(const QModelIndex &index) const;
}; // SystemSettingsModel

#endif // SYSTEMSETTINGSMODEL_H