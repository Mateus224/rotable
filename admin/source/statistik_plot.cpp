/*#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_renderer.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <qpen.h>
#include <stdlib.h>

#include "statistik_plot.h"
#include "date.h"
#include "io_readfordiagram.h"


class Histogram: public QwtPlotHistogram
{
public:
    Histogram( const QString &, const QColor & );

    void setColor( const QColor & );
    void setValues( uint numValues, const int * );
};

Histogram::Histogram( const QString &title, const QColor &symbolColor ):
    QwtPlotHistogram( title )
{
    setStyle( QwtPlotHistogram::Columns );

    setColor( symbolColor );
}

void Histogram::setColor( const QColor &color )
{
    QColor c = color;
    c.setAlpha( 160 );
    setBrush( QBrush( c ) );
}

void Histogram::setValues( uint numValues, const int *values )
{
    QVector<QwtIntervalSample> samples( numValues );
    for ( uint i = 0; i < numValues; i++ )
    {
        QwtInterval interval( double( i ), i + 1);
        interval.setBorderFlags( QwtInterval::ExcludeMaximum );

        samples[i] = QwtIntervalSample( values[i], interval );
    }

    setData( new QwtIntervalSeriesData( samples ) );
}

Statistik_Plot::Statistik_Plot( QWidget *parent ):
    QwtPlot( parent )
{
    setTitle("Umsatz");

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette(Qt::lightGray);
    canvas->setBorderRadius(12);
    setCanvas( canvas );

    plotLayout()->setAlignCanvasToScales( true );

    setAxisTitle( QwtPlot::yLeft, "€uro" );
    setAxisTitle( QwtPlot::xBottom, "Month" );

    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode( QwtLegendData::Checkable );
    insertLegend( legend, QwtPlot::RightLegend );

    populate();

    connect( legend, SIGNAL( checked( const QVariant &, bool, int ) ),
        SLOT( showItem( const QVariant &, bool ) ) );

    replot(); // creating the legend items

    QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotHistogram );
    for ( int i = 0; i < items.size(); i++ )
    {
        if ( i == 0 )
        {
            const QVariant itemInfo = itemToInfo( items[i] );

            QwtLegendLabel *legendLabel =
                qobject_cast<QwtLegendLabel *>( legend->legendWidget( itemInfo ) );
            if ( legendLabel )
                legendLabel->setChecked( true );

            items[i]->setVisible( true );
        }
        else
        {
            items[i]->setVisible( false );
        }
    }

    setAutoReplot( true );
}

void Statistik_Plot::populate()
{
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableX( false );
    grid->enableY( true );
    grid->enableXMin( false );
    grid->enableYMin( false );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach( this );




    int *UmsatzJahr=new int[12];
    int *UmsatzletztesJahr=new int[12];
    int *UmsatzVorLetztesJahr=new int[12];


    IO_ReadForDiagram thisYear;
    double* ptrtY = 0;

    ptrtY=thisYear.leseAusUmsatzDiesesJahr();


    for (int i=0; i<12; i++)  // Array durchlaufen
    {
        UmsatzJahr[i] = ptrtY[i]; // einlesen der Gewinne
    }

    IO_ReadForDiagram lastYear;
    double *ptrlY=0;
    ptrlY=lastYear.leseAusUmsatzVorLetzenJahr();
    for (int i=0; i<12; i++)  // Array durchlaufen
    {
        UmsatzletztesJahr[i] = ptrlY[i]; // einlesen der Gewinne
    }


    IO_ReadForDiagram yearBeforLast;
    double *ptrYbl=0;
    ptrYbl=lastYear.leseAusUmsatzVorVorLetzenJahr();
    for (int i=0; i<12; i++)  // Array durchlaufen
    {
        UmsatzVorLetztesJahr[i] = ptrYbl[i]; // einlesen der Gewinne
    }
    //const int novemberValues[12] = { 4, 15, 22, 34, 13, 4 };
    int iYear= date.date.year();
    QString sYear = QString::number(iYear);
    Histogram *Year = new Histogram(sYear, Qt::blue );
    Year->setValues(12 , UmsatzJahr );
    Year->attach(this);

    int ilYear= date.date.year()-1;
    QString slYear = QString::number(ilYear);
    Histogram *lYear = new Histogram(slYear, Qt::darkCyan );
    lYear->setValues(12,UmsatzletztesJahr);
    lYear->attach(this);

    int iYearbl= date.date.year()-2;
    QString sYearbl = QString::number(iYearbl);
    Histogram *Yearbl = new Histogram( sYearbl, Qt::gray );
    Yearbl->setValues(12,UmsatzVorLetztesJahr);
    Yearbl->attach(this);
}



void Statistik_Plot::exportPlot()
{
    QwtPlotRenderer renderer;
    int iPDFy= date.date.year();
    int iPDFm= date.date.month();
    QString sPDFy = QString::number(iPDFy);
    QString sPDFm = QString::number(iPDFm);
    sPDFy.append("_");
    sPDFy.append(sPDFm);

    sPDFy.append("_Diagram.pdf");
    renderer.exportTo( this, sPDFy);
}

void Statistik_Plot::setMode( int mode )
{
    QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotHistogram );

    for ( int i = 0; i < items.size(); i++ )
    {
        QwtPlotHistogram *histogram = static_cast<QwtPlotHistogram *>( items[i] );
        if ( mode < 3 )
        {
            histogram->setStyle( static_cast<QwtPlotHistogram::HistogramStyle>( mode ) );
            histogram->setSymbol( NULL );

            QPen pen( Qt::black, 0 );
            if ( mode == QwtPlotHistogram::Lines )
                pen.setBrush( histogram->brush() );

            histogram->setPen( pen );
        }
        else
        {
            histogram->setStyle( QwtPlotHistogram::Columns );

            QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
            symbol->setFrameStyle( QwtColumnSymbol::Raised );
            symbol->setLineWidth( 3 );
            symbol->setPalette( QPalette( histogram->brush().color() ) );

            histogram->setSymbol( symbol );
        }
    }
}

void Statistik_Plot::showItem( const QVariant &itemInfo, bool on )
{
    QwtPlotItem *plotItem = infoToItem( itemInfo );
    if ( plotItem )
        plotItem->setVisible( on );
}
*/
