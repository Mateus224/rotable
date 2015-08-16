#include "private/precomp.h"
#include "../include/mytables.h"
#include "../include/orderinformation.h"
#include "../include/waiter_client.h"
#include "orderinformation.h"
#include "table.h"
#include <QGuiApplication>
#include <qqmlengine.h>
#include <QQmlContext>
#include <qqml.h>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>
#include <QtQuick>
#include <tablemodel.h>



//#include "client/linux/handler/exception_handler.h"

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  // Create minidump on program crash (for later debugging)
  //google_breakpad::MinidumpDescriptor breakpad_descriptor("/tmp");
  //google_breakpad::ExceptionHandler breakpad_handler(
  //  breakpad_descriptor, NULL, NULL, NULL, true, -1);

  //Test values
  //---------------------------------------------
    int tableNr=0;
    int allTables=7;


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

  /* Connection to server building*/
//-----------------------------------------------------
  QString configFilePath("config.ini");

  QStringList args = parser.positionalArguments();
  if (args.size() > 0) {
    configFilePath = args[0];
  }

  rotable::Waiter_Client* waiter_client = new rotable::Waiter_Client(configFilePath);

  waiter_client->startup();
  QQuickView* view=new QQuickView();

  view->setResizeMode(QQuickView::SizeRootObjectToView);
  QQmlContext *ctxt = view->rootContext();//view.rootContext();sss

  //qmlContxt init(*ctxt);
  //init.initContxt(allTables);

  ctxt->setContextProperty("tables", &(waiter_client->_tables));
  ctxt->setContextProperty("orderboard", &(waiter_client->_board));

  view->setSource(QString("qrc:/waiter/main2.qml"));

  // Connect signal from table click to update order list
  QObject::connect(view->rootObject(),  SIGNAL(sendToBoardOrder(int)), &(waiter_client->_tables), SLOT(sendToBoardOrder(int)));
  // Connect exit signal for exit
  QObject::connect(view->engine(),  SIGNAL(quit()), qApp, SLOT(quit()));

  view->show();

  return app.exec();
}
