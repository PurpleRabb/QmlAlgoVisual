#ifndef SORT_H
#define SORT_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QDebug>
#include "bubblework.h"
#include "selectionsortwork.h"
#include "insertionsort.h"


class Sort : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<int> values READ getValues WRITE setValues NOTIFY valuesChanged)
    Q_PROPERTY(Status status READ getStatus NOTIFY statusChanged)
    Q_PROPERTY(quint32 speed WRITE setSpeed)

    QThread bubbleThread;

    enum Status {
        Ready = 0,
        Running,
        Finished
    };

signals:
    void updateValue();
    void valuesChanged();
    void statusChanged();
    void algoStatus(QString);

public slots:
    void algoFinished() {
        qDebug() << __LINE__ <<__func__;
        currentWork->quit();
        currentWork->wait();
        _status = Finished;
    }

public:
    explicit Sort(QObject *parent = nullptr);

    Q_INVOKABLE void switchAlgo(int algoNum)
    {
        qDebug() << "switchAlgo to:" << algoNum;
        if (currentWork->isRunning()) {
            currentWork->terminate();
            currentWork->wait();
        }
        if (algoNum == 0) {
            currentWork = bw;
        }
        if (algoNum == 1) {
            currentWork = sw;
        }
        if (algoNum == 2) {
            currentWork = iw;
        }
    }

    Q_INVOKABLE void doAlgo(int algoNum)
    {
        if(currentWork != nullptr && !currentWork->isRunning() && _status == Ready) {
            qDebug() << "do algo: " << algoNum;
            _status = Running;
            currentWork->start();
        }
    }

    Q_INVOKABLE void reset()
    {
        if (_status == Finished || _status == Running)
        {
            currentWork->terminate();
            currentWork->wait();
            _status = Ready;
        }

    }

    Status getStatus() {
        return _status;
    }

    QList<int> getValues()
    {
        return values;
    }

    void setSpeed(quint32 msec)
    {
        _speed = msec;
        if (currentWork != nullptr && !currentWork->isRunning()) {
            currentWork->setSpeed(_speed);
        }
    }

    void setValues(QList<int> v) {
        if(currentWork != nullptr && !currentWork->isRunning()) {
            qDebug() << "setValues:" << v;
            this->values = v;
            currentWork->setValue(&values);
        }
    }

private:
    BubbleWork *bw;
    SelectionSortWork *sw;
    InsertionSort *iw;
    BaseWork *currentWork;
    QList<int> values;
    Status _status = Ready;
    quint32 _speed = 1000;
};

#endif // SORT_H
