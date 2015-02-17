#include "private/precomp.h"
#include "../include/orderinformation.h"

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>

//#include "client/linux/handler/exception_handler.h"

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  // Create minidump on program crash (for later debugging)
  //google_breakpad::MinidumpDescriptor breakpad_descriptor("/tmp");
  //google_breakpad::ExceptionHandler breakpad_handler(
  //  breakpad_descriptor, NULL, NULL, NULL, true, -1);

  QGuiApplication app(argc, argv);

  QCoreApplication::setApplicationName("rotable-waiter");
  QCoreApplication::setApplicationVersion("1.0b");

  QCommandLineParser parser;
  parser.setApplicationDescription("rotable waiter application");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("config",
    QCoreApplication::translate("main", "Path of the configuration file."));
  parser.process(app);

  QString configFilePath("config.ini");

  QStringList args = parser.positionalArguments();
  if (args.size() > 0) {
    configFilePath = args[0];
  }

  //rotable::Client* client = new rotable::Client(configFilePath);

  //rotable::ImageProvider* imageProvider = new rotable::ImageProvider(client);
  //client->setImageProvider(imageProvider);

  //add information to qmllist
  QList<QObject*> dataList;
  dataList.append(new OrderInformation("Table 1", "red"));
  dataList.append(new OrderInformation("Table 2", "transparent"));
  dataList.append(new OrderInformation("Table 3", "red"));
  dataList.append(new OrderInformation("Table 4", "transparent"));
  dataList.append(new OrderInformation("Table 5", "transparent"));
  dataList.append(new OrderInformation("Table 6", "transparent"));
  dataList.append(new OrderInformation("Table 7", "transparent"));

  QQuickView view;
  //client->startup();

  view.setResizeMode(QQuickView::SizeRootObjectToView);
  QQmlContext *ctxt = view.rootContext();
  ctxt->setContextProperty("myModel", QVariant::fromValue(dataList));

  view.setSource(QString("qrc:/waiter/main.qml"));

  view.show();

  return app.exec();
}
