#include "private/precomp.h"

#include "mainwindow.h"
#include "controller.h"

#include "loglisternerstdout.h"

#include "statistik_plot.h"
#include "date.h"
#include "io_init.h"
#include "io_writeinmonthwithnewdata.h"

#include "client/linux/handler/exception_handler.h"

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  // Create minidump on program crash (for later debugging)
  google_breakpad::MinidumpDescriptor breakpad_descriptor("/tmp");
  google_breakpad::ExceptionHandler breakpad_handler(
    breakpad_descriptor, NULL, NULL, NULL, true, -1);

  QApplication a(argc, argv);

  QCoreApplication::setApplicationName("rotable-admin");
  QCoreApplication::setApplicationVersion("1.0b");
  QCoreApplication::setOrganizationName("rotable");
  QCoreApplication::setOrganizationDomain("rotable.info");

  QCommandLineParser parser;
  parser.setApplicationDescription("rotable client application");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("config", QCoreApplication::translate("main", "Path of the configuration file."));
  parser.process(a);

  QString configFilePath("config.ini");

  QStringList args = parser.positionalArguments();
  if (args.size() > 0) {
    configFilePath = args[0];
  }

  //----------------------------------------------------------------------------
  double umsatz=7.20; //heutiger Umsatz

  IO_init Init;
  Init.JahrVollLegeNeueDateiAn(); //diese Funktion muss als erstes aufgerufen werden (bevor etwas in Umsatz.data geschrieben wird)
  Init.untersucheAufLueckenUndFuelleAuf();
  Init.schreibeMonatsUmsatz();

  IO_WriteInMonthData test;
  test.schreibeInUmsatz(umsatz,0);
  //----------------------------------------------------------------------------

  MainWindow w;
  Controller controller(&w, configFilePath);
  w.show();

  return a.exec();
}
