#include "private/precomp.h"

//#include "client/linux/handler/exception_handler.h"

#include "server.h"
#include "logmanager.h"
#include "loglisternerstdout.h"
#include "loglistenerfileout.h"

#include <QTextCodec>

#include <QStandardPaths>

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  // Create minidump on program crash (for later debugging)
//  google_breakpad::MinidumpDescriptor breakpad_descriptor("/tmp");
//  google_breakpad::ExceptionHandler breakpad_handler(
//        breakpad_descriptor, NULL, NULL, NULL, true, -1);

    //--------------------------------------------------
    // For test
     rotable::LogManager::getInstance()->registerQtWarnings();
     rotable::LogManager::getInstance()->addListener(new rotable::LogListenerStdOut());
     rotable::LogManager::getInstance()->addListener(new rotable::LogListenerFileOut());
    //--------------------------------------------------

  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("rotable-server");
  QCoreApplication::setApplicationVersion("1.0b");
  QCommandLineParser parser;
  parser.setApplicationDescription("rotable server application");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("config",
  QCoreApplication::translate("main", "Path of the configuration file."));

  QCommandLineOption createDbOption("createDb", "Create a new database");
  parser.addOption(createDbOption);
  parser.process(app);

  auto dir = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
  dir.mkpath("rotable");
  dir.cd("rotable");
  QString configFilePath(dir.filePath("config.ini"));
  rotable::LogManager::getInstance()->logInfo(configFilePath);
  QStringList args = parser.positionalArguments();
  if (args.size() > 0) {
    configFilePath = args[0];
  }


  rotable::Server server(configFilePath);
  if (!server.startup()) {
    exit(EXIT_FAILURE);
  }

  if (parser.isSet(createDbOption)) {
    server.createDatabase();
  }

  rotable::LogManager::getInstance()->startServer(5001);

  return app.exec();
}
