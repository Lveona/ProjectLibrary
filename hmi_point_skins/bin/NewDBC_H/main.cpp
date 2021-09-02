#include <QtDebug>
#include <QDir>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include "hmibox.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;
    HMIBox box;
    view.rootContext()->setContextProperty("HMIBox", &box);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.setTitle("生成DBCData和dynamic_create.h");
    view.show();
    return app.exec();
}
