#ifndef WAITERAPPWINDOW_H
#define WAITERAPPWINDOW_H
#include <QObject>

class WaiterAppWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double TooPay READ toPay WRITE setToPay NOTIFY toPayChanged)

public:
    WaiterAppWindow(QObject *parent=0);
    ~WaiterAppWindow();

    double toPay()const;
    void setToPay(const double &toPay);

private:
    double m_toPay;

signals:
    void toPayChanged();
};

#endif // WAITERAPPWINDOW_H
