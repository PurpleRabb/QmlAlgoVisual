#ifndef SORT_H
#define SORT_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QDebug>

class BubbleWork : public QThread
{
    Q_OBJECT

public:
    explicit BubbleWork(QObject *parent = nullptr) { }

signals:
    void updateValue();
    void algofinished();

public:
    void run() override {
        int len = values->length();
        qDebug() << "values len:" << len;
        for (int i=0; i < len - 1; i++) {
            for (int j=0; j<len-1-i; j++) {
                if ((*values)[j] > (*values)[j+1]) {
                    int temp = (*values)[j];
                    (*values)[j] = (*values)[j+1];
                    (*values)[j+1] = temp;
                    emit updateValue();
                    msleep(_speed);
                }
            }
        }
        emit algofinished();
    }

    void setValue(QList<int> *v)
    {
        this->values = v;
    }

    void setSpeed(quint32 msec)
    {
        _speed = msec;
    }

private:
    QList<int> *values;
    quint32 _speed = 1000;
};

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

public slots:
    void algoFinished() {
        qDebug() << __LINE__ <<__func__;
        bw->quit();
        bw->wait();
        _status = Finished;
    }

public:
    explicit Sort(QObject *parent = nullptr);

    Q_INVOKABLE void doAlgo(int algoNum)
    {
        if(bw != nullptr && !bw->isRunning() && _status == Ready) {
            qDebug() << "do algo";
            _status = Running;
            bw->start();
        }
    }

    Q_INVOKABLE void reset()
    {
        if (_status == Finished || _status == Running)
        {
            bw->terminate();
            bw->wait();
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
        if (bw != nullptr && !bw->isRunning()) {
            bw->setSpeed(_speed);
        }
    }

    void setValues(QList<int> v) {
        if(bw != nullptr && !bw->isRunning()) {
            qDebug() << "setValues:" << v;
            this->values = v;
            bw->setValue(&values);
        }
    }

private:
    BubbleWork *bw;
    QList<int> values;
    Status _status = Ready;
    quint32 _speed = 1000;
};

#endif // SORT_H
