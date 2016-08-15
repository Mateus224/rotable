#include "usertablemodel.h"

#include <QBrush>
#include <QColor>

//------------------------------------------------------------------------------

UserTableModel::UserTableModel() : QAbstractTableModel() {}

//------------------------------------------------------------------------------

int UserTableModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return _container->count();
}

//------------------------------------------------------------------------------s

QVariant UserTableModel::data(const QModelIndex &index, int role) const {
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
      QList<int> ids = _container->userIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::User *user = _container->user(ids[index.row()]);
      Q_ASSERT(user);
      if (user) {
        return QVariant(user->name());
      }
    }
  } break;
  //  case nick: {
  //    if (role == Qt::DisplayRole || role == Qt::EditRole) {
  //      QList<int> ids = _container.userIds();
  //      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
  //      User *user = _container.user(ids[index.row()]);
  //      Q_ASSERT(user);
  //      if (user) {
  //        return QVariant(user->nick());
  //      }
  //    }
  //  } break;
  case accountType: {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> ids = _container->userIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::User *user = _container->user(ids[index.row()]);
      Q_ASSERT(user);
      if (user) {
        return QVariant(user->accountType());
      }
    }
  } break;
  }

  return QVariant();
}

//------------------------------------------------------------------------------

bool UserTableModel::setData(const QModelIndex &index, const QVariant &value,
                             int role) {
  if (role == Qt::EditRole) {
    switch (index.column()) {
    case name: {
      QList<int> ids = _container->userIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::User *user = _container->user(ids[index.row()]);
      Q_ASSERT(user);
      if (user) {
        user->setName(value.toString());
        return true;
      }
    } break;
    //    case nick: {
    //      QList<int> ids = _container.userIds();
    //      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
    //      User *user = _container.user(ids[index.row()]);
    //      Q_ASSERT(user);
    //      if (user) {
    //        user->setNick(value.toString());
    //        return true;
    //      }
    //    } break;
    case accountType: {
      QList<int> ids = _container->userIds();
      Q_ASSERT(index.row() >= 0 && index.row() < ids.count());
      rotable::User *user = _container->user(ids[index.row()]);
      Q_ASSERT(user);
      if (user) {
        _container->changeAccountType(user->id(), value.toInt());
      }
    } break;
    }
  }
  return false;
}

//------------------------------------------------------------------------------

Qt::ItemFlags UserTableModel::flags(const QModelIndex &index) const {
  Q_UNUSED(index)
  return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

//------------------------------------------------------------------------------

int UserTableModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return accountType + 1;
}

//------------------------------------------------------------------------------

QModelIndex UserTableModel::index(int row, int column,
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

QVariant UserTableModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  if (orientation == Qt::Horizontal) {
    if (role == Qt::DisplayRole) {
      switch (section) {
      case name: {
        return QVariant("Name");
      } break;
      //        case nick:
      //        {
      //          return QVariant("Nick");
      //        } break;
      case accountType: {
        return QVariant("AccountType");
      } break;
      }
    }
  }

  return QVariant();
}

//------------------------------------------------------------------------------

void UserTableModel::setUserContainer(rotable::UserContainter *model) {
    _container = model;
}

//------------------------------------------------------------------------------

void UserTableModel::updateModel()
{
    beginResetModel();
    endResetModel();
}

//------------------------------------------------------------------------------
