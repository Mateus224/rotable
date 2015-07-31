#include "tablemodel.h"

//-----------------------------------------------------

using rotable::TableModel;
using rotable::Table;

//-----------------------------------------------------

TableModel::TableModel(QObject *parent): QObject(parent)
{

}

//-----------------------------------------------------

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[SizeRole] = "size";
    return roles;
}

//-----------------------------------------------------

int TableModel::rowCount(const QModelIndex &parent) const
{

}

//-----------------------------------------------------

int TableModel::columnCount(const QModelIndex &parent) const
{

}

//-----------------------------------------------------

QVariant TableModel::data(const QModelIndex &index, int role) const
{

}

//-----------------------------------------------------

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}

//-----------------------------------------------------
