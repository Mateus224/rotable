#include "private/precomp.h"
#include "../include/mytables.h"
#include "../include/orderinformation.h"
#include "../include/waiter_client.h"
#include "orderinformation.h"
#include "tablelist.h"
#include "table.h"
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

  /* Connection to server building*/
//-----------------------------------------------------
  QString configFilePath("config.ini");

  QStringList args = parser.positionalArguments();
  if (args.size() > 0) {
    configFilePath = args[0];
  }

  rotable::Waiter_Client* waiter_client = new rotable::Waiter_Client(configFilePath);

  QQuickView* view=new QQuickView;
  waiter_client->startup();
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  QQmlContext *ctxt = view->engine()->rootContext();//view.rootContext();sss


  ProductOrderListModel *_productorderlistmodel = new ProductOrderListModel(waiter_client, waiter_client->_productOrder);
  view->rootContext()->setContextProperty("MyProductOrderList", _productorderlistmodel);
  //qmlContxt init(*ctxt);
  //init.initContxt(allTables);

  view->rootContext()->setContextProperty("TableList", (QObject*)&(waiter_client->_tables));

  view->setSource(QString("qrc:/waiter/main2.qml"));

  // Connect exit signal for exit
  QObject::connect(view->engine(),  SIGNAL(quit()), qApp, SLOT(quit()));

  view->show();

  return app.exec();
}
