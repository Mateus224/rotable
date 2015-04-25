#include "private/precomp.h"

//#include "client/linux/handler/exception_handler.h"

#include "client.h"
#include "settings.h"
#include "imageprovider.h"
#include "productorder.h"

#ifdef __arm__
#include <wiringPi.h>
#include <iostream>
#endif

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  // Create minidump on program crash (for later debugging)
  //google_breakpad::MinidumpDescriptor breakpad_descriptor("/tmp");
  //google_breakpad::ExceptionHandler breakpad_handler(
  //  breakpad_descriptor, NULL, NULL, NULL, true, -1);

  QGuiApplication app(argc, argv);

  QCoreApplication::setApplicationName("rotable-client");
  QCoreApplication::setApplicationVersion("1.0b");

  QCommandLineParser parser;
  parser.setApplicationDescription("rotable client application");
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

#ifdef __arm__
  // Set the Raspberry GPIO pins used for short range sensors to "IN"
  system("gpio export 07 IN");
  system("gpio export 08 IN");
  system("gpio export 24 IN");
  system("gpio export 25 IN");

  // this has to be called once on program start
  if (-1 == wiringPiSetupSys()) {
    std::cout << "Error setting up wiringPi!" << std::endl;
    return -1;
  }

  pinMode(1, PWM_OUTPUT); // PWM_LED

//  pinMode(7, INPUT);
//  pinMode(8, INPUT);
//  pinMode(24, INPUT);
//  pinMode(25, INPUT);
#endif

  rotable::Client* client = new rotable::Client(configFilePath);

  rotable::ImageProvider* imageProvider = new rotable::ImageProvider(client);
  client->setImageProvider(imageProvider);

  QQuickView view;
  client->startup();
  rotable::ProductOrder* MyOrder;                   //this will be in the fulture in the client included
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.rootContext()->setContextProperty("client", client);
  view.rootContext()->setContextProperty("CategoryListModel", client->categoryListModel());
  view.rootContext()->setContextProperty("ProductListModel", client->productListModel());
  view.engine()->addImageProvider("rotable", imageProvider);
  view.rootContext()->setContextProperty("MyOrder", MyOrder);

  //view.setSource(QUrl::fromLocalFile(QString(ROTABLE_QML_PATH) + QString("main.qml")));
  view.setSource(QString("qrc:/client/main.qml"));
  view.show();

  return app.exec();
}
