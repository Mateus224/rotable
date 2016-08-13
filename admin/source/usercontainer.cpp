#include "usercontainer.h"

//------------------------------------------------------------------------------

rotable::UserContainter::UserContainter(QObject *parent): QObject(parent), _users()
{

}

//------------------------------------------------------------------------------

void rotable::UserContainter::addUser(rotable::User *user)
{
    if(!user)
        return;
    if(_users.contains(user->id()))
    {
        _users[user->id()]->updateData(user);
        emit updateView();
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
