#ifndef ROTABLE_MESSAGECONNECTOR_H
#define ROTABLE_MESSAGECONNECTOR_H

#ifndef QOBJECT_H
#include <QObject>
#endif

#include "message.h"

namespace rotable {
    class MessageConnector;
}


class rotable::MessageConnector : public QObject
{
    Q_OBJECT
public:
    explicit MessageConnector(QObject *parent = 0);

signals:

public slots:
};

#endif // ROTABLE_MESSAGECONNECTOR_H
