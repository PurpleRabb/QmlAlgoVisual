#ifndef MERGESORT_H
#define MERGESORT_H

#include <QObject>
#include "basework.h"

class MergeSort : public BaseWork
{
public:
    explicit MergeSort(QObject *parent = nullptr):BaseWork(parent) { emit registerSort("Merge",this); }
    void run() override;

private:
    void __MergeSort(QList<int> *a, int left, int right, int * tmp);
};

#endif // MERGESORT_H
