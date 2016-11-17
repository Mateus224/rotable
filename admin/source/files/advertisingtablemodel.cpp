#include "include/files/advertisingtablemodel.h"

AdvertisingTableModel::AdvertisingTableModel(QObject *parent)
    : QAbstractTableModel(parent), _advertisingVideos(0)
{

}
//------------------------------------------------------------------------------

AdvertisingTableModel::~AdvertisingTableModel()
{

}

//------------------------------------------------------------------------------

int AdvertisingTableModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return _advertisingVideos->count();
}

//------------------------------------------------------------------------------s

QVariant AdvertisingTableModel::data(const QModelIndex &index, int role) const {
  if (role == Qt::BackgroundRole) {
    if (index.row() % 2) {
      return QVariant(QBrush(QColor(200, 250, 200)));
    } else {
      return QVariant(QBrush(QColor(220, 250, 220)));
    }
  }

  switch (index.column()) {
  case name: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::File *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_fileInfo._name);
      }
    }
  } break;
  case date: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::File *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_fileInfo._date);
      }
    }
  } break;
  }

  return QVariant();
}

//------------------------------------------------------------------------------

bool AdvertisingTableModel::setData(const QModelIndex &index, const QVariant &value,
                             int role) {
  if (role == Qt::EditRole) {
    switch (index.column()) {
    case name: {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::File *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        file->_fileInfo._name=value.toString();
        return true;
      }
    } break;
    case date: {
        QList<int> ids = _advertisingVideos->fileIds();
        Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
        rotable::File *file = _advertisingVideos->file(ids[index.row()]);
        Q_ASSERT(file);
        if (file) {
        file->_fileInfo._date= value.toString();
      }
    } break;
    }
  }
  return false;
}

//------------------------------------------------------------------------------

Qt::ItemFlags AdvertisingTableModel::flags(const QModelIndex &index) const {
  Q_UNUSED(index)
  return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

//------------------------------------------------------------------------------

int AdvertisingTableModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return name + 1;
}

//------------------------------------------------------------------------------

QModelIndex AdvertisingTableModel::index(int row, int column,
                                  const QModelIndex &parent) const {
  if (!parent.isValid()) {
    QList<int> ids = _container->userIds();
    if (row >= 0 && row < ids.size() && column >= 0 && column <= accountType) {
      return createIndex(row, column, ids[row]);
    }
  }

  return QModelIndex();
}

//------------------------------------------------------------------------------

QVariant AdvertisingTableModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  if (orientation == Qt::Horizontal) {
    if (role == Qt::DisplayRole) {
      switch (section) {
      case name: {
        return QVariant("Name");
      } break;
      case date: {
        return QVariant("Date");
      } break;
      }
    }
  }

  return QVariant();
}

//------------------------------------------------------------------------------

void AdvertisingTableModel::setUserContainer(FileContainer *model) {
    _advertisingVideos = model;
}

//------------------------------------------------------------------------------

void AdvertisingTableModel::updateModel()
{
    beginResetModel();
    endResetModel();
}

//------------------------------------------------------------------------------
