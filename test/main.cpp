#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QDebug>

#include "../include/app_view.h"
#include "../include/app_abstract.h"
#include "DemoApp.h"

#define APP_MAIN_UI_PATH "qrc:/QML/system-ui/main.qml"

int main(int argc, char *argv[]) {

    try {
        hmi::AbstractApplication *hmiApp = new hmi::DemoApp();
        hmi::ApplicationView *appView;

        QGuiApplication *app = hmiApp->create(argc, argv);
        QQmlApplicationEngine *engine = static_cast<QQmlApplicationEngine *>(hmiApp->appEnngine()->engine());

        const QUrl url(APP_MAIN_UI_PATH);
        QObject::connect(
            engine, &QQmlApplicationEngine::objectCreated,
            app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
        engine->load(url);
        return app->exec();

    } catch (const std::exception &e) {
        qCritical() << "ERROR:" << e.what();
        return 2;
    }
}