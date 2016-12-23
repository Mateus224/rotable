#include "private/precomp.h"

#include "mainwindow.h"
#include "controller.h"

#include "loglisternerstdout.h"

#include "statistik_plot.h"
#include "date.h"
#include "io_init.h"
#include "io_writeinmonthwithnewdata.h"

#include "languagesupport.h"

#include <QStandardPaths>
#include <QDir>

#define ThisDay "ThisDay.data"
#define umsatz "umsatz.data"

//#include "client/linux/handler/exception_handler.h"

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
//  Create minidump on program crash (for later debugging)
//  google_breakpad::MinidumpDescriptor breakpad_descriptor("/tmp");
//  google_breakpad::ExceptionHandler breakpad_handler(
//   breakpad_descriptor, NULL, NULL, NULL, true, -1);

  QApplication a(argc, argv);

  QCoreApplication::setApplicationName("rotable-admin");
  QCoreApplication::setApplicationVersion("1.0b");
  QCoreApplication::setOrganizationName("rotable");
  QCoreApplication::setOrganizationDomain("rotable.info");

  // Load translator
  rotable::LanguageSupport* langSupp = new rotable::LanguageSupport(rotable::LanguageSupport::AppType::admin);
  langSupp->LoadInit();

  QCommandLineParser parser;
  parser.setApplicationDescription("rotable client application");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("config", QCoreApplication::translate("main", "Path of the configuration file."));
  parser.process(a);

  auto dir = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
  dir.mkpath("rotable");
  dir.cd("rotable");
  QString configFilePath(dir.filePath("config.ini"));

  QStringList args = parser.positionalArguments();
  if (args.size() > 0) {
      qDebug()<<args.size();
    configFilePath = args[0];
  }

  MainWindow w;
  Controller controller(&w, configFilePath);
  w.show();
  return a.exec();
}
