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
  QGuiApplication app(argc, argv);

  QCoreApplication::setApplicationName("rotable-waiter");
  QCoreApplication::setApplicationVersion("1.0");

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

  QQuickView* view = new QQuickView();
  view->setTitle(QCoreApplication::translate("Title", "Waiter client"));

  QQmlContext *ctxt = view->rootContext();//view.rootContext();sss

  QQmlEngine *engine = ctxt->engine();

  // Connect exit signal for exit
  QObject::connect(engine,  SIGNAL(quit()), qApp, SLOT(quit()));

  view->setSource(QUrl("qrc:/waiter/qml/main.qml"));
  view->show();
  return app.exec();
}
