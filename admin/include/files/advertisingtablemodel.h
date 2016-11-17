#ifndef ADVERTISINGTABLEMODEL_H
#define ADVERTISINGTABLEMODEL_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QAbstractTableModel>
#include "files/filecontainer.h"

//------------------------------------------------------------------------------

class AdvertisingTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AdvertisingTableModel(QObject *parent = 0);

    ~AdvertisingTableModel();

    void setFileContainer(FileContainer* products);

    /**
     * Returns the number of rows under the given parent.
     *
     * When the parent is valid it means that rowCount is returning the number of
     * children of parent.
     *
     * @param parent              parent
     * @return                    number of rows
     */
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    /**
     * Returns the data stored under the given role for the item referred to by
     * the index.
     *
     * @param index               data index
     * @param role                data role
     * @return                    data
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    /**
     * This method gets called, when a user edits the table data.
     *
     * @param index               item index
     * @param value               new item value
     * @param role                role
     * @return                    true on success
     */
    bool setData(const QModelIndex & index, const QVariant & value,
                 int role = Qt::EditRole);

    /**
     * Returns the item flags for the given index.
     *
     * @param index               item index
     * @return                    item flags
     */
    Qt::ItemFlags flags(const QModelIndex & index) const;

    /**
     * Returns the number of columns for the children of the given parent.
     *
     * @param parent              parent item
     * @return                    column count
     */
    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    /**
     * Returns the index of the data in row and column with parent.
     *
     * @param row               row
     * @param column            column
     * @param parent            parent
     * @return                  index
     */
    QModelIndex index(int row, int column = 0,
                      const QModelIndex & parent = QModelIndex()) const;

    /**
     * Returns the data for the given role and section in the header with the
     * specified orientation.
     *
     * @param section
     * @param orientation
     * @param role
     * @return
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

signals:

public slots:
    /**
     * A new AdvertisingVideo has been added.
     *
     * @param id                  id of new product
     */
    void onAdvertisingVideoAdded(int id);

    /**
     * A AdvertisingVideo has been removed.
     *
     * @param product             removed product
     */
    void onAdvertisingVideoRemoved(rotable::Product* product);

    /**
     * A AdvertisingVideo has been updated.
     *
     * @param product             updated product
     */
    void onAdvertisingVideoUpdated(rotable::Product* product);

public:
    enum Columns{
        name=0,
        size,
        date,
        played,
        frequnecy,
        play
    };

private:
    /* Product container */
    FileContainer* _advertisingVideos;
};

#endif // ADVERTISINGTABLEMODEL_H
