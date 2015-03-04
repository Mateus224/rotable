#include "../include/waiterappwindow.h"


WaiterAppWindow::WaiterAppWindow(QObject *parent)
{

}

WaiterAppWindow::~WaiterAppWindow()
{

}


//------------------------------------------------------------
double WaiterAppWindow::toPay() const
{
    return m_toPay;
}

void WaiterAppWindow::setToPay(const double &toPay)
{
    if (toPay != m_toPay) {
        m_toPay = toPay;
        emit toPayChanged();
    }
}
