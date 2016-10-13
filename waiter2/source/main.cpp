#include "private/precomp.h"
#include "../include/mytables.h"
#include "../include/orderinformation.h"
#include "../include/waiter_client.h"
#include "orderinformation.h"
#include "tablemodel.h"
#include "languagesupport.h"
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QCoreApplication>

#include <QStandardPaths>


//#include "client/linux/handler/exception_handler.h"

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  // Create minidump on program crash (for later debugging)
  //google_breakpad::MinidumpDescriptor breakpad_descriptor("/tmp");
  //google_breakpad::ExceptionHandler breakpad_handler(
  //  breakpad_descriptor, NULL, NULL, NULL, true, -1);

  //---------------------------------------------
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

  /* Load translator */

  rotable::LanguageSupport* langSupp = new rotable::LanguageSupport(rotable::LanguageSupport::AppType::waiter);
  langSupp->LoadInit();

  /* Connection to server building*/
//-----------------------------------------------------
  auto dir = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
  dir.mkpath("rotable");
  dir.cd("rotable");
  QString configFilePath(dir.filePath("config.ini"));

  QStringList args = parser.positionalArguments();

  if (args.size() > 0) {
    configFilePath = args[0];
  }

  rotable::Waiter_Client* waiter_client = new rotable::Waiter_Client(configFilePath);

  waiter_client->startup();

  QQuickView* view = new QQuickView();
  view->setTitle(QCoreApplication::translate("Title", "Waiter client"));

  QQmlContext *ctxt = view->rootContext();//view.rootContext();sss

  ctxt->setContextProperty("tables", &(waiter_client->_tables));
  ctxt->setContextProperty("orderboard", &(waiter_client->_board));
  ctxt->setContextProperty("productList", &(waiter_client->_productsList));
  ctxt->setContextProperty("needBoard", &(waiter_client->_needBoard));
  ctxt->setContextProperty("waiter", waiter_client);
  ctxt->setContextProperty("langObject", langSupp);
  //view->setSource(QString("qrc:/waiter/main2.qml"));

  QQmlEngine *engine = ctxt->engine();

  // Connect exit signal for exit
  QObject::connect(engine,  SIGNAL(quit()), qApp, SLOT(quit()));

  view->setSource(QUrl("qrc:/waiter/qml/main.qml"));
  view->show();
  return app.exec();
}
