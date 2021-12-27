#ifndef BUBBLEWORK_H
#define BUBBLEWORK_H

#include <QObject>
#include "basework.h"

class BubbleWork : public BaseWork
{
public:
    explicit BubbleWork(QObject *parent = nullptr):BaseWork(parent) { emit registerSort("Bubble",this); }

public:
    void run() override;
};

#endif // BUBBLEWORK_H
