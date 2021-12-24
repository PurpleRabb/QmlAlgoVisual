#ifndef BASEWORK_H
#define BASEWORK_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#define MARK(val1,val2)
#define VALUES (*values)

class BaseWork : public QThread
{
    Q_OBJECT

public:
    BaseWork(QObject *parent = nullptr) {
        connect(this,SIGNAL(updateValue()),parent,SIGNAL(valuesChanged()));
        connect(this,SIGNAL(algofinished()),parent,SLOT(algoFinished()));
        connect(this,SIGNAL(algoStatus(QString)),parent,SIGNAL(algoStatus(QString)));
        connect(this,SIGNAL(registerSort(QString, BaseWork *)),parent,SLOT(registerSort(QString,BaseWork *)));
    }

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
    void registerSort(QString,BaseWork *);

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

#endif // BASEWORK_H
