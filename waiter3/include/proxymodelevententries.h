#ifndef PROXYMODELEVENTENTRIES_H
#define PROXYMODELEVENTENTRIES_H

//-----------------------------------------------------

namespace rotable{
    class PMFilterNew;
    class PMFilterToPay;
}

//-----------------------------------------------------

#include <QSortFilterProxyModel>

class rotable::PMFilterNew : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    PMFilterNew();

    bool filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const override;

};

class rotable::PMFilterToPay : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    PMFilterToPay();

    bool filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const override;

};

#endif // PROXYMODELEVENTENTRIES_H
