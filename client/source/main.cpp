#include "private/precomp.h"
#include  "../include/qmlcontxt.h"
#include <QApplication>

#include "client.h"
#include "settings.h"
#include "imageprovider.h"
#include "productorder.h"
#include "mytables.h"
#include "languagesupport.h"
#include "touchevent.h"

#ifdef __arm__
#include <wiringPi.h>
#include <iostream>
#endif
//------------------------------------------------------------------------------
/////////////////////////////////////////////////////////
////define for which product the system will compile ////
/////////////////////////////////////////////////////////
//1=LB_Bar [LOW Budget (7" Display)]
//2=LB_Cocktail
//3=LB_Restaurant
//4=DISCO (10"Display)
#define ProductVersion 4
//-----------------------------------
/////////////////////////////////////////
////Define your device and the funktions
/////////////////////////////////////////
//1= raspberry device without sensors
//2= android device without sensors
//3= raspberry device with sensors
//4= raspberry device with sensors and pwm signal
//5= raspberry device with sensors and pwm signal and advertising sensors
#define device 1
/////////////////////////////////////////
//------------------------------------------------------------------------------

void touchEvent(QTouchEvent* test){
    qDebug()<<"bbbb";
}


int main(int argc, char *argv[])
{
  // Create minidump on program crash (for later debugging)
  //google_breakpad::MinidumpDescriptor breakpad_descriptor("/tmp");
  //google_breakpad::ExceptionHandler breakpad_handler(
  //  breakpad_descriptor, NULL, NULL, NULL, true, -1);
  QApplication app(argc, argv);

  QCoreApplication::setApplicationName("rotable-client");
  QCoreApplication::setApplicationVersion("1.0b");

  QCommandLineParser parser;
  parser.setApplicationDescription("rotable client application");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("config",
    QCoreApplication::translate("main", "Path of the configuration file."));
  parser.process(app);

  auto dir = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
  dir.mkpath("rotable");
  dir.cd("rotable");
  QString configFilePath(dir.filePath("config.ini"));

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

  //called to setup PWM from console
  system("gpio pwm-ms");
  system("gpio mode 1 pwm");

  // this has to be called once on program start
  if (-1 == wiringPiSetupSys()) {
    std::cout << "Error setting up wiringPi!" << std::endl;
    return -1;
  }

  pinMode(1, PWM_OUTPUT); // PWM_LED
  pwmWrite(1, 0);
#endif

  // Load translator
  rotable::LanguageSupport* langSupp = new rotable::LanguageSupport(rotable::LanguageSupport::AppType::client);
  //langSupp->LoadInit("de");

  langSupp->LoadInit();


  rotable::Client* client = new rotable::Client(configFilePath);

  client->_device=device;
  client->_sensors._device=device;

  rotable::ImageProvider* imageProvider = new rotable::ImageProvider(client);
  client->setImageProvider(imageProvider);


  rotable::TouchEvent*  touch=new rotable::TouchEvent;
  QQuickView* view=new QQuickView();

  client->startup();               //this will be in the fulture in the client included
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->rootContext()->setContextProperty("client", client);
  view->rootContext()->setContextProperty("CategoryListModel", client->categoryListModel());
  view->rootContext()->setContextProperty("ProductListModel", client->productListModel());
  view->engine()->addImageProvider("rotable", imageProvider);
  view->rootContext()->setContextProperty("MyOrder", client->_productOrder);
  ProductOrderListModel *_productorderlistmodel = new ProductOrderListModel(client, client->_productOrder);
  view->rootContext()->setContextProperty("MyProductOrderList", _productorderlistmodel);
  view->rootContext()->setContextProperty("CallWaiterObject", &(client->_callWaiter));
  view->rootContext()->setContextProperty("OrderQueue", &(client->_queue));
  view->rootContext()->setContextProperty("langObject", langSupp);
  view->rootContext()->setContextProperty("touchEvent",client->_touch);
  view->engine()->rootContext()->setContextProperty("mediaplayer", client->_player);

  switch (ProductVersion){
  case 1:
    view->setSource(QString("qrc:/client_LB/main_LB.qml"));
    break;
  case 2:
    view->setSource(QString("qrc:/client_LB/main_LB.qml"));
    break;
  case 3:
    view->setSource(QString("qrc:/client_LB/main_LB.qml"));
    break;
  case 4:
    view->setSource(QString("qrc:/client/main.qml"));
    break;
  }

  view->showFullScreen();

  return app.exec();
}
