#include "private/precomp.h"
#include "../include/table.h"
#include "../include/orderinformation.h"
#include "orderinformation.h"
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

  QList <table*>  tableNumber;
  int NumberOfTables=6;
  for(int i=0;i <NumberOfTables; i++)
  {
    tableNumber.append(new table(3, "Table 1", "Hallo", 3, "Sambuca", 2, true, false ));
  }


  QQuickView view;

  //client->startup();

  table* tab=new table;
  int position;
  position=tab->tableNumber();
  qDebug()<<position;
  tab=tableNumber.at(position);
  tab->add_orderinformation("Table 1", "Hallo", 3, "Sambuca", 2, false, false );
  tab->add_orderinformation("Table 2", "Hallo", 3, "Vodka", 2, false, false );
  tab->add_orderinformation("Table 3", "Nie", 2, "Vodka", 3, true, false );


  view.setResizeMode(QQuickView::SizeRootObjectToView);
  QQmlContext *ctxt = view.rootContext();
  //OrderInformation orderinformation;
  ctxt->setContextProperty("con", tab);
  ctxt->setContextProperty("myModel", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));
  ctxt->setContextProperty("table", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));
  view.setSource(QString("qrc:/waiter/main.qml"));


view.show();

  return app.exec();
}
