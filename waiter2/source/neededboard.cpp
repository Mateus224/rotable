#include "neededboard.h"
#include "QDebug"

//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

NeedBoard::NeedBoard(QObject *parent) : QAbstractListModel(parent)
{

}

//-----------------------------------------------------

NeedBoard::~NeedBoard()
{

}

//-----------------------------------------------------

int NeedBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return count();
}

//-----------------------------------------------------

QVariant NeedBoard::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= _needs.count())
        return QVariant();


    rotable::Table *table = _needs[index.row()];
    switch(role){
    case NameRole:
        return QVariant(table->name());
    case IdxRole:
        return QVariant(index.row());
    default:
        qCritical() << "Role don't exists";
    }
}

//-----------------------------------------------------

int NeedBoard::count() const
{
    return _needs.count();
}

//-----------------------------------------------------

void NeedBoard::unneedTable(int idx)
{
    emit unsetWaiterNeed(_needs.at(idx)->id());
}

//-----------------------------------------------------

void NeedBoard::addTable(Table *table)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _needs.append(table);
    endInsertRows();
}

//-----------------------------------------------------

QHash<int, QByteArray> NeedBoard::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[NameRole] = "tableName";
    roles[IdxRole] = "tableIdx";

    return roles;
}

//-----------------------------------------------------

void NeedBoard::tableNeedChanged()
{
    Table *table = dynamic_cast<Table*>(QObject::sender());
    if(table)
    {
        if(table->waiterIsNeeded())
            addTable(table);
        else
            removeTable(table);
    }
    else
        qCritical() << "Someone call method, forbiden";
}

//-----------------------------------------------------

void NeedBoard::removeTable(Table* table)
{
    int idx = _needs.indexOf(table);
    if(idx != -1){
        beginRemoveRows(QModelIndex(), idx, idx);
        _needs.removeAt(idx);
        endRemoveRows();
    }
}

//-----------------------------------------------------
