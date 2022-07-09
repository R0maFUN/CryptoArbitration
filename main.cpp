#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ViewModel/MainViewModel.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ViewModel::MainViewModel mainViewModel;

    engine.rootContext()->setContextProperty("viewModel", &mainViewModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    qDebug() << "Starting the app";
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
