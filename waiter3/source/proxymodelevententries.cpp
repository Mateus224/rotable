#include "proxymodelevententries.h"
#include "orderboard.h"

rotable::PMFilterNew::PMFilterNew()
{
}

bool rotable::PMFilterNew::filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const
{
    bool ret( false );
    if ( this->sourceModel() != nullptr )
    {
        auto index = this->sourceModel()->index( source_row, 0, source_parent );
        if ( index.isValid() )
        {
            auto valueRole = index.data( rotable::OrderBoard::BoardRoles::StatusRole );
            if ( valueRole.isValid() )
            {
                bool ok( false );
                auto value = valueRole.toInt( &ok );
                if ( ok )
                {
                    if ( value == 0 )
                    {
                        ret = true;
                    }
                }
            }
        }
    }
    return ret;
}

rotable::PMFilterToPay::PMFilterToPay()
{
}

bool rotable::PMFilterToPay::filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const
{
    bool ret( false );
    if ( this->sourceModel() != nullptr )
    {
        auto index = this->sourceModel()->index( source_row, 0, source_parent );
        if ( index.isValid() )
        {
            auto valueRole = index.data( rotable::OrderBoard::BoardRoles::StatusRole );
            if ( valueRole.isValid() )
            {
                bool ok( false );
                auto value = valueRole.toInt( &ok );
                if ( ok )
                {
                    if ( value == 3 )
                    {
                        ret = true;
                    }
                }
            }
        }
    }
    return ret;
}
