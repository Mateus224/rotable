#ifndef USERCONTAINER_H
#define USERCONTAINER_H

//------------------------------------------------------------------------------

#include "client.h"
#include <QObject>
#include <QHash>

//------------------------------------------------------------------------------

namespace rotable{
    class UserContainter;
}

using rotable::User;

//------------------------------------------------------------------------------

/**
 * @brief This class provide contener for Users
 *
 */
class rotable::UserContainter: public QObject{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent    pointer to parent object
     */
    explicit UserContainter(QObject *parent = nullptr);

    /**
     * @brief Method for add user
     * @
     * @param user
     */
    void addUser(User *user);

    QList<int> userIds() const;
    /**
     * @brief
     *
     * @return int
     */
    int count() const;
signals:
    /**
     * @brief
     *
     * @param user
     */
    void userAdded(User *user);
    /**
     * @brief
     *
     */
    void userRemoved();
    /**
     * @brief
     *
     */
    void userUpdated();
    /**
     * @brief
     *
     */
    void updateView();
private:
    QHash <int, User*> _users; /**< TODO: describe */
};

//------------------------------------------------------------------------------

#endif // USERCONTAINER_H
