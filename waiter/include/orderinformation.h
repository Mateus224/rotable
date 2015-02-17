#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H

#include <QObject>

class OrderInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ order WRITE setorder NOTIFY orderChanged)

public:
    OrderInformation(QObject *parent=0);
    OrderInformation(const QString &name, const QString &order, QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QString order() const;
    void setorder(const QString &order);

signals:
    void nameChanged();
    void orderChanged();

private:
    QString m_name;
    QString m_order;
};

#endif // ORDERINFORMATION_H
