#include "waiter.h"

using namespace rotable;

//------------------------------------------------------------------------------

#include <QCryptographicHash>

//------------------------------------------------------------------------------

void Waiter::setPassword(QString password){
    // Create cryptograpy hash generator, initialized with hash type
    QCryptographicHash hash(QCryptographicHash::Sha512);    // I'm paranoid and I know it
    hash.addData(password.toUtf8().constData());            // add password
    QByteArray result = hash.result();                      // get hash from password
    _passwd = QString(result);                              // set _passwd with hash
}
