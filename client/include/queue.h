#ifndef QUEUE_H
#define QUEUE_H
//------------------------------------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

//------------------------------------------------------------------------------

namespace rotable {
    class Queue;
}

//------------------------------------------------------------------------------
class rotable::Queue: public QObject{
    Q_OBJECT

    Q_PROPERTY(int queueOrder READ queueOrder WRITE setqueueOrder NOTIFY queueOrderChanged)
public:
    Queue():_queueOrder(0){}

    inline int queueOrder() const { return _queueOrder; }
    inline void setqueueOrder(int queueOrder)
        { _queueOrder = queueOrder; emit queueOrderChanged();}



signals:
    void queueOrderChanged();

private:
    int _queueOrder;

};

#endif // QUEUE_H
