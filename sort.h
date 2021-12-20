#ifndef SORT_H
#define SORT_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#define MARK(val1,val2)

class Work : public QThread
{
    Q_OBJECT

public:
    void setValue(QList<int> *v)
    {
        this->values = v;
    }

    void setSpeed(quint32 msec)
    {
        _speed = msec;
    }

signals:
    void updateValue();
    void algofinished();
    void algoStatus(QString);

protected:
    QJsonObject MsgBuilder() {
        QJsonObject object;
        QJsonArray list;
        list.append(-1);
        list.append(-1);
        object.insert("Marked",list);
        object.insert("Restored",list);
        return object;
    }

    QString MARKED(int v1,int v2) {
        QJsonObject msg = MsgBuilder();
        QJsonArray marked = msg["Marked"].toArray();
        marked[0] = v1;
        marked[1] = v2;
        msg["Marked"] = marked;
        QJsonDocument jsonDoc(msg);
        return QString(jsonDoc.toJson());
    }

    QString RESTORED(int v1,int v2) {
        QJsonObject msg = MsgBuilder();
        QJsonArray marked = msg["Restored"].toArray();
        marked[0] = v1;
        marked[1] = v2;
        msg["Restored"] = marked;
        QJsonDocument jsonDoc(msg);
        return QString(jsonDoc.toJson());
    }

protected:
    QList<int> *values = nullptr;
    quint32 _speed = 1000;
};

class BubbleWork : public Work
{
public:
    explicit BubbleWork(QObject *parent = nullptr) { }

public:
    void run() override {
        if (values == nullptr) {
            emit algofinished();
            return;
        }
        qsizetype len = values->length();
        qDebug() << "values len:" << len;
        for (int i=0; i < len - 1; i++) {
            for (int j=0; j<len-1-i; j++) {
                emit algoStatus(MARKED(j,j+1));
                msleep(_speed);
                if ((*values)[j] > (*values)[j+1]) {
                    std::swap((*values)[j],(*values)[j+1]);
                    emit updateValue();
                }
                emit algoStatus(RESTORED(j,-1));//将比较的前一个数字颜色还原
            }
        }
        emit algoStatus(MARKED(0,-1)); //结束后将最前面的也涂掉
        emit algofinished();
    }
};

class SelectionWork : public Work
{
public:
    explicit SelectionWork(QObject *parent = nullptr) { }

public:
    void run() override {
        if (values == nullptr) {
            emit algofinished();
            return;
        }
        qsizetype len = values->length();
        qDebug() << "values len:" << len;
        //对数组a排序,length是数组元素数量
        for( int i = 0; i < len; i++ ) {
            // 找到从i开始到最后一个元素中最小的元素,k存储最小元素的下标.
            int k = i;
            for( int j = i + 1; j < len; j++ ) {
                if( (*values)[j] < (*values)[k] )
                {
                    emit algoStatus(MARKED(k,-1));//标记要判断交换的两个数字
                    k = j;
                }
            }

            // 将最小的元素a[k] 和 开始的元素a[i] 交换数据.
            if( k != i ) {
                std::swap((*values)[k],(*values)[i]);
            }

            emit updateValue();
            msleep(_speed);
        }
        emit algofinished();
    }
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
        if (algoNum == 0) {
            currentWork = bw;
        }
        if (algoNum == 1) {
            currentWork = sw;
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
    SelectionWork *sw;
    Work *currentWork;
    QList<int> values;
    Status _status = Ready;
    quint32 _speed = 1000;
};

#endif // SORT_H
