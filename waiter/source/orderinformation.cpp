#include <QDebug>
#include "../include/orderinformation.h"


OrderInformation::OrderInformation(QObject *parent) : QObject(parent)
{
}


OrderInformation::OrderInformation(const QString &name, const QString &color, QObject *parent)
    : QObject(parent), m_name(name), m_color(color)
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

QString OrderInformation::color() const
{
    return m_color;
}

void OrderInformation::setColor(const QString &color)
{
    if (color != m_color) {
        m_color = color;
        emit colorChanged();
    }
}
