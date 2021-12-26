#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <QObject>
#include "basework.h"


class ShellSort : public BaseWork
{
public:
    explicit ShellSort(QObject *parent = nullptr):BaseWork(parent) { emit registerSort("Shell",this); }

public:
    void run() override;
};
#endif // SHELLSORT_H
