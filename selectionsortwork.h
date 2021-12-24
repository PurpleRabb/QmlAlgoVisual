#ifndef SELECTIONSORTWORK_H
#define SELECTIONSORTWORK_H

#include <QObject>
#include "basework.h"

class SelectionSortWork : public BaseWork
{
public:
    explicit SelectionSortWork(QObject *parent = nullptr):BaseWork(parent) { emit registerSort("Selection",this); }
    void run() override;
};

#endif // SELECTIONSORTWORK_H
