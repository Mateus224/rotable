#include "io_init_day.h"

io_init_day::io_init_day()
{
    ti.time.start();
}

void io_init_day::init(double umsatz)
{
    qDebug()<<ti.time;


    qDebug("Time elapsed: %d ms", ti.time.elapsed());
}
