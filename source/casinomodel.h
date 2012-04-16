#ifndef CASINOMODEL_H
#define CASINOMODEL_H

#include <QtCore/QAbstractItemModel>
#include "casinoplugins.h"

class CasinoModel : public QAbstractItemModel
{
	Q_OBJECT

	public:
		CasinoModel(QObject *pParent = NULL);

		const void SetCasinos(const CasinoPlugins *pCasinos);

	private:
		enum eColumn {
			ColumnName,
			ColumnActive,
			ColumnCount
		}; // eColumn

		const CasinoPlugins *_cpCasinos;

		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		virtual QModelIndex parent(const QModelIndex &index) const;
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

	signals:
		void ActiveChanged(const int &pRow, const bool &pActive);

	private slots:
		const void on_ciCasino_GameActiveChanged(const bool &pActive);
}; // CasinoModel

#endif // CASINOMODEL_H