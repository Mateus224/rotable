#include "neededboard.h"

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
    return QVariant();
}

//-----------------------------------------------------

int NeedBoard::count() const
{
    return _needs.count();
}

//-----------------------------------------------------

QHash<int, QByteArray> NeedBoard::roleNames() const
{
    return QHash<int, QByteArray>();
}

//-----------------------------------------------------
