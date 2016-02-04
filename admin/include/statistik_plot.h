#ifndef STATISTIK_PLOT_H
#define STATISTIK_PLOT_H
/*
#include <qwt_plot.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_renderer.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
*/
#include <qpen.h>
#include <stdlib.h>
#include <date.h>


class Statistik_Plot//: public QwtPlot
{
    //Q_OBJECT


public:
    Statistik_Plot( QWidget * = NULL );
    /*
    qint32 istream;

public Q_SLOTS:
    void setMode( int );
    void exportPlot();

private:
    void populate();
    //Date date;
private Q_SLOTS:
    void showItem( const QVariant &, bool on );
//QDataStream & operator>> (Statistik_Plot& plot, qint32 & stream );*/
};


#endif // STATISTIK_PLOT_H
