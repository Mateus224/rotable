#include "waiter.h"

using namespace rotable;

//------------------------------------------------------------------------------

#include <QCryptographicHash>

//------------------------------------------------------------------------------

void Waiter::setPassword(QString password){
        QCryptographicHash hash(QCryptographicHash::Sha512); // I'm paranoid and I know it
        hash.addData(password.toUtf8().constData());
        QByteArray result = hash.result();
        _passwd = QString(result);
}
