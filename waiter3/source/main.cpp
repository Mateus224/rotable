#include "private/precomp.h"
#include "../include/mytables.h"
#include "../include/orderinformation.h"
#include "../include/waiter_client.h"
#include "orderinformation.h"
#include "tablemodel.h"
#include "languagesupport.h"
#include "batteryinfo.h"
#include "proxymodelevententries.h"
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QCoreApplication>

#include <QStandardPaths>


//#include "client/linux/handler/exception_handler.h"
#include "loglistenerfileout.h"

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{

  //this command is necessary to use virtual keyboard in qml
  qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

  //--------------------------------------------------
  // Teporary testing logging, remove it after done
  // rotable::LogManager::getInstance()->registerQtWarnings();
  rotable::LogManager::getInstance()->addListener(new rotable::LogListenerFileOut("waiterlog.txt"));
  //--------------------------------------------------

  QGuiApplication app(argc, argv);

  QCoreApplication::setApplicationName("rotable-waiter");
  QCoreApplication::setApplicationVersion("1.0");
  app.setWindowIcon(QIcon(":/resources/icon/waiter_icon.ico"));

  QCommandLineParser parser;
  parser.setApplicationDescription("rotable waiter application");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("config",
  QCoreApplication::translate("main", "Path of the configuration file."));
  parser.process(app);

#ifdef __linux__
  //system("qjackctl -s &"); //maybe you need it
#elif _WIN32

#endif

  /* Load translator */

  rotable::LanguageSupport* langSupp = new rotable::LanguageSupport(rotable::LanguageSupport::AppType::waiter);
  langSupp->LoadInit();

  /* Load battery info class */

  rotable::BatteryInfo* batteryInfo = new rotable::BatteryInfo();

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
  ctxt->setContextProperty("batteryInfo", batteryInfo);

  rotable::PMFilterNew* filterNewOrders = new rotable::PMFilterNew();
  filterNewOrders->setSourceModel(&(waiter_client->_board));

  rotable::PMFilterToPay* filterToPayOrders = new rotable::PMFilterToPay();
  filterToPayOrders->setSourceModel(&(waiter_client->_board));

  ctxt->setContextProperty("orderFilterNew", filterNewOrders);
  ctxt->setContextProperty("orderFilterToPay", filterToPayOrders);

  QQmlEngine *engine = ctxt->engine();

  // Connect exit signal for exit
  QObject::connect(engine,  SIGNAL(quit()), qApp, SLOT(quit()));

  view->setSource(QUrl("qrc:/resources/qml/main.qml"));
  view->setResizeMode(QQuickView::SizeRootObjectToView);

  view->showMaximized();
  return app.exec();
}
