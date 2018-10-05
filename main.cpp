#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <unistd.h>
#include "qquickimage.h"
#include "xlibutil.h"
#include "context.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Context *context = new Context();
    QQuickImage image;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Context", context);
    engine.addImageProvider("pixmap", &image);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    context->engine = &engine;
    QObject *obj = engine.rootObjects().first();
    QWindow *window = qobject_cast<QWindow *>(obj);

//    context->window = window;
    Xlibutil util;
    util.openboxChange(window->winId(), ALL_DESKTOPS);
    util.xchange(window->winId(), "_NET_WM_WINDOW_TYPE_DESKTOP");

    return app.exec();
}