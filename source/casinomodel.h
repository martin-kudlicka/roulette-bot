#ifndef CASINOMODEL_H
#define CASINOMODEL_H

#include <QtCore/QAbstractItemModel>
#include "casinoplugins.h"

class CasinoModel : public QAbstractItemModel
{
	public:
		CasinoModel(const CasinoPlugins *pCasinos, QObject *pParent = NULL);

	private:
		enum eColumn {
			ColumnName,
			ColumnCount
		}; // eColumn

		const CasinoPlugins *_cpCasinos;

		virtual int	columnCount(const QModelIndex &parent = QModelIndex()) const;
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		virtual QModelIndex parent(const QModelIndex &index) const;
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
}; // CasinoModel

#endif // CASINOMODEL_H
