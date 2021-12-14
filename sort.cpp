#include "sort.h"

Sort::Sort(QObject *parent)
    : QObject{parent}
{
    bw = new BubbleWork(this);
    connect(bw,SIGNAL(updateValue()),this,SIGNAL(valuesChanged()));
    connect(bw,SIGNAL(algofinished()),this,SLOT(algoFinished()));
}
