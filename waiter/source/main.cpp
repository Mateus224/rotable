#include "private/precomp.h"

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

  //rotable::Client* client = new rotable::Client(configFilePath);

  //rotable::ImageProvider* imageProvider = new rotable::ImageProvider(client);
  //client->setImageProvider(imageProvider);

  QQuickView view;
  //client->startup();

  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.setSource(QString("qrc:/waiter/main.qml"));
  view.show();

  return app.exec();
}