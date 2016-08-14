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
      * @brief Default destructor
      */
    ~UserContainter();

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

    /**
     * @brief Get user base on id
     * @param id    user id
     * @return      user object
     */
    User* user(int idx) const;

    /**
     * @brief Function for change property account type
     *
     * @param id   user id
     * @param accountType   new account tyoe
     */
    void changeAccountType(int id, int accountType) const;


    /**
     * @brief Clear object
     *
     */
    void clear();
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
    QHash <int, User*> _users; /** Container with users */
};

//------------------------------------------------------------------------------

#endif // USERCONTAINER_H
