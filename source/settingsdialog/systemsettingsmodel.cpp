#include "systemsettingsmodel.h"

SystemSettingsModel::SystemSettingsModel(const SystemPlugins *pSystems, QObject *pParent /* NULL */) : QAbstractItemModel(pParent)
{
	_spSystems = pSystems;
} // SystemSettingsModel

int SystemSettingsModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
	return ColumnCount;
} // columnCount

QVariant SystemSettingsModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	} // if

	const SystemInterface *siSystem = static_cast<const SystemInterface *>(index.internalPointer());
	switch (index.column()) {
	case ColumnName:
		return siSystem->GetName();
	} // switch

	return QVariant();
} // data

QVariant SystemSettingsModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
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

QModelIndex SystemSettingsModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
	return createIndex(row, column, _spSystems->GetSystem(row));
} // index

QModelIndex SystemSettingsModel::parent(const QModelIndex &index) const
{
	return QModelIndex();
} // parent

int SystemSettingsModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
	if (parent == QModelIndex()) {
		return _spSystems->GetCount();
	} else {
		return 0;
	} // if else
} // rowCount