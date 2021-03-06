#include "sort.h"

Sort::Sort(QObject *parent)
    : QObject{parent}
{
    bw = new BubbleWork(this);
    sw = new SelectionSortWork(this);
    iw = new InsertionSort(this);
    ss = new ShellSort(this);
    ms = new MergeSort(this);
    qs = new QuickSort(this);
    currentWork = bw;
}

