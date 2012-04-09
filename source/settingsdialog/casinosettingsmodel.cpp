#include "casinosettingsmodel.h"

CasinoSettingsModel::CasinoSettingsModel(const CasinoPlugins *pCasinos, QObject *pParent /* NULL */) : QAbstractItemModel(pParent)
{
	_cpCasinos = pCasinos;
} // CasinoSettingsModel

int CasinoSettingsModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
	return ColumnCount;
} // columnCount

QVariant CasinoSettingsModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	} // if

	const CasinoInterface *ciCasino = static_cast<const CasinoInterface *>(index.internalPointer());
	switch (index.column()) {
	case ColumnName:
		return ciCasino->GetName();
	} // switch

	return QVariant();
} // data

QVariant CasinoSettingsModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	} // if

	switch (section) {
	case ColumnName:
		return tr("Name");
	} // switch

	return QVariant();
} // headerData

QModelIndex CasinoSettingsModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
	return createIndex(row, column, _cpCasinos->GetCasino(row));
} // index

QModelIndex CasinoSettingsModel::parent(const QModelIndex &index) const
{
	return QModelIndex();
} // parent

int CasinoSettingsModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
	if (parent == QModelIndex()) {
		return _cpCasinos->GetCount();
	} else {
		return 0;
	} // if else
} // rowCount