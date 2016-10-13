#include "usercontainer.h"

//------------------------------------------------------------------------------

rotable::UserContainter::UserContainter(QObject *parent): QObject(parent), _users()
{
    connect(this, &UserContainter::userAdded, this, &UserContainter::updateView);
    connect(this, &UserContainter::userRemoved, this, &UserContainter::updateView);
    connect(this, &UserContainter::userUpdated, this, &UserContainter::updateView);
}

//------------------------------------------------------------------------------

rotable::UserContainter::~UserContainter()
{
    clear();
}

//------------------------------------------------------------------------------

void rotable::UserContainter::addUser(rotable::User *user)
{
    if(!user)
        return;
    if(_users.contains(user->id()))
    {
        _users[user->id()]->updateData(user);
        emit userUpdated();
    }
    else
    {
        _users[user->id()] = user;
        connect(user, &User::userChanged, this, &UserContainter::userUpdated);
        emit userAdded(user);
    }
}

//------------------------------------------------------------------------------

QList<int> rotable::UserContainter::userIds() const
{
    return _users.keys();
}

//------------------------------------------------------------------------------

int rotable::UserContainter::count() const
{
    return _users.count();
}

//------------------------------------------------------------------------------

rotable::User *rotable::UserContainter::user(int idx) const
{
    return _users[idx];
}

//------------------------------------------------------------------------------

void rotable::UserContainter::changeAccountType(int id, int accountType) const
{
    Q_UNIMPLEMENTED();
    Q_UNUSED(id)
    Q_UNUSED(accountType)
    //TODO: implement
}

//------------------------------------------------------------------------------

void rotable::UserContainter::clear()
{
    qDeleteAll(_users.begin(), _users.end());
    _users.clear();
    emit updateView();
}

//------------------------------------------------------------------------------

void rotable::UserContainter::setSelectedUser(int idx)
{
  selectedUser = _users.values()[idx];
}

//------------------------------------------------------------------------------

rotable::User *rotable::UserContainter::getSelectedUser() const
{
    return selectedUser;
}

//------------------------------------------------------------------------------

void rotable::UserContainter::setSelectedUser(User *value)
{
    selectedUser = value;
}

//------------------------------------------------------------------------------
