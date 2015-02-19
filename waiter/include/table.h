#ifndef TABLE_H
#define TABLE_H
#include <QObject>

class table : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pieces READ tableNumber WRITE settableNumber NOTIFY tableNumberChanged)

public:
    table(QObject *parent=0);
    table(const int &tableNumber, QObject *parent=0);

    int tableNumber() const;
    void settableNumber(const int &tableNumber);


signals:
    void tableNumberChanged();

private:
    int m_tableNumber;
};

#endif // TABLE_H
