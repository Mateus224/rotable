#include <QDebug>
#include "../include/orderinformation.h"


OrderInformation::OrderInformation(QObject *parent) : QObject(parent)
{
}


OrderInformation::OrderInformation(const QString &name, const QString &order, QObject *parent)
    : QObject(parent), m_name(name), m_order(order)
{
}

QString OrderInformation::name() const
{
    return m_name;
}

void OrderInformation::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}

QString OrderInformation::order() const
{
    return m_order;
}

void OrderInformation::setorder(const QString &order)
{
    if (order != m_order) {
        m_order = order;
        emit orderChanged();
    }
}
