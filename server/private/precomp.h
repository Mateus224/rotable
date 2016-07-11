#include <assert.h>

#include <QtGlobal>
#include <QString>
#include <QObject>
#include <QSqlDatabase>
#include <QMap>
#include <QTcpServer>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>
#include <QPixmap>
#include <QCommandLineParser>
#include <QBuffer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QResource>

#ifdef __ANDROID__
#include <android/api-level.h>
#endif
