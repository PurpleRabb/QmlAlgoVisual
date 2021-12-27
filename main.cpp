#include <QApplication>
#include <QQmlApplicationEngine>
#include "algo/sort/sort.h"

static QObject *getSort(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Sort *ss = new Sort();
    return ss;
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    qmlRegisterSingletonType<Sort>("Sort", 1, 0, "Sort", getSort);
#else
    QScopedPointer<Sort> sort(new Sort);
    qmlRegisterSingletonInstance("Sort", 1, 0, "Sort", sort.get());
#endif

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
