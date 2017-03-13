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
    if (parent.isValid()) {
      return 0;
    } else {
        return _advertisingVideos->count();
    }
}

//------------------------------------------------------------------------------

QVariant AdvertisingTableModel::data(const QModelIndex &index, int role) const {

  if (role == Qt::BackgroundRole) {
    if (index.row() % 2 && (index.column()<5) ) {
      return QVariant(QBrush(QColor(200, 250, 200)));
    } else if(index.column()<5 ) {
      return QVariant(QBrush(QColor(220, 250, 220)));
    }
    else if (index.row() % 2 && (index.column()==6) )
      return QVariant(QBrush(QColor(200, 200, 250)));
    else if(index.column()==6)
      return QVariant(QBrush(QColor(220, 220, 250)));

    if (index.row() % 2 && (index.column()==5) )
      return QVariant(QBrush(QColor(200, 200, 250)));
    else if(index.column()==5)
      return QVariant(QBrush(QColor(220, 220, 250)));
  }

  switch (index.column()) {
  case name: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_fileInfo._name);
      }
    }
  } break;
  case size: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_fileInfo._size/1000000);
      }
    }
  } break;
  case date: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_fileInfo._date);
      }
    }
  } break;
  case duration: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_advertisingInfo._duration/1000);
      }
    }
  }
  case played: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_advertisingInfo._played);
      }
    }
  } break;
  case playTime: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_advertisingInfo._playTime);
      }
    }
  } break;
  case play: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _advertisingVideos->fileIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        return QVariant(file->_advertisingInfo._play);
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
      rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
      Q_ASSERT(file);
      if (file) {
        //file->setName(value.toString());
        return true;
      }
    } break;
    case size: {
        QList<int> ids = _advertisingVideos->fileIds();
        Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
        rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
        Q_ASSERT(file);
        if (file) {
        //file->setSize(value.toInt());
      }
    } break;
    case date: {
        QList<int> ids = _advertisingVideos->fileIds();
        Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
        rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
        Q_ASSERT(file);
        if (file) {
        //file->setDate(value.toString());
      }
    } break;
    case duration: {
        QList<int> ids = _advertisingVideos->fileIds();
        Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
        rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
        Q_ASSERT(file);
        if (file) {
        //file->_advertisingInfo._played = value.toInt();
      }
    } break;
    case played: {
        QList<int> ids = _advertisingVideos->fileIds();
        Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
        rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
        Q_ASSERT(file);
        if (file) {
        //file->_advertisingInfo._played = value.toInt();
      }
    } break;
    case playTime: {
        QList<int> ids = _advertisingVideos->fileIds();
        Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
        rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
        Q_ASSERT(file);
        if (file) {
        file->setPlayTime(value.toInt());
        _advertisingVideos->playTimeNextElement(file->getA_id());
      }
    } break;
    case play: {
        QList<int> ids = _advertisingVideos->fileIds();
        Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
        rotable::AdvertisingVideo *file = _advertisingVideos->file(ids[index.row()]);
        Q_ASSERT(file);
        if (file) {
        file->setPlay(value.toBool());
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
  return play + 1;
}

//------------------------------------------------------------------------------

QModelIndex AdvertisingTableModel::index(int row, int column,
                                  const QModelIndex &parent) const {
  if (!parent.isValid()) {
    QList<int> ids = _advertisingVideos->fileIds();
    if (row >= 0 && row < ids.size() && column >= 0 && column <=play) {
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
          case size: {
            return QVariant("Size [MB]");
          } break;
          case duration: {
            return QVariant("Duration [sec]");
          } break;
          case date: {
            return QVariant("Date");
          } break;
          case played:{
              return QVariant("Played");
          } break;
          case playTime: {
           return QVariant("Play Time [%]");
          } break;
          case play: {
           return QVariant("Play");
         } break;
       }
    }
  }


  return QVariant();
}

//------------------------------------------------------------------------------

void AdvertisingTableModel::setFileContainer(rotable::AdvertisingContainer *model) {
    _advertisingVideos = model;
}

//------------------------------------------------------------------------------

void AdvertisingTableModel::updateModel()
{
    beginResetModel();
    endResetModel();
}

//------------------------------------------------------------------------------
