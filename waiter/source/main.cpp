#include "private/precomp.h"
#include "../include/mytables.h"
#include "../include/orderinformation.h"
#include "orderinformation.h"
#include "qmlcontxt.h"
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QtQuick>

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

  QQuickView view;
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  QQmlContext *ctxt = view.rootContext();

  qmlContxt init(*ctxt);
  init.initContxt(6,false);
  init.add_orderInfoForTable(0);
  init.contxt(1);
  view.setSource(QString("qrc:/waiter/main.qml"));





  //client->startup();

view.show();

  return app.exec();
}
