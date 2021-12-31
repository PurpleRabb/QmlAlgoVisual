#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <QObject>
#include "basework.h"

class QuickSort : public BaseWork
{
public:
    explicit QuickSort(QObject *parent = nullptr):BaseWork(parent) { emit registerSort("QuickSort",this); }
    void run() override;

private:
    int partition(QList<int>* root,int low,int high);
    void quickSortNoRec(QList<int>* root,int low,int high);
};

#endif // QUICKSORT_H
