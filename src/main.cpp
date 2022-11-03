#include <QApplication>
#include <QQmlApplicationEngine>
#include "opendcm.h"
#include <QIcon>
#include "rgbachange.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/res/CT.png"));

    QQuickVTKRenderWindow::setupGraphicsBackend();
    qmlRegisterType<QQuickVTKRenderWindow>("QQuickVTKRenderWindow", 1, 0, "QQuickVTKRenderWindow");
    qmlRegisterType<QQuickVTKRenderItem>("QQuickVTKRenderItem", 1, 0, "QQuickVTKRenderItem");
    qmlRegisterType<OpenDcm>("OpenDcm", 1, 0, "OpenDcm");

    QQmlApplicationEngine engine;

    RGBAchange rgbachange;
    engine.rootContext()->setContextProperty("rgbachange",&rgbachange);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
