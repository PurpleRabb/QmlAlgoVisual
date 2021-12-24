#include "sort.h"

Sort::Sort(QObject *parent)
    : QObject{parent}
{
    bw = new BubbleWork(this);
    sw = new SelectionSortWork(this);
    iw = new InsertionSort(this);
    currentWork = bw;
}

