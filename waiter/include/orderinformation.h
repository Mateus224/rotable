#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H

#include <QObject>

class OrderInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

public:
    OrderInformation(QObject *parent=0);
    OrderInformation(const QString &name, const QString &color, QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QString color() const;
    void setColor(const QString &color);

signals:
    void nameChanged();
    void colorChanged();

private:
    QString m_name;
    QString m_color;
};

#endif // ORDERINFORMATION_H
