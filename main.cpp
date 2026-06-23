#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "application/Application.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    Application::registerUiTypes();

    engine.loadFromModule(QML_MODULE, "Main");

    return QCoreApplication::exec();
}
