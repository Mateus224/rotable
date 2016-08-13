#include "usertablemodel.h"

//------------------------------------------------------------------------------

int UserTableModel::rowCount(const QModelIndex &parent) const
{
    _model.count();
}

//------------------------------------------------------------------------------s

QVariant UserTableModel::data(const QModelIndex &index, int role) const
{

}

//------------------------------------------------------------------------------

bool UserTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

//------------------------------------------------------------------------------

Qt::ItemFlags UserTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

//------------------------------------------------------------------------------

int UserTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return accountType + 1;
}

//------------------------------------------------------------------------------

QModelIndex UserTableModel::index(int row, int column, const QModelIndex &parent) const
{

}

//------------------------------------------------------------------------------

QVariant UserTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}

//------------------------------------------------------------------------------
