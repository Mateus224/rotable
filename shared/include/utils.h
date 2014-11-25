#ifndef ROTABLE_UTILS_H
#define ROTABLE_UTILS_H

//------------------------------------------------------------------------------

#ifndef QABSTRACTSOCKET_H
#include <QAbstractSocket>
#endif

//------------------------------------------------------------------------------

/**
 * Get a string describing the given socket error.
 *
 * @param socketError       socket error
 * @return                  message
 */
QString SocketErrorToString(QAbstractSocket::SocketError socketError);

/**
 * Sleep function that does still process events.
 *
 * @param ms                milliseconds to sleep
 */
void delay(int ms);

//------------------------------------------------------------------------------

#endif // ROTABLE_UTILS_H
