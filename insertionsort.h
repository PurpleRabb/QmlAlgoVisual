#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <QObject>
#include "basework.h"

class InsertionSort : public BaseWork
{
public:
    explicit InsertionSort(QObject *parent = nullptr):BaseWork(parent) { }

public:
    void run() override;
};

#endif // INSERTIONSORT_H
