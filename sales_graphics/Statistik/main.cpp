#include <qapplication.h>
#include <qmainwindow.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qwt_abstract_scale.h>
#include "statistik_plot.h"
#include "date.h"
#include "io_init.h"
#include "io_writeinmonthwithnewdata.h"
#include "date.h"
//using namespace IO_WriteInMonthData;

class MainWindow: public QMainWindow
{
public:
    MainWindow( QWidget * = NULL );

private:
    Statistik_Plot *d_plot;
};

MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    d_plot = new Statistik_Plot( this );
    setCentralWidget(d_plot);
    QToolBar *toolBar = new QToolBar( this );

    //QComboBox *typeBox = new QComboBox( toolBar );
    QToolButton *btnExport = new QToolButton( toolBar );
    btnExport->setText( "Save PDF" );
    btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    connect( btnExport, SIGNAL( clicked() ), d_plot, SLOT(exportPlot() ) );

    //toolBar->addWidget( typeBox );
    toolBar->addWidget( btnExport );
    addToolBar( toolBar );
    d_plot->setMode(3);

}



int main( int argc, char **argv )
{
    double umsatz=7.20; //heutiger Umsatz
    Date dat;

    QApplication a(argc, argv);
    IO_init Init;
    Init.JahrVollLegeNeueDateiAn(); //diese Funktion muss als erstes aufgerufen werden (bevor etwas in Umsatz.data geschrieben wird)
    Init.untersucheAufLueckenUndFuelleAuf();
    Init.schreibeMonatsUmsatz();

    IO_WriteInMonthData test;
    test.schreibeInUmsatz(umsatz, dat.date.dayOfYear());

    MainWindow mainWindow;

    mainWindow.resize( 800, 600 );
    mainWindow.show();


    return a.exec();
}
