#include "casinomodel.h"

CasinoModel::CasinoModel(QObject *pParent /* NULL */) : QAbstractItemModel(pParent)
{
	_cpCasinos = NULL;
} // CasinoModel

int CasinoModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
	return ColumnCount;
} // columnCount

QVariant CasinoModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	} // if

	const CasinoInterface *ciCasino = static_cast<const CasinoInterface *>(index.internalPointer());
	switch (index.column()) {
		case ColumnName:
			return ciCasino->GetName();
		case ColumnActive:
			return ciCasino->GameActive() ? tr("Yes") : tr("No");
	} // switch

	return QVariant();
} // data

QVariant CasinoModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	} // if

	switch (section) {
		case ColumnName:
			return tr("Name");
		case ColumnActive:
			return tr("Active");
	} // switch

	return QVariant();
} // headerData

QModelIndex CasinoModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
	return createIndex(row, column, _cpCasinos->GetCasino(row));
} // index

const void CasinoModel::on_ciCasino_GameActiveChanged(const bool &pActive)
{
	for (int iRow = 0; iRow < rowCount(); iRow++) {
		QModelIndex qmiIndex = index(iRow, ColumnActive);
		if (qmiIndex.internalPointer() == sender()) {
			emit dataChanged(qmiIndex, qmiIndex);
		} // if
	} // for
} // on_ciCasino_GameActiveChanged

QModelIndex CasinoModel::parent(const QModelIndex &index) const
{
	return QModelIndex();
} // parent

int CasinoModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
	if (parent == QModelIndex()) {
		return _cpCasinos->GetCount();
	} else {
		return 0;
	} // if else
} // rowCount

const void CasinoModel::SetCasinos(const CasinoPlugins *pCasinos)
{
	beginResetModel();

	_cpCasinos = pCasinos;

	for (int iCasino = 0; iCasino < pCasinos->GetCount(); iCasino++) {
		const CasinoInterface *ciCasino = pCasinos->GetCasino(iCasino);
		connect(ciCasino, SIGNAL(GameActiveChanged(const bool &)), SLOT(on_ciCasino_GameActiveChanged(const bool &)));
	} // for

	endResetModel();
} // SetCasinos