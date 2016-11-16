#ifndef FILECONTAINER_H
#define FILECONTAINER_H

#include <QObject>

class filecontainer : public QObject
{
    Q_OBJECT
public:
    explicit filecontainer(QObject *parent = 0);

signals:

public slots:
};

#endif // FILECONTAINER_H