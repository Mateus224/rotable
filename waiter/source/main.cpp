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

  QString configFilePath("config.ini");

  QStringList args = parser.positionalArguments();
  if (args.size() > 0) {
    configFilePath = args[0];
  }

  QQuickView* view=new QQuickView;
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  QQmlContext *ctxt = view->engine()->rootContext();//view.rootContext();

  qmlContxt init(*ctxt);
  init.initContxt(allTables);
  //For tests
  //-----------------------------------------------------
  init.add_orderInfoForTable(tableNr,1, "Sambuca",2.1);
  init.add_orderInfoForTable(tableNr+1,3, "Banana Split Shooter",22.60);
  init.add_orderInfoForTable(tableNr+1,3, "Kangeru",22.60);
  init.add_orderInfoForTable(tableNr+1,3, "Tequilla sunrise",22.60);
  init.add_orderInfoForTable(tableNr+1,3, "Banana Split Shooter",8.80);
  init.add_orderInfoForTable(tableNr+1,3, "Swimming Pool",20.60);
  init.add_orderInfoForTable(tableNr+1,3, "Long Island Ice Tea",22.60);
  init.add_orderInfoForTable(tableNr+1,3, "Hacke Beck",12.60);
  init.add_orderInfoForTable(tableNr+1,3, "Gin Tonic Hendrix",22.60);
  init.add_orderInfoForTable(tableNr+1,3, "Gin Tonic Tanquerry",22.60);
  init.add_orderInfoForTable(tableNr+1,3, "Banana Split Shooter",22.60);
  init.add_orderInfoForTable(tableNr+2,3, "Gin Tonic Bombay",18.3);
  init.add_orderInfoForTable(tableNr+3,3, "Sambuca",2.4);
  init.add_orderInfoForTable(tableNr+4,3, "Champan Bottle",100.00);
  init.add_orderInfoForTable(tableNr+5,3, "Vodka shot",2.1);
  init.add_orderInfoForTable(tableNr+1,3, "Tequilla Gold",3.1);
  init.add_orderInfoForTable(tableNr+1,3, "Sambuca",2.1);
  init.add_orderInfoForTable(tableNr+2,3, "Becks non-Alcoholic",4.1);
  init.add_orderInfoForTable(tableNr+2,3, "Sambuca Coffee",2.1);
  //-------------------------------------------------------------



  init.contxt(0);
  view->setSource(QString("qrc:/waiter/main.qml"));

  init.tableNumber.at(2)->setNewOrder("red");
  init.tableNumber.at(2)->setCallWaiter("blue");
  init.resetOldCurrentTable();
  init.tableNumber.at(3)->setNewOrder("red");
  init.tableNumber.at(6)->setCallWaiter("blue");
  //init.tableNumber.at(3)->setCallWaiter("blue");
  init.addAllPrices();


  //client->startup();

view->show();

  return app.exec();
}
