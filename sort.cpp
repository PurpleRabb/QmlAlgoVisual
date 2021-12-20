#include "sort.h"

Sort::Sort(QObject *parent)
    : QObject{parent}
{
    bw = new BubbleWork(this);
    sw = new SelectionWork(this);
    currentWork = bw;

    connect(bw,SIGNAL(updateValue()),this,SIGNAL(valuesChanged()));
    connect(bw,SIGNAL(algofinished()),this,SLOT(algoFinished()));
    connect(bw,SIGNAL(algoStatus(QString)),this,SIGNAL(algoStatus(QString)));

    connect(sw,SIGNAL(updateValue()),this,SIGNAL(valuesChanged()));
    connect(sw,SIGNAL(algofinished()),this,SLOT(algoFinished()));
    connect(sw,SIGNAL(algoStatus(QString)),this,SIGNAL(algoStatus(QString)));
}

