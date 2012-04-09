#ifndef CASINOSETTINGSMODEL_H
#define CASINOSETTINGSMODEL_H

#include <QtCore/QAbstractItemModel>
#include "casinoplugins.h"

class CasinoSettingsModel : public QAbstractItemModel
{
	public:
		enum eColumn {
			ColumnName,
			ColumnCount
		}; // eColumn

		CasinoSettingsModel(const CasinoPlugins *pCasinos, QObject *pParent = NULL);

		virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

	private:
		const CasinoPlugins *_cpCasinos;

		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		virtual QModelIndex parent(const QModelIndex &index) const;
}; // CasinoSettingsModel

#endif // CASINOSETTINGSMODEL_H